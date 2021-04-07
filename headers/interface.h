#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "joueur.h"

/** @file interface.h
 * 	@brief Gestion de l'interface en console
 *	@author Mathias DURAND
*/


//----------------------------------------
//FONCTIONS DE DEMANDES À L'UTILISATEUR

/**
 * @fn int whichStudent()
 * @brief Demande au joueur quel type de carte élève il souhaite prendre
 * @return renvoie 0 s'il choisit une FISE, 1 si il choisit une FISA
*/
int whichStudent();

/**
 * @fn Card askCard(Ensiie player)
 * @brief Réalise un appel à printHand pour les cartes dont le cout est inférieur au PE
		Demande si le joueur veut jouer une carte et, dans ce cas, quelle carte le joueur souhaite
          jouer et renvoie la carte (card) choisie par le joueur (renvoie une carte "default" (définie à l'avance avec un id=0)
          si le joueur n'en choisit aucune). Informe également le joueur s'il ne dispose pas d'assez de PE.
 * @param player un joueur valide (possèdant une liste de carte à jouer (une main))
 * @return la carte que le joueur désire jouer
*/
Card askCard(Ensiie player);

//----------------------------------------
//FONCTIONS D'AFFICHAGE

/**
 * @fn void printNotEnoughPE()
 * @brief Imprime sur le flux de sortie un message d'erreur. Utilisée lorsque le joueur souhaite jouer une carte dont le coût dépasse son nombre de PE
*/
void printNotEnoughPE();

/**
 * @fn void printStateOfGame(Ensiie player1, Ensiie player2, int round)
 * @brief Affiche l'état actuel du jeu : le plateau avec les cartes Eleve et Personnel
 * @param player1 un joueur valide
 * @param player2 un joueur valide 
 * @param round le numéro du tour
*/
void printStateOfGame(Ensiie player1, Ensiie player2, int round);

/**
 * @fn void printHand(List_Card* hand, int energy)
 * @brief Imprime sur le flux de sortie standard les cartes de la main passée en paramètre dont le coût est inférieur aux PE.
 * @param list_hand une liste de cartes (card) valide : la main et un entier : le nombre de PE pour afficher que les cartes dont le coût est inférieur au nombre de PE
*/
void printHand(List_Card list_hand, int energy);

/**
 * @fn void printListCard(List_Card* liste_cartes)
 * @brief Imprime sur le flux de sortie standard le contenu de la liste de carte passée en paramètre
 * @param liste_cartes une liste de cartes (card) valide 
 * */
void printListCard(List_Card liste_cartes);

/**
 * @fn void printGraveyard(List_Card* graveyard)
 * @brief Imprime sur le flux de sortie le contenu de la pile de défausse passée en paramètre
		En pratique, réalise un appel à la fonction printListCard.
 * @param graveyard une liste de cartes (card) : la pile de défausse
*/
void printGraveyard(List_Card graveyard);

/**
 * @fn void printStudentPool(List_Card pool, int round)
 * @brief Imprime sur le flux de sortie le contenu de la liste de cartes élèves "pool" (particularité : affiche les sustainable_points et durability_points)
 * affiche egalement les cartes FISA comme non jouables en tour pair
 * @param pool une liste de cartes (card) : la liste de cartes élèves
 * @param round entier désignant le numéro du tour
*/
void printStudentPool(List_Card pool, int round);

//----------------------------------------
//FONCTIONS D'INFORMATION SUR L'ÉTAT DU JEU

/**
 * @fn void printEndGame(game_status status)
 * @brief Imprime sur le flux de sortie le vainqueur de la partie ou l'égalité le cas écheant, le numéro du tour et les points DD de chaque ENSIIE.
 * @param status la valeur correspondant à si le joueur 1 a gagné, le joueur 2 ou bien égalité. Il faut status != 0:
 *        1 si le joueur 1 a gagné
 *        2 si le joueur 2 a gagné
 *        3 si il y a égalité
 * @param player1 le premier joueur du jeu
 * @param player2 le second joueur du jeu
*/
void printEndGame(int status, Ensiie player1, Ensiie player2);

/**
 * @fn void printNewRound(int round)
 * @brief Imprime sur le flux de sortie qu'un nouveau tour vient de débuter et 
          indique le numéro du tour ainsi que d'autres informations utiles 
          (par exemple la présence ou non d'un nouvel élément "Personnel")
 * @param round un entier
*/
void printNewRound(int round);

/**
 * @fn void printNewPhase(Ensiie current_player, Ensiie player1)
 * @brief Imprime sur le flux de sortie qu'une nouvelle phase vient de débuter et indique l'ENSIIE associée à cette phase
 * @param player1 le premier joueur du jeu
 * @param player2 le second joueur du jeu
*/
void printNewPhase(Ensiie player1, Ensiie player2);

/** 
 * @fn void printNewGame(Ensiie player1, Ensiie player2)
 * @brief Imprime sur le flux de sortie qu'une nouvelle partie commence et demande aux joueurs leurs noms
 * @param player1 le premier joueur du jeu
 * @param player2 le second joueur du jeu
*/
void printNewGame(Ensiie player1, Ensiie player2);

#endif
