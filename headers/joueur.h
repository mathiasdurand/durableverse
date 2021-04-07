#ifndef _JOUEUR_H
#define _JOUEUR_H

#include "plateau.h"

/** @file joueur.h
 * 	@brief Gestion des joueurs
 *	@author Alex Danduran--Lembezat	
*/

/******************* TYPES ET STRUCTURES ********************/
/** @enum sust_or_dura
 *  @brief Permet de rendre plus lisible l'appel aux fonctions changeSustOrDura(...), getChangedSustOrDura(...) et updateSustAndDura(...)
 */
typedef enum sust_or_dura {SUSTAINABLE, DURABILITY} sust_or_dura;

/** @typedef Ensiie
 * 	@brief Définition abstraite de la structure correspondant à un joueur
 */

typedef struct str_ensiie* Ensiie;

/**************** CONSTRUCTEUR ET DESTRUCTEUR ****************/
/**
 * @fn Ensiie createEnsiie()
 * @brief Constructeur de ensiie
 * @return Une ensiie en situation initiale :
		0 points de developpement durable,
		un deck vide,
		une main vide,
		un plateau vide,
		0 PE,
		une defausse vide.
*/
Ensiie createEnsiie();

/**
 * @fn void destroyEnsiie(Ensiie player)
 * @brief Destructeur de ensiie
 * @param player une ensiie a ete creee
 * @author Sirine HAMDANA
*/
void destroyEnsiie(Ensiie player);

/**
 * @fn void initiateEnsiie(Ensiie player)
 * @brief Initialisation de ensiie : initialise la pioche
 * @param player une ensiie a ete creee
*/
void initiateEnsiie(Ensiie player);


/**************** ACTIONS SUR LES CARTES ****************/
/**
 * @fn void drawEnsiie(Ensiie player)
 * @brief Piocher une carte : le joueur pioche une carte
 * @param player une ensiie valide
*/
void drawEnsiie(Ensiie player);

/**
 * @fn void addEleve (int eleve, Ensiie player)
 * @brief Ajout d'une carte Eleve sur le plateau d'une ENSIIE (FISE ou FISA en fonction de l'identifiant)
 * @param player une ensiie valide,
 * @param id l'identifiant de la carte FISE ou FISA
*/
void addEleve (id_cardname id, Ensiie player);

/**
 * @fn int numberEleve(Ensiie player)
 * @brief Calcul du nombre de cartes Eleve reçue en début de phase 
 * @param player le joueur courant
 * @return le nombre de cartes Eleve que player doit recevoir au debut de sa phase*/
int numberEleve(Ensiie player);

/**
 * @fn void addAdditionalStudent(Ensiie player, int amount)
 * @brief Augmente d'une quantité donnée le nombre de carte Eleve à piocher au début du tour suivant
 * @param player une ensiie valide
 * @param amount un entier positif
*/
void addAdditionalStudent(Ensiie player, int amount);

/**
 * @fn int numberCard(Ensiie player)
 * @brief Renvoie combien de cartes player doit piocher en debut de phase et réinitialise le compteur de cartes additionnelles à ajouter
 * @param player une ensiie valide
 * @return le nombre de cartes que doit piocher player au debut de sa phase
*/
int numberCard(Ensiie player);

/**
 * @fn void addAdditionalCard(Ensiie player, int amount)
 * @brief Augmente d'une quantité donnée le nombre de carte à piocher au début du tour suivant
 * @param player une ensiie valide
 * @param amount un entier positif
*/
void addAdditionalCard(Ensiie player, int amount);

/**
 * @fn int isInHand(Ensiie player, Card card)
 * @brief Teste si une carte est dans la main d'un joueur
 * @param player le joueur courant
 * @return 1 si card est dans la main de player et 0 sinon*/
int isInHand(Ensiie player, Card card);


/**************** ENERGIE ****************/

/** 
 * @brief Ajoute des points d'énergie à un joueur
 * @param player un joueur bien initialisé
 * @param energy la quantité d'énergie à ajouter
 * @author Alex Danduran--Lembezat
 */
void addEnergy (Ensiie player, int energy);

/** 
 * @brief Retire des points d'énergie à un joueur
 * @param player un joueur bien initialisé
 * @param energy la quantité d'énergie à retirer
 * @author Alex Danduran--Lembezat
 */
void removeEnergy(Ensiie player, int energy);

/** 
 * @brief Accesseur en lecture de l'énergie du joueur 
 * @param player un joueur bien initialisé
 * @return L'énergie du joueur en question
 * @author Alex Danduran--Lembezat
 */
int getEnergy(Ensiie player);

/** 
 * @brief Mutateur du nombre de point d'énergie d'un joueur
 * @param player un joueur bien initialisé
 * @param energy la quantité d'énergie à mettre
 * @author Alex Danduran--Lembezat
 */
void setEnergy(Ensiie player, int energy);

/** 
 * @brief Doit être appelé après la fonction addEleve(). Permet de compter le nombre de points d'énergie dispobible au joueur au début de sa phase en fonction du tour courant et des cartes élève qu'il possède
 * @param player un joueur bien initialisé
 * @param round le numéro du tour courant
 * @author Alex Danduran--Lembezat
 */
void countEnergy(Ensiie player, int round);

/** 
 * @fn int enoughEnergy(Ensiie player, Card card)
 * @brief Renseigne si oui ou non un joueur a suffisemment d'énergie pour jouer une carte donnée
 * @param player un joueur bien initialisé
 * @param card la carte qu'il souhaite jouer
 * @author Alex Danduran--Lembezat
 */
int enoughEnergy(Ensiie player, Card card);

/********************* ACCESSEURS EN LECTURE ***************************/
/** 
 * @brief Récupère le nom du joueur spécifié
 * @param joueur joueur dont on veut le nom
 * @return Le nom du joueur
 */
char* getPlayerName(Ensiie player);
/** 
 * @brief Récupère la liste des cartes du deck d'un joueur spécifié
 * @param joueur joueur dont on veut le deck
 * @return Le deck du joueur
 */
List_Card getDeck(Ensiie player);

/** 
 * @brief Récupère la liste des cartes en main d'un joueur spécifié
 * @param player joueur dont on veut la main
 * @return La main du joueur
 */
List_Card getHand(Ensiie player);

/** 
 * @brief Récupère la liste des cartes correspondant à la défausse d'un joueur spécifié
 * @param player joueur dont on veut la défausse
 * @return La défausse du joueur
 */
List_Card getGraveyard(Ensiie player);

/** 
 * @brief Récupère le nombre de carte FISE placées sur le plateau du joueur spécifié
 * @param player joueur dont on veut le nombre de carte FISE
 * @return Le nombre de carte FISE placées sur le plateau d'un joueur
 */
int getFiseNumber(Ensiie player);

/** 
 * @brief Récupère le nombre de carte FISA placées sur le plateau du joueur spécifié
 * @param player joueur dont on veut le nombre de carte FISA
 * @return Le nombre de carte FISA placées sur le plateau d'un joueur
 */
int getFisaNumber(Ensiie player);

/** 
 * @brief Accesseur en lecture des points de développement durable d'un joueur
 * @param player un joueur bien initialisé
 * @return Les points de développement durable du joueur
 */
int getPlayerSustainablePoints(Ensiie player);

/** 
 * @fn void addPlayerSustainablePoints(Ensiie player, int points)
 * @brief Permet d'ajouter des points de DD à un joueur
 * @param player un joueur bien initialisé
 * @param points le nombre de points à ajouter
 */
void addPlayerSustainablePoints(Ensiie player, int points);

/** 
 * @brief Accesseur en lecture des points supplémentaires de développement durable d'un joueur
 * @param player un joueur bien initialisé
 * @return Les points de développement durable supplémentaires du joueur
 */
int getAdditionalSustainablePoints(Ensiie player);

/** 
 * @fn void addAdditionalSustainablePoints(Ensiie player, int points)
 * @brief Permet d'ajouter des points de DD supplémentaires à la fin du tour à un joueur
 * @param player un joueur bien initialisé
 * @param points le nombre de points à ajouter
 */
void addAdditionalSustainablePoints(Ensiie player, int points);

/** 
 * @fn void removeAdditionalSustainablePoints(Ensiie player, int points)
 * @brief Permet de retirer des points de DD parmis les points supplémentaires à la fin du tour à un joueur
 * @param player un joueur bien initialisé
 * @param points le nombre de points à retirer
 */
void removeAdditionalSustainablePoints(Ensiie player, int points);

/** 
 * @brief Accesseur du plateau d'un joueur
 * @param player Le joueur bien initialisé dont on veut le plateau
 * @return Renvoie le plateau du joueur
 */
Board getBoard(Ensiie player);

/** 
 * @brief Permet de savoir si oui ou non c'est au tour du joueur en question de jouer
 * @param player Joueur bien initialisé
 * @return Renvoie 1 si le joueur est le joueur en cours et 0 sinon
 */
int isCurrentPlayer(Ensiie player);

/** 
 * @fn void setIsCurrentPlayer(Ensiie player, int valeur)
 * @brief Mutateur de la variable is_current_player qui renseigne si le joueur en question est le joueur courant
 * @param player Joueur bien initialisé
 */
void setIsCurrentPlayer(Ensiie player, int valeur);


/** 
 * @fn void changeSustOrDura(Ensiie player, sust_or_dura dura_or_sust, id_cardname id, int value)
 * @brief Permet de changer de manière persistante la durabilité ou le développement des cartes FISE ou FISA pour un joueur
 * @param player Joueur bien initialisé dont on veut altérer les statistiques des cartes
 * @param dura_or_sust DURABILITY si on veut changer la durabilité et SUSTAINABLE si on veut changer le développement
 * @param id FISE si on veut modifier les statistiques des cartes FISE et FISA pour celles des cartes FISA
 * @param value (Peut être négatif). La valeur donnant de combien on veut modifier les statistiques
 */
void changeSustOrDura(Ensiie player, sust_or_dura dura_or_sust, id_cardname id, int value);

/** 
 * @fn int getChangedSustOrDura(Ensiie player, sust_or_dura dura_or_sust, id_cardname id)
 * @brief Permet de récupérer la quantité de modification des statistiques des cartes en fonction de si on veut la durabilité ou le développement pour un FISE ou un FISA
 * @param player Joueur bien initialisé dont on veut récupérer les statistiques des cartes
 * @param dura_or_sust DURABILITY si on veut récupérer la durabilité et SUSTAINABLE si on veut récupérer le développement
 * @param id FISE si on veut récupérer les statistiques des cartes FISE et FISA pour celles des cartes FISA
 * @return (Peut être négatif). Retourne la quantité de modification des statistiques
 */
int getChangedSustOrDura(Ensiie player, sust_or_dura dura_or_sust, id_cardname id);

/** 
 * @fn void updateSustAndDura(Ensiie player)
 * @brief Permet de mettre à jour la durabilité et le développement de toutes les cartes Eleve du joueur donné
 * @param player Joueur bien initialisé dont on veut mettre à jour les statistiques de carte
 */
void updateSustAndDura(Ensiie player);

/** 
 * @fn void upgradeCardSustainable(Ensiie player)
 * @brief Permet de signifier l'amélioration des cartes Elèves pour qu'elles aient 1 point de développement en plus dès leur arrivée sur le plateau
 * @param player Joueur bien initialisé
 */
void upgradeCardSustainable(Ensiie player);


/** 
 * @fn int getUpgradedCardSustainable(Ensiie player)
 * @brief Accesseur de la variable upgraded_cards_durability qui renseigne si les nouvelles cartes élèves doivent êtres améliorées
 * @param player Joueur bien initialisé
 * @return 1 si la carte doit être améliorée, 0 sinon
 */
int getUpgradedCardSustainable(Ensiie player);


/** 
 * @fn void upgradeCardDurability(Ensiie player)
 * @brief Permet de signifier l'amélioration des cartes Elèves pour qu'elles aient 1 point de durabilité en plus dès leur arrivée sur le plateau
 * @param player Joueur bien initialisé
 */
void upgradeCardDurability(Ensiie player);



/** 
 * @fn int getUpgradedCardDurability(Ensiie player)
 * @brief Accesseur de la variable upgraded_cards_sustainable qui renseigne si les nouvelles cartes élèves doivent êtres améliorées
 * @param player Joueur bien initialisé
 * @return 1 si la carte doit être améliorée, 0 sinon
 */
int getUpgradedCardDurability(Ensiie player);


/** 
 * @fn int getSumCardSustainable(Ensiie player, int is_round_even)
 * @brief Renvoie la somme des points de développement des cartes Elève
 * @param player Joueur bien initialisé
 * @param is_round_even 1 si le tour est pair, 0 s'il est impair
 * @return Somme des points de développement des cartes Elèves FISE si tour impair et FISE + FISA si tour pair
 */
int getSumCardSustainable(Ensiie player, int is_round_even);

/** 
 * @fn int getSumCardDurability(Ensiie player, int is_round_even)
 * @brief Renvoie la somme des points de durabilité des cartes Elève
 * @param player Joueur bien initialisé
 * @param is_round_even 1 si le tour est pair, 0 s'il est impair
 * @return Somme des points de durabilité des cartes Elèves FISE si tour impair et FISE + FISA si tour pair
 */
int getSumCardDurability(Ensiie player, int is_round_even);

/** 
 * @fn void playDistanciation(Ensiie player)
 * @brief Retire la moitié des cartes FISE et des cartes FISA du plateau
 * @param player Joueur bien initialisé
 */
void playDistanciation(Ensiie player);

/** 
 * @brief Change le nom du joueur spécifié
 * @param joueur joueur dont on veut changer le nom
 * @param name le nom à donner au joueur
 */
void setPlayerName(Ensiie player, char* name);

#endif
