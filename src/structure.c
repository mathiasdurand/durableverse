#include <time.h>
#include <stdlib.h>

#include "../headers/structure.h"

/**Structure de liste de cartes
*/
struct str_list_card {
	Card* list;
	int size;
};

List_Card createListCard() {
	List_Card instance = (List_Card)malloc(sizeof(struct str_list_card));
	instance->list = NULL;
	instance->size = 0;
	return instance;
}

void destroyListCard(List_Card list_card) {
	destroyElements(list_card->list, list_card->size);
	free(list_card->list);
	free(list_card);
}

void destroyElements(Card* list, int size)
{
	for (int i = 0; i < size; i++)
	{
		destroyCard(list[i]);
	}
}


Card removeElement(List_Card list_card, int index)
{
	if (index < 0 || index >= list_card->size)
		return NULL;

	Card* old_list = list_card->list;
	Card* new_list = (Card*)malloc((list_card->size-1)*sizeof(Card));

	Card removed_card = copyCard(old_list[index]);

	for(int i = 0; i < index; i++)
	{
		new_list[i] = copyCard(old_list[i]);
	}
	for(int i = index + 1; i < list_card->size; i++)
	{
		new_list[i-1] = copyCard(old_list[i]);
	}

	destroyElements(old_list, list_card->size);
	free(old_list);

	list_card->list = new_list;
	list_card->size -= 1;
	
	return removed_card;
}

void addElement(List_Card list_card, Card card) {
	list_card->size += 1;
	Card* new_content = (Card*)calloc(list_card->size, sizeof(Card));
	for (int i = 0; i < list_card->size - 1; i++)
		new_content[i] = copyCard(list_card->list[i]);
	destroyElements(list_card->list, list_card->size-1);
	free(list_card->list);
	list_card->list = new_content;
	list_card->list[list_card->size - 1] = card;
}


void addAndSort(List_Card list_card, Card card) {
	addElement(list_card, card);
	if (getType(card)==STUDENT) { //Tri du student_pool
		Card* fise_list = (Card*)calloc(list_card->size, sizeof(Card));
		Card* fisa_list = (Card*)calloc(list_card->size, sizeof(Card));
		int cpt_fise = 0;
		int cpt_fisa = 0;
		for (int i=0; i < list_card->size; i++) { //On sépareles cartes Eleve en deux listes une FISE, une FISA
			if (getCardId(list_card->list[i])==FISE) {
				fise_list[cpt_fise] =  copyCard(list_card->list[i]);
				cpt_fise += 1;
			}
			else {
				fisa_list[cpt_fisa] =  copyCard(list_card->list[i]);
				cpt_fisa += 1;
			}
		}
		Card* new_content = (Card*)calloc(list_card->size, sizeof(Card));
		for (int i=0; i < list_card->size; i++) {
			if (i < cpt_fise) { // D'abord les FISE
				new_content[i] = copyCard(fise_list[i]);
			}
			else { // Puis les FISA
				new_content[i] = copyCard(fisa_list[i-cpt_fise]);
			}
		}
		destroyElements(list_card->list,list_card->size);
		destroyElements(fise_list,cpt_fise);
		destroyElements(fisa_list,cpt_fisa);
		free(list_card->list);
		free(fise_list);
		free(fisa_list);
		list_card->list = new_content;
	}
	else { //Tri de la main
		int min_idx; // Indice de la carte au plus petit coût
		Card min;
		Card old;
		for (int j=0; j < list_card->size; j++) {
			old = list_card->list[j];
			min = list_card->list[j];
			min_idx = j;
			for (int i=j; i < list_card->size; i++) {
				if (getPE(list_card->list[i]) < getPE(min)) {
					min = list_card->list[i];
					min_idx = i;
				}
			}
			list_card->list[min_idx] = old;
			list_card->list[j] = min;
		}  
	}
}

void shuffle(List_Card list_card) {
	if (list_card->size > 1) {
		for (int i = 0; i < list_card->size - 1; i++)
		{
			// j is a random number between i and list_card->size-1 (included)
			int j = i + rand() % (list_card->size - i);
			//swap the values of list_card->list[i] and list_card->list[j]
			Card tmp = list_card->list[i];
			list_card->list[i] = list_card->list[j];
			list_card->list[j] = tmp;
		}   
	}
}

Card* getList(List_Card list_card) {
	return list_card->list;
}

int getSize(List_Card list_card) {
	return list_card->size;
}


int exists(List_Card list_card, Card card)
{
	id_cardname id = getCardId(card);
	int compteur = 0;

	for (int i = 0; i < getSize(list_card); i++)
	{
		if (getCardId(getList(list_card)[i]) == id)
			compteur++;
	}
	return compteur;
}


void displaceElement(Card card, List_Card original_list, List_Card destination_list)
{
	int index;

	for (int i = 0; i < getSize(original_list); i++)
	{
		if(card == getList(original_list)[i])
			index = i;
	}

	addElement(destination_list, removeElement(original_list, index));
}
