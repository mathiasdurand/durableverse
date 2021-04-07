#ifndef _CARTE_H_
#define _CARTE_H_

#include "utils.h"

/** @file carte.h
 * 	@brief Gestion du type carte 
 *	@author Maureen Lachaize	
*/

/******************* TYPES ET STRUCTURES ********************/
/** @enum type_card
	@brief Type d'une carte : Eleve, Personnel ou Action
*/
typedef enum type_card { STUDENT, STAFF, ACTION } type_card;

/** @enum card_effect
 * 	@brief Effets des cartes Personnel et Action
 */
typedef enum card_effect { AE1, AE2, AA1, AA2
						 , RE1, RE2, RA1, RA2
						 , ADD, RDD, DR, E
						 , CDD, REC, RFISE, RFISA
						 , EV, DIP, DCH, RCY
						 , ZPA, RVG, FER, DIS, BDE
						 , PPL, PGL, PHPC, PMA, PIN } card_effect;

/** @enum id_cardname
 * 	@brief Relation entre l'id d'une carte et son nom
 * 	L'id d'une carte est compris entre 0 et 33, de 1 à 20 : cartes Personnels,
 *	de 21 à 31 : cartes Action, 32 : FISE, 33 : FISA et 0 : carte virtuelle de fin de phase
 */
typedef enum id_cardname {END_PHASE, 
	LIM, SZAFRANSKI, FAYE, MOUILLERON, DUMBRAVA, FOREST, BRUNEL, BOURARD, WATEL, Y, GOILARD, JEANNAS, MERABET, LIGOZAT, DUBOIS, LEJEUNE, MATHIAS, SALHAB, SAGNA, PREVEL, SANDRINE, DOSSANTOS,
	COURS_DD, RECRUTEMENT, RENTREE_FISE, RENTREE_FISA, ENERGIE_VERTE, DIPLOMATION, DECHARGE, RECYCLAGE, ZERO_PAPIER, REPAS_VEGETARIEN, FERMETURE_ANNUELLE, DISTANCIATION_SOCIALE, SOIREE_BDE, PARCOURS_PL, PARCOURS_GL, PARCOURS_HPC, PARCOURS_MA, PARCOURS_IN,
	FISE, FISA
	} id_cardname;

/** @enum card_specialise
 *  @brief Spécialisation des élèves et profs 
 */
typedef enum card_specialise {NOT_SPECIALISED, PL, GL, HPC, MA, IN} card_specialise;

/** @typedef Card
 * 	@brief Définition abstraite de la structure correspondant à une carte
 */
typedef struct str_card* Card;

/******************* FONCTIONS ********************/
/**	@fn Card createCard(int id)
 * 	@brief Constructeur de carte
	@param id_cardname Id de la carte sous forme d'un entier ou du nom
	@return Instance nouvellement allouée de type Card, correspondant à id  
*/
Card createCard(id_cardname id);

/** @fn void destroyCard(Card card)
 * 	@brief Destructeur de carte
	@param card Une carte du jeu
*/
void destroyCard(Card card);

/** @fn Card copyCard(Card source)
 * 	@brief Constructeur de carte par copie
 * 	@param source Une carte du jeu
 * 	@return Instance nouvellement allouée de type Card, identique à source
*/
Card copyCard(Card source);

/** @fn int initiateQuantity(int id)
 * 	@brief Fonction qui renvoie la quantité d'une carte à ajouter au deck au début du jeu
 * 	@param id Id d'une carte Personnel ou Action, soit un id entre 1 et 31
 * 	@return La quantité de cartes d'ID id à glisser dans le deck d'un joueur au début du jeu
*/
int initiateQuantity(id_cardname id);

/**	@fn int isEndPhaseCard(Card card)
 * 	@brief Fonction qui teste la fin de la phase en cours
 * 	On décide d'ajouter une carte virtuelle fin de phase au jeu, toujours présente dans la main du joueur 
	@param card Une carte du jeu
	@return 1 si card est la carte fin de phase et 0 sinon*/
int isEndPhaseCard(Card card);

/********************* ACCESSEURS EN LECTURE ***************************/
/** @fn type_card getType(Card card)
 * @brief Accesseur en lecture du type d'une carte
 * @param card Une carte du jeu
 * @return Le type de la carte : Personnel, Etudiant ou Action
*/
type_card getType(Card card);

/** @fn id_cardname getCardId(Card card);
 * 	@brief Accesseur en lecture de l'id d'une carte
 *  @param card Une carte du jeu
 *	@return L'ID de la carte
*/
id_cardname getCardId(Card card);

/**	@fn char* getName(Card card)
 * 	@brief Accesseur en lecture du nom d'une carte
 * 	@param card Une carte du jeu
 * 	@return Le nom de la carte (ex: Alain Faye, FISE, Recyclage)
*/
char* getName(Card card);

/** @fn int getPE(Card card)
 * 	@brief Accesseur en lecture du coût en PE d'une carte
 * 	@param card Une carte du jeu
 * 	@return Le coût en PE de la carte
*/
int getPE(Card card);

/** @fn int getCardSustainable(Card card)
 * 	@brief Accesseur en lecture des points de développement durable d'une carte
 * 	@param card Une carte du jeu
 *  @return Le nombre de points de développement durable de la carte
*/
int getCardSustainable(Card card);

/** @fn int getDurability(Card card)
 * 	@brief Accesseur en lecture des points de durabilité d'une carte
 *  @param card Une carte du jeu
 * 	@return Le nombre de points de durabilité de la carte
*/
int getDurability(Card card);

/** @fn card_effect* getEffects(Card card)
 * 	@brief Accesseur en lecture des effets d'une carte
 * 	@param card Une carte du jeu
 * 	@return La liste des effets de la carte
*/ 
card_effect* getEffects(Card card);

/** @fn int getSizeEffects(Card card);
 * 	@brief Accesseur en lecture de la longueur de la liste des effets d'une carte
 * 	@param card Une carte du jeu
 * 	@return La longueur de la liste des effets de la carte
*/ 
int getSizeEffects(Card card);

/** @fn card_specialise getSpecialisation(Card card)
 * 	@brief Accesseur en lecture de la spécialisation d'une carte
 * 	@param card Une carte du jeu valide
 * 	@return Renvoie la spécialisation d'une carte (avec l'énum correspondant)
 * 	@author Alex Danduran--Lembezat
 */
card_specialise getSpecialisation(Card card);

/********************* ACCESSEURS EN ECRITURE ***************************/
/** @fn void setDurability(Card card, int value)
 *  @brief Accesseur en écriture du nombre de points de durabilité de la carte
 *  @param card une carte du jeu 
 * 	@param value l'entier  correspondant à la valeur voulue de durability
 */
void setDurability(Card card, int value);

/** @fn void setCardSustainable(Card card, int value)
 *  @brief Accesseur en écriture du nombre de points de sustainable_points de la carte
 *  @param card une carte du jeu 
 * 	@param value l'entier correspondant à la valeur voulue de sustainable_points
 */
void setCardSustainable(Card card, int value);

/** @fn void addDurability(Card card, int value)
 *  @brief Modification en écriture du nombre de points de durabilité de la carte
 *  @param card une carte du jeu 
 * 	@param value l'entier correspondant à la valeur à ajouter à la durabilité
 */
void addDurability(Card card, int value);

/** @fn void addCardSustainable(Card card, int value)
 *  @brief Modification en écriture du nombre de points de sustainable_points de la carte
 *  @param card une carte du jeu 
 * 	@param value l'entier correspondant à la valeur à ajouter à sustainable_points
 */
void addCardSustainable(Card card, int value);

/** @fn void removeDurability(Card card, int value)
 *  @brief Modification en écriture du nombre de points de durabilité de la carte (moins)
 *  @param card une carte du jeu 
 * 	@param value l'entier correspondant à la valeur à retirer à la durabilité
 */
void removeDurability(Card card, int value);

/** @fn void removeCardSustainable(Card card, int value)
 *  @brief Modification en écriture du nombre de points de sustainable_points de la carte (moins)
 *  @param card une carte du jeu 
 * 	@param value l'entier correspondant à la valeur à retirer à sustainable_points
 */
void removeCardSustainable(Card card, int value);

/** @fn void setSpecialisation(Card card, card_specialise special)
 * 	@brief Mutateur de la spécialisation d'une carte
 * 	@param card Une carte du jeu valide
 * 	@param special Une spécialisation valide (provenant de l'enum card_specialise)
 * 	@author Alex Danduran--Lembezat
 */
void setSpecialisation(Card card, card_specialise special);

#endif
