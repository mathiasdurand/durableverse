#ifndef _JEU_H_
#define _JEU_H_

#include "joueur.h"
#include "interface.h"

/** @file jeu.h
 * 	@brief Gestion du jeu 
 *	@author Sirine HAMDANA	
*/

/** @enum game_status
 * 	@brief Différents états possibles du jeu : en cours, un gagnant, égalité ou match nul
 * */
typedef enum game_status {NOT_FINISHED, ONE_WINNER, TWO_WINNER, DRAW} game_status;


/********************** STRUCTURE ***********************/
/** @typedef Game
 *  @brief Définition abstraite de la structure correspondant à une partie
 * */
typedef struct str_game* Game;



/********************** FONCTIONS ***********************/
/**
 * @fn Game createGame()
 * @brief Constructeur de partie
 * @return cree une partie 
	- Génère chaque ENSIIE (player1->is_current_player à 1 et
							player2->is_current_player à 0) 
							donc par défaut player1 est le joueur courant
	- Initialise nombre de tour (initialisé à 0)
	- Initialise numéro de phase (0)
*/
Game createGame();

/**
 * @fn void destroyGame(Game game)
 * @brief Destructeur de partie : la partie est liberee
 * @param game la partie a detruire
*/
void destroyGame(Game game);

/* Fonctions sur les plateaux */

/**
 * @fn Board newRound(Game game)
 * @brief Début d'un nouveau tour : mise a jour les espaces disponibles pour les cartes Personnel
 * @param game qui a été créé et initialisé
*/
void newRound(Game game);

/**
 * @fn void endRound (Game game)
 * @brief Fin du tour : Modifie les compteurs de DD de chaque joueur, incrémente le compteur de tours
 * @param game une partie en cours
 */
void endRound (Game game);

/**
 * @fn void playPhase(Game game)
 * @brief Exécute une phase de jeu pour le joueur courant
 * @param game un game valide (bien initialisé) 
*/
void playPhase(Game game);

/**
 * @fn int isGameFinished(Game game)
 * @brief Est-ce la fin de la partie ?
 * @param game une partie en cours
 * @return  0 si la partie n'est pas finie, 1 si le joueur 1 a gagné, 2 si le joueur 2 a gagné et 3 s'il y a égalité
*/
int isGameFinished(Game game);

/**
 * @fn Ensiie getCurrentPlayer(Game game)
 * @brief Retourne le joueur courant
 * @param game une partie en cours
 * @return renvoie le joueur actuellement en train de jouer
*/
Ensiie getCurrentPlayer(Game game);

/**
 * @fn Ensiie getNotCurrentPlayer(Game game)
 * @brief Retourne le joueur qui n'est pas le joueur courant
 * @param game une partie en cours
 * @return renvoie le joueur actuellement pas en train de jouer
*/
Ensiie getNotCurrentPlayer(Game game);

/** 
 * @fn void switchCurrentPlayer(Game game)
 * @brief Échange le caractère de joueur courant entre les 2 joueurs
	Si joueur1 est le joueur courant, alors joueur2 devient le joueur courant et joueur1 n'est plus joueur courant
	Si joueur2 est le joueur courant, alors joueur1 devient le joueur courant et joueur2 n'est plus joueur courant.
 * @param game jeu valide (contient 2 joueurs valides)
 */
void switchCurrentPlayer(Game game);

/** 
 * @fn int isRoundEven(Game game)
 * @brief Permet de savoir si le tour de jeu est un tour pair ou impair
 * @param game jeu valide en cours
 * @return 1 si le tour de jeu est pair
 * 		   0 si le tour de jeu est impair
 * @author Alex Danduran--Lembezat
 */
int isRoundEven(Game game);

/** 
 * @brief getter de joueur
 * @param game le jeu dont on veut le joueur
 * @param player_id le numero du joueur a recuperer
 * @return le joueur correspondant au numero player_number
 */
Ensiie getPlayer(Game game, int player_id);

/** 
 * @brief Renvoie le joueur qui n'est pas le joueur renseigné
 * @param game le jeu dont on veut le joueur
 * @param player Le joueur tel qu'on veut l'autre joueur
 * @return L'autre joueur qui n'est pas player
 */
Ensiie getOtherPlayer(Game game, Ensiie player);

/** 
 * @brief getter de tour
 * @param game le jeu dont on veut le tour
 * @return le tour correspondant au jeu game
 */
int getRound(Game game);

/**
 * @fn void playCard(Card played_card, Game game)
 * @brief Joue une carte de la main du joueur courant : déplace la carte played_card de la main du à son plateau ou a la défausse et en applique les effets, recalcul des PE
 * @param played_card une carte de sa main
 * @param game le jeu
 * @return 1 si la carte de fin de phase est jouée, 
 * 		   0 sinon
 */
int playCard(Card played_card, Game game);

/** 
 * @fn void sendToGraveyard(Game game, Ensiie player,  List_Card corresponding_list, Card card)
 * @brief Envoie dans la défausse d'un joueur une carte donnée provenant d'une liste donnée et retire ses effets si elle en a
 * @param game le jeu bien initialisé
 * @param player Joueur bien initialisé
 * @param corresponding_list la liste dans laquelle se trouve la carte
 * @param card la carte que l'on cherche à envoyer à la défausse
 * @author Alex Danduran--Lembezat
 */
void sendToGraveyard(Game game, Ensiie player,  List_Card corresponding_list, Card card);

#endif
