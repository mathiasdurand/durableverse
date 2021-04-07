#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../headers/jeu.h"


int main()
{
	srand(time(NULL));
	int ending_status;  //Permet de suivre l'état du jeu. Varie entre 0, 1, 2

	Game game=createGame();     //Génère une instance de Game et l'initialise correctement

	printNewGame(getPlayer(game,1),getPlayer(game,2));
	
	/* Permet d'initialiser l'aléatoire et d'avoir un chiffre pseudo-aléatoire
       entre 0 et 1 (équiprobable) */
	
	int first_to_play=rand()%2;

	/*  Permet d'assigner aléatoirement quel joueur est le premier à jouer
		Par défaut (pdt génération de game), player1 est le joueur courant*/
	if(first_to_play){  //Si first_to_play=1
		switchCurrentPlayer(game);  //1 chance sur 2 de switch le joueur courant (donc 1 chance sur 2 pour chacun des joueurs de commencer la partie)
	}

	/*  Boucle principale du jeu
		Condition de terminaison : isGameFinished(game) renvoit 
			- 0 si la partie n'est pas finie
			- 1 s'il y a 1 vainqueur à la partie
			- 2 s'il y a égalité entre les 2 joueurs
		Cette fonction vérifie le nombre de DD de chaque ENSIIE et le nombre de tours écoulés
		À la fin de chaque tour (une itération de la boucle), endRound(game) met à jour les DD
		On ne peut que gagner (et pas perdre) des DD donc ultimement soit :
			- Une seule ENSIIE aura atteint au moins 20 DD et en aura plus que l'autre
			- Les 2 ENSIIEs auront le même nombre de DD > 20
			- Le nombre de tour=31 (incrémenté à chaque itération de boucle) */
	while((ending_status=isGameFinished(game))==NOT_FINISHED)
	{
		newRound(game);     //Signifie au plateau qu'un nouveau tour commence
		printNewRound(getRound(game));    //Affiche les informations relatives au nouveau tour aux joueurs

		/*Phase 1*/
		printNewPhase(getPlayer(game,1),getPlayer(game,2));    //Affiche le début d'une nouvelle phase et indique le joueur associé

		playPhase(game);    //Gère toute la phase d'un joueur
        
		switchCurrentPlayer(game);  //Change de joueur courant 

		/*Phase 2*/
		printNewPhase(getPlayer(game,1),getPlayer(game,2));    //Affiche le début d'une nouvelle phase et indique le joueur associé

		playPhase(game);    //Gère toute la phase d'un joueur

		endRound(game);     //Met à jour les compteurs de DD

		printStateOfGame(getPlayer(game, 1), getPlayer(game, 2), getRound(game));
	}

	printEndGame(ending_status, getPlayer(game,1), getPlayer(game,2));     //Affiche le vainqueur de la partie (ou égalité ou aucun vainqueur) et des informations sur la fin de partie

	destroyGame(game);      //Libère la mémoire allouée dans la création de game

}
