#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "../headers/joueur.h"

#define MAX_STRING 100

/********************* STRUCTURE **********************/

struct str_ensiie {
	char* name; //nom du joueur
	int sustainable_points; //points de DD
	List_Card deck; //pioche
	List_Card hand; //main de chaque ENSIIE, la ou vont les cartes piochees dans le deck
	Board board; //le plateau propre a l'ensiie, ce qu'elle pose devant elle
	int energy; //points d'énergie du joueur
	List_Card graveyard; //defausse, la ou sont posees les cartes qui ne sont plus en jeu
	int is_current_player; //0 si le joueur n'est pas le joueur qui joue, 1 si oui

	int additional_sustainable_points; //(Peut être négatif) Permet de donner ou retirer des DD à la fin du tour
	
	int changed_fise_sustainable; //1 si le développement des FISE est amélioré, 0 sinon
	int changed_fise_durability; //1 si la durabilité des FISE est améliorée, 0 sinon
	
	int changed_fisa_sustainable; //1 si le développement des FISA est amélioré, 0 sinon
	int changed_fisa_durability; //1 si la durabilité des FISA est améliorée, 0 sinon
	
};


/******** Joueur ********/

Ensiie createEnsiie() {
	Ensiie instance = (Ensiie)malloc(sizeof(struct str_ensiie));
	instance->name = (char*) malloc(MAX_STRING*sizeof(char));
	instance->deck = createListCard();
	instance->hand = createListCard();
	instance->board = createBoard();
	instance->energy = 0;
	instance->sustainable_points = 0;
	instance->additional_sustainable_points = 0;
	instance->graveyard = createListCard();
	instance->is_current_player = 0; 
	instance->changed_fise_sustainable = 0; 
	instance->changed_fise_durability = 0; 
	instance->changed_fisa_sustainable = 0; 
	instance->changed_fisa_durability = 0; 

	return instance;
}

void destroyEnsiie(Ensiie player) {
	destroyListCard(player->deck);
    destroyListCard(player->hand);
    destroyListCard(player->graveyard);
    destroyBoard(player->board);
	free(player->name);
    free(player);
}

void initiateEnsiie(Ensiie player)
{
	int q = 0;
	for (int id = 1; id < FISE; id++) { //FISE correspond à l'identifiant de la première carte qui n'est pas une carte action. Ainsi on veut bien toutes les cartes avant la carte FISE
		q = initiateQuantity(id);
		for (int i = 0; i < q; i++) {
			addElement(getDeck(player), createCard(id));
		}
	}

	shuffle(getDeck(player));	//On mélange le deck

	addElement(getHand(player), createCard(END_PHASE)); //La première carte du joueur est la carte de fin de phase

	for (int i = 0; i<2; i++)	//Le joueur tire 2 cartes à son initialisation pour qu'au début de sa phase il en tire une autre et commence avec 3 cartes
	{
		drawEnsiie(player);
	}
}

void drawEnsiie(Ensiie player)
{
	addAndSort(getHand(player), removeElement(getDeck(player), getSize(getDeck(player))-1));	//On prend une carte du deck pour la mettre dans la main du joueur
}


void addEleve (id_cardname id, Ensiie player)
{
	Card temp;
	
	temp = createCard(id);
	setDurability(temp, max(0, getDurability(temp) + getChangedSustOrDura(player, DURABILITY, id)));  	//On initialise la dirabilité et le développement de la carte en fonction des buffs ou débuffs sur le joueur
	setCardSustainable(temp, max(0, getCardSustainable(temp) + getChangedSustOrDura(player, SUSTAINABLE, id) ));
	addAndSort(getStudentPool(getBoard(player)), temp);
}


void addEnergy (Ensiie player, int energy)
{
	setEnergy(player, getEnergy(player) + abs(energy));
}

void removeEnergy(Ensiie player, int energy)
{
	setEnergy(player, (int)max(0, getEnergy(player) - abs(energy)));
}

int getEnergy(Ensiie player)
{
	return player->energy;
}

void setEnergy(Ensiie player, int energy)
{
	player->energy=energy;
}

void countEnergy(Ensiie player, int round)
{
	int result = 0;

	id_cardname id;

	List_Card student_pool = getStudentPool(getBoard(player));

	for (int i = 0; i < getSize(student_pool); i++)
	{
		id = getCardId(getList(student_pool)[i]);

		if(id == FISE)
			result++;

		if(id == FISA)			//Si on est sur le cas d'une carte FISA, on ne compte son énergie que pour les tours impairs (son énergie vaut double par ailleurs)
			if(round % 2 == 1)
				result += 2;
	}

	setEnergy(player, result);
}


int enoughEnergy(Ensiie player, Card card)
{
	if(getEnergy(player) >= getPE(card))
		return 1;
	else 
		return 0;
}


int numberEleve(Ensiie player)
{
	int compteur = 1;	//Le compteur de base est à 1 car le joueur pioche à priori qu'une carte Elève au début de son tour

	List_Card staff_pool = getStaffPool(getBoard(player));

	for (int i=0; i < getSize(staff_pool); i++) //i.e   i < (longueur de la liste de cartes personnel jouées)
	{
		for (int j=0; j < getSizeEffects(getList(staff_pool)[i]); j++)	
		{
			if(getEffects(getList(staff_pool)[i])[j]==E)	//Si on voit qu'une carte Personnel jouée a l'effet E, on ajoute 1 au compteur
				compteur++;
		}
	}

	return compteur;
}

int numberCard(Ensiie player)	//Même principe que la fonction numberEleve(...) définie précédemment mais on regarde s'il y a une carte avec l'effet DR
{
	int compteur = 1;

	List_Card staff_pool = getStaffPool(getBoard(player));

	for (int i=0; i < getSize(staff_pool); i++) //i.e i < longueur de la liste de cartes personnel jouées
	{
		for (int j=0; j < getSizeEffects(getList(staff_pool)[i]); j++)
		{
			if(getEffects(getList(staff_pool)[i])[j]==DR)
				compteur++;
		}
	}

	return compteur;
}

int isInHand(Ensiie player, Card card)
{
	if (exists(getHand(player), card) > 0)
		return 1;
	else 
		return 0;
}

char* getPlayerName(Ensiie player) {
	return player->name;
}

List_Card getDeck(Ensiie player)
{
	return player->deck;
}

List_Card getHand(Ensiie player)
{
	return player->hand;
}

List_Card getGraveyard(Ensiie player)
{
	return player->graveyard;
}


int getFiseNumber(Ensiie player)
{
	Card temp_card = createCard(FISE);		
	int result = exists( getStudentPool(getBoard(player)), temp_card);
	destroyCard(temp_card);

	return result;
}


int getFisaNumber(Ensiie player)
{
	Card temp_card = createCard(FISA);
	int result = exists( getStudentPool(getBoard(player)), temp_card);
	destroyCard(temp_card);

	return result;
}


int getPlayerSustainablePoints(Ensiie player)
{
	return player->sustainable_points;
}


void addPlayerSustainablePoints(Ensiie player, int points)
{
	player->sustainable_points += abs(points);
}

int getAdditionalSustainablePoints(Ensiie player)
{
	return player->additional_sustainable_points;
}


void addAdditionalSustainablePoints(Ensiie player, int points)
{
	player->additional_sustainable_points += abs(points);
}


void removeAdditionalSustainablePoints(Ensiie player, int points)
{
	player->additional_sustainable_points -= abs(points);
}


Board getBoard(Ensiie player)
{
	return player->board;
}


int isCurrentPlayer(Ensiie player)
{
	return player->is_current_player;
}


void setIsCurrentPlayer(Ensiie player, int valeur)
{
	if (valeur == 0 || valeur == 1)
		player->is_current_player = valeur;
}


void changeSustOrDura(Ensiie player, sust_or_dura dura_or_sust, id_cardname id, int value)
{
	if (dura_or_sust == 0) //Développement
		if(id == FISE)	//FISE
			player->changed_fise_sustainable += value;
		else 			//FISA
			player->changed_fisa_sustainable += value;
	else					//Durabilité
		if(id == FISE)	//FISE
			player->changed_fise_durability += value;
		else			//FISA
			player->changed_fisa_durability += value;
}


int getChangedSustOrDura(Ensiie player, sust_or_dura dura_or_sust, id_cardname id)
{
	if (dura_or_sust == 0) //Développement
		if(id == FISE)	//FISE
			return player->changed_fise_sustainable;
		else 			//FISA
			return player->changed_fisa_sustainable;
	else					//Durabilité
		if(id == FISE)	//FISE	
			return player->changed_fise_durability;
		else			//FISA
			return player->changed_fisa_durability;
}


void updateSustAndDura(Ensiie player)
{
	Card temp;
	int special_durability = 0;
	int special_sustainable = 0;

	//On va récupérer les buffs et débuffs de durabilité et de développement enregistrés comme attribut du joueur et on va l'ajouter (peut être négatif) aux statistiques de base : 1 de Durabilité et 1 de Développement
	for(int i = 0; i < getSize(getStudentPool(getBoard(player))); i++)
	{
		temp = getList(getStudentPool(getBoard(player)))[i];
		
		if( (getSpecialisation(temp) == GL || getSpecialisation(temp) == PL) && (isStaffSpecialised(getBoard(player), GL) == 1))
			special_sustainable++;

		if( (getSpecialisation(temp) == HPC || getSpecialisation(temp) == PL) && (isStaffSpecialised(getBoard(player), HPC) == 1))
			special_durability++;

		if( (getSpecialisation(temp) == MA || getSpecialisation(temp) == PL) && (isStaffSpecialised(getBoard(player), MA) == 1))
			special_durability++;

		if( (getSpecialisation(temp) == IN || getSpecialisation(temp) == PL) && (isStaffSpecialised(getBoard(player), IN) == 1))
			special_sustainable++;


		setDurability(temp, max(0, 1 + getChangedSustOrDura(player, DURABILITY, getCardId(temp)) + special_durability)); 	
		setCardSustainable(temp, max(0, 1 + getChangedSustOrDura(player, SUSTAINABLE, getCardId(temp)) + special_sustainable)); 

		special_sustainable = 0;
		special_durability = 0;
	}
	
}

int getSumCardSustainable(Ensiie player, int is_round_even)
{
	List_Card list_card = getStudentPool(getBoard(player));
	Card* iterable_list = getList(list_card);

	int sum = 0;
    for (int i = 0; i < getSize(list_card); i++)
	{
		if (getCardId(iterable_list[i]) == FISE)
			sum += getCardSustainable(iterable_list[i]);		//Pour chacune des FISE on ajoute à la somme sa valeur de développement
		else if (getCardId(iterable_list[i]) == FISA && is_round_even == 0)
			sum += getCardSustainable(iterable_list[i]);		//Si le tour est impair, on ajoute à la somme la valeur de développement de la carte FISA
	}

	return sum;
}


int getSumCardDurability(Ensiie player, int is_round_even)
{
	List_Card list_card = getStudentPool(getBoard(player));
	Card* iterable_list = getList(list_card);

	int sum = 0;
    for (int i = 0; i < getSize(list_card); i++)
	{
		if(getCardId(iterable_list[i]) == FISE)
			sum += getDurability(iterable_list[i]);			//Pour chacune des FISE on ajoute à la somme sa valeur de durabilité
		else if (getCardId(iterable_list[i]) == FISA && is_round_even == 0)
			sum += getDurability(iterable_list[i]);			//Si le tour est impair, on ajoute à la somme la valeur de durabilité de la carte FISA
	}

	return sum;
}

void playDistanciation(Ensiie player)
{
	List_Card list_card = getStudentPool(getBoard(player));

	int count_fise = floor(getFiseNumber(player) / 2);
	int count_fisa = floor(getFisaNumber(player) / 2);
	int index = 0;
	int flag_count_final = 1;

	while (flag_count_final)
	{

		if (getCardId(getList(list_card)[index]) == FISE && count_fise > 0)
		{
			destroyCard(removeElement(list_card, index));
			list_card = getStudentPool(getBoard(player));
			count_fise = count_fise - 1;
			index--;
		}
		else if (getCardId(getList(list_card)[index]) == FISA && count_fisa > 0)
		{
			destroyCard(removeElement(list_card, index));
			list_card = getStudentPool(getBoard(player));
			count_fisa = count_fisa - 1;
			index--;
		}

		index++;

		if ((count_fise <= 0) && (count_fisa <= 0))
		{
			flag_count_final = 0;
		}
	}
}

void setPlayerName(Ensiie player, char* name) {
	free(player->name);
	player->name = name;
}