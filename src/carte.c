#include "../headers/carte.h"
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 30

/******************* STRUCTURE ********************/
/** @struct Card 
 * 	@brief Structure de carte du jeu
 *  Une carte possède plusieurs attributs : un type, un ID, un nom, un coût, des points de développement durable et de durabilité et des effets
 *  Le jeu possède 33 cartes dans sa version de base et une carte virtuelle de fin de phase
*/

/**Structure concrète de carte
*/
struct str_card {
	type_card type; //Card->type = STUDENT||STAFF||ACTION
	id_cardname id; //identifiant : entier ou nom
	char* name; //par exemple FISE, FISA, Alain Faye, Decharge
	int cost; //cout 
	int sustainable_points; //points de developpement durable si Eleve
	int durability_points; //points de durabilite si Eleve
	card_effect* effects; //liste des effets de la carte si Personnel ou Action
	int size_effects; //longueur de la liste des effets
	card_specialise specialisation;
	};



/******************* FONCTIONS ********************/

/** Constructeur de carte */
Card createCard(id_cardname id) {
	Card new = (Card)calloc(1, sizeof(struct str_card));
	new->id = id;
	switch(id) {
		case END_PHASE :
			new->name = "Finir Votre Phase";
			new->cost = 0; //Cette carte peut être jouée n'importe quand
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->size_effects = 0;
			new->specialisation = NOT_SPECIALISED;
			break;
		case LIM :
			new->type = STAFF;
			new->name = "Thomas LIM";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = AE1;  
			new->size_effects = 1;
			new->specialisation = MA;
			break;
		case SZAFRANSKI :
			new->type = STAFF;
			new->name = "Marie SZAFRANSKI";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = AE2;
			new->size_effects = 1;
			new->specialisation = MA;
			break;  
		case FAYE :
			new->type = STAFF;
			new->name = "Alain FAYE";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = AA1; 
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break; 
		case MOUILLERON :
			new->type = STAFF;
			new->name = "Christophe MOUILLERON";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = AA2;
			new->size_effects = 1;
			new->specialisation = HPC;
			break; 
		case DUMBRAVA :
			new->type = STAFF;
			new->name = "Stefania DUMBRAVA";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RE1; 
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;	 
		case FOREST :
			new->type = STAFF;
			new->name = "Julien FOREST";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RE2; 
			new->size_effects = 1;
			new->specialisation = GL;
			break;	 
		case BRUNEL :
			new->type = STAFF;
			new->name = "Nicolas BRUNEL";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RA1; 
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break; 
		case BOURARD :
			new->type = STAFF;
			new->name = "Laurence BOURARD";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RA2; 
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break; 
		case WATEL :
			new->type = STAFF;
			new->name = "Dimitri WATEL";
			new->cost = 5;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(2*sizeof(card_effect));
			new->effects[0] = AE1;
			new->effects[1] = AA1; 
			new->size_effects = 2;
			new->specialisation = GL;
			break;
		case Y :
			new->type = STAFF;
			new->name = "Vitera Y";
			new->cost = 5;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(2*sizeof(card_effect));
			new->effects[0] = AE2;
			new->effects[1] = AA2; 
			new->size_effects = 2;
			new->specialisation = IN;
			break;
		case GOILARD :
			new->type = STAFF;
			new->name = "Kevin GOILARD";
			new->cost = 5;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(2*sizeof(card_effect));
			new->effects[0] = RE1;
			new->effects[1] = RA1; 
			new->size_effects = 2;
			new->specialisation = IN;
			break;
		case JEANNAS :
			new->type = STAFF;
			new->name = "Vincent JEANNAS";
			new->cost = 5;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(2*sizeof(card_effect));
			new->effects[0] = RE2;
			new->effects[1] = RA2; 
			new->size_effects = 2;
			new->specialisation = NOT_SPECIALISED;
			break;
		case MERABET :
			new->type = STAFF;
			new->name = "Massinissa MERABET";
			new->cost = 7;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(2*sizeof(card_effect));
			new->effects[0] = DR;
			new->effects[1] = DR; 
			new->size_effects = 2;
			new->specialisation = NOT_SPECIALISED;
			break;
		case LIGOZAT :
			new->type = STAFF;
			new->name = "Anne-Laure LIGOZAT";
			new->cost = 8;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(4*sizeof(card_effect));
			new->effects[0] = ADD;
			new->effects[1] = ADD;
			new->effects[2] = DR;
			new->effects[3] = E; 
			new->size_effects = 4;
			new->specialisation = NOT_SPECIALISED;
			break;
		case DUBOIS :
			new->type = STAFF;
			new->name = "Catherine DUBOIS";
			new->cost = 8;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(4*sizeof(card_effect));
			new->effects[0] = RDD;
			new->effects[1] = RDD;
			new->effects[2] = DR;
			new->effects[3] = E; 
			new->size_effects = 4;
			new->specialisation = NOT_SPECIALISED;
			break;
		case LEJEUNE :
			new->type = STAFF;
			new->name = "Eric LEJEUNE";
			new->cost = 10;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(4*sizeof(card_effect));
			new->effects[0] = AE1;
			new->effects[1] = AE2;
			new->effects[2] = RE2;
			new->effects[3] = RDD; 
			new->size_effects = 4;
			new->specialisation = NOT_SPECIALISED;
			break;
		case MATHIAS :
			new->type = STAFF;
			new->name = "Christine MATHIAS";
			new->cost = 10;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(4*sizeof(card_effect));
			new->effects[0] = AA1;
			new->effects[1] = AA2;
			new->effects[2] = RA2;
			new->effects[3] = RDD; 
			new->size_effects = 4;
			new->specialisation = NOT_SPECIALISED;
			break;
		case SALHAB :
			new->type = STAFF;
			new->name = "Katrin SALHAB";
			new->cost = 15;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(5*sizeof(card_effect));
			new->effects[0] = AE1;
			new->effects[1] = AE1;
			new->effects[2] = AE2;
			new->effects[3] = AE2;
			new->effects[4] = E;
			new->size_effects = 5;
			new->specialisation = NOT_SPECIALISED;
			break;
		case SAGNA :
			new->type = STAFF;
			new->name = "Abass SAGNA";
			new->cost = 15;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(5*sizeof(card_effect));
			new->effects[0] = AA1;
			new->effects[1] = AA1;
			new->effects[2] = AA2;
			new->effects[3] = AA2;
			new->effects[4] = E;
			new->size_effects = 5;
			new->specialisation = NOT_SPECIALISED;
			break;
		case PREVEL :
			new->type = STAFF;
			new->name = "Laurent PREVEL";
			new->cost = 20;
			new->sustainable_points = 0;
			new->durability_points = 0; 
			new->effects = (card_effect*) malloc(13*sizeof(card_effect));
			new->effects[0] = AE1;
			new->effects[1] = AE1;
			new->effects[2] = AE2;
			new->effects[3] = AE2;
			new->effects[4] = AA1;
			new->effects[5] = AA1;
			new->effects[6] = AA2;
			new->effects[7] = AA2;
			new->effects[8] = ADD;
			new->effects[9] = RDD;
			new->effects[10] = DR;
			new->effects[11] = E;
			new->effects[12] = E;	
			new->size_effects = 13;
			new->specialisation = NOT_SPECIALISED;
			break;
		case SANDRINE:
			new->type = STAFF;
			new->name = "Sandrine DE L'ACCUEIL";
			new->cost = 1;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->size_effects = 0;
			new->specialisation = NOT_SPECIALISED;
			break;
		case DOSSANTOS:
			new->type = STAFF;
			new->name = "Pierre DOSSANTOS";
			new->cost = 9;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(4*sizeof(card_effect));
			new->effects[0] = AE2;
			new->effects[1] = ADD;
			new->effects[2] = DR;
			new->effects[3] = E;
			new->size_effects = 4;
			new->specialisation = HPC;
			break;
		case COURS_DD :
			new->type = ACTION;
			new->name = "Cours Developpement Durable";
			new->cost = 2;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = CDD;
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;  
		case RECRUTEMENT :
			new->type = ACTION;
			new->name = "Recrutement";
			new->cost = 2;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = REC;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;  
		case RENTREE_FISE :
			new->type = ACTION;
			new->name = "Rentree FISE";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RFISE; 
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;   
		case RENTREE_FISA :
			new->type = ACTION;
			new->name = "Rentree FISA";
			new->cost = 3;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RFISA;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;  
		case ENERGIE_VERTE :
			new->type = ACTION;
			new->name = "Energie Verte";
			new->cost = 4;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = EV;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;  
		case DIPLOMATION :
			new->type = ACTION;
			new->name = "Diplomation";
			new->cost = 5;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = DIP;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;  
		case DECHARGE :
			new->type = ACTION;
			new->name = "Decharge";
			new->cost = 5;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = DCH;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;  
		case RECYCLAGE :
			new->type = ACTION;
			new->name = "Recyclage";
			new->cost = 10;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RCY; 
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;   
		case ZERO_PAPIER :
			new->type = ACTION;
			new->name = "Zero Papier";
			new->cost = 10;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = ZPA;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;  
		case REPAS_VEGETARIEN :
			new->type = ACTION;
			new->name = "Repas vegetarien";
			new->cost = 10;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = RVG;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;
		case FERMETURE_ANNUELLE :
			new->type = ACTION;
			new->name = "Fermeture annuelle";
			new->cost = 10;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect*) malloc(sizeof(card_effect));
			new->effects[0] = FER;  
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;
		case DISTANCIATION_SOCIALE :
			new->type = ACTION;
			new->name = "Distanciation sociale";
			new->cost = 7;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect *)malloc(sizeof(card_effect));
			new->effects[0] = DIS;
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;
		case SOIREE_BDE:
			new->type = ACTION;
			new->name = "Soiree BDE";
			new->cost = 15;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect *)malloc(sizeof(card_effect));
			new->effects[0] = BDE;
			new->size_effects = 1;
			new->specialisation = NOT_SPECIALISED;
			break;
		case PARCOURS_PL:
			new->type = ACTION;
			new->name = "Parcours Libre";
			new->cost = 12;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect *)malloc(sizeof(card_effect));
			new->effects[0] = PPL;		//PLACEHOLDER
			new->size_effects = 1;
			new->specialisation = PL;
			break;
		case PARCOURS_GL:
			new->type = ACTION;
			new->name = "Parcours GL";
			new->cost = 6;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect *)malloc(sizeof(card_effect));
			new->effects[0] = PGL;		//PLACEHOLDER
			new->size_effects = 1;
			new->specialisation = GL;
			break;
		case PARCOURS_HPC :
			new->type = ACTION;
			new->name = "Parcours HPC";
			new->cost = 6;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect *)malloc(sizeof(card_effect));
			new->effects[0] = PHPC;		//PLACEHOLDER
			new->size_effects = 1;
			new->specialisation = HPC;
			break;
		case PARCOURS_MA :
			new->type = ACTION;
			new->name = "Parcours MA";
			new->cost = 6;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect *)malloc(sizeof(card_effect));
			new->effects[0] = PMA;		//PLACEHOLDER
			new->size_effects = 1;
			new->specialisation = MA;
			break;
		case PARCOURS_IN :
			new->type = ACTION;
			new->name = "Parcours IN";
			new->cost = 6;
			new->sustainable_points = 0;
			new->durability_points = 0;
			new->effects = (card_effect *)malloc(sizeof(card_effect));
			new->effects[0] = PIN;		//PLACEHOLDER
			new->size_effects = 1;
			new->specialisation = IN;
			break;
		case FISE :
			new->type = STUDENT;
			new->name = "FISE";
			new->cost = 0; // coût nul pour les cartes Eleve
			new->sustainable_points = 1;
			new->durability_points = 1;
			new->size_effects = 0;
			new->specialisation = NOT_SPECIALISED;
			break;
		case FISA : // cas restant : id_cardname = 33 : FISA
			new->type = STUDENT;
			new->name = "FISA";
			new->cost = 0; // coût nul pour les cartes Eleve
			new->sustainable_points = 1;
			new->durability_points = 1;
			new->size_effects = 0;
			new->specialisation = NOT_SPECIALISED;
			break;
	}
	return new;
}

/** Destructeur de carte */
void destroyCard(Card card) {
	// La seule entité à libérer est la liste d'effets de la carte
	if (card->id >= 1 ||  card->id <= 31) { //Seules les cartes Action et Personnel ont des effets
		free(card->effects);
	}
	free(card);
}

/** Constructeur de carte par copie **/
Card copyCard(Card source) {
	Card new = createCard(source->id);
	new->sustainable_points = source->sustainable_points;
	new->durability_points = source->durability_points;
	new->specialisation = source->specialisation;
	return new;
}

/** Quantité de cartes à ajouter au deck au début du jeu **/
int initiateQuantity(id_cardname id) {
	switch(id) {
		case COURS_DD : return 3; 
		case RECRUTEMENT : return 3; 
		case RENTREE_FISE : return 2; 
		case RENTREE_FISA : return 2; 
		case ENERGIE_VERTE : return 2; 
		case DIPLOMATION : return 2; 
		case DECHARGE : return 4; 
		default : return 1; //Carte Personnel, Recyclage, Zéro papier, Repas végétarien et Fermeture annuelle
	}
}

/** Test de fin de phase **/
int isEndPhaseCard(Card card) {
	return card->id == 0;
}

/********************* ACCESSEURS EN LECTURE ***************************/
/** Récupération du type d'une carte **/
type_card getType(Card card) {
	return card->type;
}

/** Récupération de l'id d'une carte **/
id_cardname getCardId(Card card) {
	return card->id;
}

/** Récupération du nom d'une carte **/
char* getName(Card card) {
	return card->name;
}

/** Récupération du coût en PE d'une carte **/
int getPE(Card card) {
	return card->cost;
}

/** Récupération des points de développement durable d'une carte **/
int getCardSustainable(Card card) {
	return card->sustainable_points;
}

/** Récupération des points de durabilité d'une carte **/
int getDurability(Card card) {
	return card->durability_points;
}

/** Récupération des effets d'une carte **/
card_effect* getEffects(Card card) {
	return card->effects;
}

/** Récupération de la longueur de la liste des effets d'une carte **/
int getSizeEffects(Card card){
	return card->size_effects;
}

card_specialise getSpecialisation(Card card)
{
	return card->specialisation;
}

void setDurability(Card card, int value){
	card->durability_points = value;
}

void setCardSustainable(Card card, int value){
	card->sustainable_points = value;
}

/** Ajout de value points aux points de durabilité de la carte card **/
void addDurability(Card card, int value){
	setDurability(card, getDurability(card)+abs(value));
}

/** Ajout de value points aux sustainable_points de la carte card **/
void addCardSustainable(Card card, int value){
	setCardSustainable(card, getCardSustainable(card)+abs(value));
}

/** Retrait de value points aux points de durabilité de la carte card **/
void removeDurability(Card card, int value){
	setDurability(card, getDurability(card)-abs(value));
}
/** Retrait de value points aux sustainable_points de la carte card**/
void removeCardSustainable(Card card, int value){
	setCardSustainable(card, getCardSustainable(card)-abs(value));
}

void setSpecialisation(Card card, card_specialise special)
{
	if(card->specialisation == NOT_SPECIALISED && special > NOT_SPECIALISED && special <= IN)
		card->specialisation = special;
}





