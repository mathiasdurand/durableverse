#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "structure.h"

/** @file plateau.h
 * 	@brief Gestion du plateau
 *	@author Alex Danduran--Lembezat	
*/

/******************* TYPES ET STRUCTURES ********************/
/** @typedef Board
 *  @brief Type plateau, chaque joueur a son propre plateau
 *  Qui est composé des cartes Eleve et des cartes Personnel en jeu
 *  Définition abstraite de la structure correspondant à un plateau
 * */
typedef struct str_board* Board;

/*********************** FONCTIONS ************************/
/**
 * @fn Board createBoard()
 * @brief Constructeur de plateau : cree un plateau et l'initialise comme vide avec 1 emplacement pour une carte Personnel
 * @return Le plateau cree
*/
Board createBoard();

/**
 * @fn void destroyBoard(Board b)
 * @brief Destructeur de plateau 
 * @param b Un plateau valide
*/
void destroyBoard(Board b);


/** 
 * @fn void updateUnlockedSpots(Board board, int round)
 * @brief Met à jour le nombre d'emplacement de cartes Personnels disponibles en fonction du nombre de tour écoulé
 * @param board Plateau de jeu d'un joueur bien initialisé
 * @param round Numéro du actuelle du tour de jeu
 */
void updateUnlockedSpots(Board board, int round);

/********************* ACCESSEURS EN LECTURE ***************************/
/** 
 * @fn List_Card getStudentPool(Board board)
 * @brief Renseigne l'ensemble des cartes Elève en place sur le plateau d'un joueur donné
 * @param board Le plateau d'un joueur bien initialisé
 * @return La liste des cartes de type Elève d'un joueur posées sur son plateau
 */
List_Card getStudentPool(Board board);

/** 
 * @fn List_Card getStaffPool(Board board)
 * @brief Renseigne l'ensemble des cartes Personnels en place sur le plateau
 * @param board Le plateau d'un joueur bien initialisé
 * @return La liste des cartes de type Personnels d'un joueur posées sur son plateau
 */
List_Card getStaffPool(Board board);

/** 
 * @fn unsigned int getUnlockedSpotNumber(Board board)
 * @brief Renvoie le nombre d'emplacement Personnels débloqué (varie en 1 et 3) 
 * @param board Plateau de jeu d'un joueur bien initialisé
 * @return Nombre d'emplacement Personnels débloqué
 */
unsigned int getUnlockedSpotNumber(Board board);

/** 
 * @fn int getAvailableSpotNumber(Board board)
 * @brief Renvoie le nombre d'emplacement Personnels disponible
 * @param board Plateau de jeu d'un joueur bien initialisé
 * @return Nombre d'emplacement Personnels disponible
 */
int getAvailableSpotNumber(Board board);

/** 
 * @fn int isStaffSpecialised(Board board, card_specialise specialisation)
 * @brief Renvoie si oui ou non il existe au moins une carte Personnel sur le plateau avec une spécialisation donnée
 * @param board Plateau de jeu d'un joueur bien initialisé
 * @param specialisation Un spécialisation valide
 * @return 1 si il existe une carte Personnel posée avec la spécialisation donnée, 0 sinon
 */
int isStaffSpecialised(Board board, card_specialise specialisation);


#endif
