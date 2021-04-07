#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "carte.h"

/** @file structure.h
 * 	@brief Gestion des listes de cartes
 *	@author Sirine Hamdana	
*/

/******************* TYPES ET STRUCTURES ********************/
/** @typedef List_Card
 *  @brief  Type liste de cartes, permettant d'implémenter la main, la pioche, la défausse, 
 *  les cartes élèves et les cartes personnels en jeu
 *  Définition abstraite de la structure correspondant à une liste de cartes
*/
typedef struct str_list_card* List_Card;

/******************* FONCTIONS ********************/
/** @fn List_Card createListCard()
 *  @brief Constructeur de liste de cartes
 *  @return Cree une liste de cartes et la renvoie
*/
List_Card createListCard();

/** @fn void destroyListCard(List_Card list_card)
 *  @brief Destructeur de liste de cartes 
 *  @param list_card une liste de cartes valide à détruire	
*/
void destroyListCard(List_Card list_card);


/** @fn void destroyElements(Card* list, int size)
 *  @brief Permet de détruire tous les éléments d'une liste itérable
 *  @param list le pointeur vers le premier élément de la liste de carte
 *  @param size l'entier correspondant à la taille de cette liste
 */
void destroyElements(Card* list, int size);

/** @fn Card removeElement(List_Card list_card, int index)
 *  @brief Supprime une carte d'une List_Card
 *  @param list_card Une liste de cartes valide
 *  @param index Un entier 
 *  @return La carte situee a l'indice index de list_card, 
 *  Si index est négatif ou plus grand que la taille de la liste, renvoie NULL
*/
Card removeElement(List_Card list_card, int index);

/** @fn void addElement(List_Card list_card, Card card)
 *  @brief Ajoute une carte à la fin d'une liste de cartes
 *  @param card Une carte valide
 *  @param list_card Une liste de cartes valide
*/
void addElement(List_Card list_card, Card card);

/** @fn void addAndSort(List_Card list_card, Card card)
 *  @brief Ajoute une carte à une liste et trie la liste
 *  @param card Une carte valide
 *  @param list_card Une liste de cartes valide
*/
void addAndSort(List_Card list_card, Card card);

/** @fn void shuffle(List_card list_card)
 *  @brief Mélange une liste de cartes
 *  @param list_card Une liste de cartes valide
*/
void shuffle(List_Card list_card);

/** @fn int exists(List_card list_card, Card card)
 *  @brief Renseigne le nombre d'occurrences d'une carte donnée dans une liste de cartes
 *  @param list_card Une liste de carte valide
 *  @param card Une carte valide
 *  @return Le nombre d'occurences de card dans la liste 
*/
int exists(List_Card list_card, Card card);

/** @fn void displaceElement(Card card, List_Card original_list, List_Card destination_list)
 *  @brief Déplace une carte donnée depuis sa liste d'origine vers une liste de destination
 *  @param card Une carte valide
 *  @param original_list Une liste de cartes valide dans laquelle se trouve la carte
 *  @param destination_list Une liste de cartes valide dans laquelle on veut déplacer la carte
*/
void displaceElement(Card card, List_Card original_list, List_Card destination_list);

/********************* ACCESSEURS EN LECTURE ***************************/
/** @fn List_Card getList(List_Card list_card)
 *  @brief Accesseur en lecture de la liste de cartes
 *  @param list_card Une liste de cartes valide
 *  @return La liste de cartes
*/
Card* getList(List_Card list_card);

/** @fn int getSize(List_Card list_card);
 *  @brief Accesseur en lecture de la taille de la liste de cartes
 *  @param list_card Une liste de cartes valide
 *  @return La taille de la liste de cartes
*/
int getSize(List_Card list_card);

#endif
