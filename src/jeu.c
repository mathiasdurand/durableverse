#include <stdlib.h>
#include <math.h>

#include "../headers/jeu.h"

/**Structure de partie
*/
struct str_game {
	Ensiie player1; //joueur 1
	Ensiie player2; //joueur 2
	int round; //tour
};


Game createGame() 
{
	Game instance = (Game)malloc(sizeof(struct str_game));
	instance->player1=createEnsiie();
	initiateEnsiie(instance->player1);
	instance->player2=createEnsiie();
	initiateEnsiie(instance->player2);
	instance->round=1;

	setIsCurrentPlayer(instance->player1, 1);		//De manière arbitraire on met le joueur1 comme joueur courant car il sera changé aléatoirement après
	
	return instance;
}


void destroyGame(Game game)
{
	destroyEnsiie(game->player1);
	destroyEnsiie(game->player2);
	free(game);
}


void newRound(Game game)
{
	updateUnlockedSpots(getBoard(getCurrentPlayer(game)), getRound(game));	//Il suffit de mettre à jour les nombre d'emplacement en fonction du round
}

void endRound (Game game)
{
	Ensiie player1 = getPlayer(game, 1);
	Ensiie player2 = getPlayer(game, 2);


	int sum_player1_card_durability = getSumCardDurability(player1, isRoundEven(game));			//Récupère la somme des durabilités de ttes les cartes élèves (sauf les FISA si tour impair)
	int sum_player1_card_sustainable = getSumCardSustainable(player1, isRoundEven(game));		//De même pour le développement

	int sum_player2_card_durability = getSumCardDurability(player2, isRoundEven(game));			//même chose pour le joueur2
	int sum_player2_card_sustainable = getSumCardSustainable(player2, isRoundEven(game));


	int points_player1 = max(0, sum_player1_card_sustainable - sum_player2_card_durability);	//On calcule les points DD que devrait remporter le joueur1 sans compter les buffs/debuffs
	int points_player2 = max(0, sum_player2_card_sustainable - sum_player1_card_durability);	//De même

	addPlayerSustainablePoints(player1, max(0, points_player1+getAdditionalSustainablePoints(player1)));	//On rajoute le bon nombre de DD (en compter les buffs et débuffs avec getAdditionalSustainablePoints(...))
	addPlayerSustainablePoints(player2, max(0, points_player2+getAdditionalSustainablePoints(player2)));

	game->round++;	//On incrémente le numéro du tour
}

void playPhase(Game game)
{
	int which_student;  //Servira à stocker si l'utilisateur veut tirer une carte FISA ou FISE

	Card card_to_play;  //Carte que le joueur va tirer dans la boucle do...while suivante

	/* Calcule le nombre de carte élève qu'un joueur peut tirer pour la phase courante et 
       demande au joueur s'il veut jouer une carte FISA ou FISE*/
	for (int i=0; i<numberEleve(getCurrentPlayer(game)); i++)
	{
		which_student=whichStudent();   //Demande au joueur quel carte élève il veut utiliser (FISA ou FISE)
		addEleve(which_student, getCurrentPlayer(game));    //Pose la carte élève choisie sur le plateau
	}
	countEnergy(getCurrentPlayer(game), getRound(game));    //Compte le nombre de PE disponibles pour cette phase
	countEnergy(getNotCurrentPlayer(game), getRound(game));

	/* Calcul et pioche le bon nombre de cartes dans le deck*/
	for (int i=0; i<numberCard(getCurrentPlayer(game)); i++)
	{
		drawEnsiie(getCurrentPlayer(game));   //Pioche une carte dans le deck
	}

	int end_phase=0;    //Sert à la condition de terminaison de la boucle while
    
	/*  Boucle d'action du joueur : le joueur choisit de jouer une carte ou de passer son tour
		Condition de Terminaison : Quand le joueur décide de terminer son tour, il choisit une carte virtuelle
            qui une fois tirée va passer la variable 'end_phase' à 1 et donc permettre de sortir de la boucle*/
	do
	{
		printStateOfGame(getPlayer(game, 1), getPlayer(game, 2), getRound(game));     //Affiche la main du joueur, les cartes en jeu, la défausse
		card_to_play=askCard(getCurrentPlayer(game));   //Demande au joueur de choisir quelle carte il veut jouer

		end_phase=playCard(card_to_play, game);     //Joue la carte sélectionnée sur le plateau et applique ses effets. Récupère si oui ou non la carte de fin de phase a été jouée
        
	} while (!end_phase);
}

int isGameFinished(Game game)
{
	//Une ENSIIE gagne si elle a plus de 20DD à la fin de son tour et que l'autre Ensiie en a moins
	if (getPlayerSustainablePoints(game->player1) > 20 && getPlayerSustainablePoints(game->player1) > (getPlayerSustainablePoints(game->player2)))
		return ONE_WINNER;
	else if (getPlayerSustainablePoints(game->player2) > 20 && getPlayerSustainablePoints(game->player2) > (getPlayerSustainablePoints(game->player1)))
		return TWO_WINNER;
	//Si on dépasse les 30 tours (on peut donc jouer le tour n°30), la partie s'arrête (si une Ensiie n'a pas gagné au 30eme tour bien sûr)
	else if (game->round > 30)
		return DRAW;
	else 
		return NOT_FINISHED;
}

Ensiie getCurrentPlayer(Game game)
{
	if (isCurrentPlayer(game->player1))
		return game->player1;
	else
		return game->player2;
}

Ensiie getNotCurrentPlayer(Game game)
{
	if (isCurrentPlayer(game->player1))
		return game->player2;
	else
		return game->player1;
}

void switchCurrentPlayer(Game game)
{
	if (isCurrentPlayer(game->player1) == 1)
	{
		setIsCurrentPlayer(game->player1, 0);
		setIsCurrentPlayer(game->player2, 1);
	}
	else
	{
		setIsCurrentPlayer(game->player2, 0);
		setIsCurrentPlayer(game->player1, 1);
	}
}

int isRoundEven(Game game)
{
	if (game->round % 2 == 0)
		return 1;
	else 
		return 0;
}

Ensiie getPlayer(Game game, int player_id)
{
	Ensiie result;

	switch (player_id)
	{
	case 1:
		result = game->player1;
		break;
	
	case 2:
		result = game->player2;
		break;
	}

	return result;
}

Ensiie getOtherPlayer(Game game, Ensiie player)
{
	if (player == getPlayer(game, 1))
		return getPlayer(game, 2);
	else 
		return getPlayer(game, 1);
}

int getRound(Game game)
{
	return game->round;
}


void applyEffect(Game game, card_effect effect)
{
	List_Card list_card;
	Card* iterable_list;

	switch (effect)
	{
	case AE1:	//Ajoute 1 point de Développement à chacune des cartes FISE du joueur courant
		changeSustOrDura(getCurrentPlayer(game), SUSTAINABLE, FISE, 1);
		updateSustAndDura(getCurrentPlayer(game));
		break;

	case AE2:	//Ajoute 1 point de Durabilité à chacune des cartes FISE du joueur courant
		changeSustOrDura(getCurrentPlayer(game), DURABILITY, FISE, 1);
		updateSustAndDura(getCurrentPlayer(game));
		break;

	case AA1:	//Ajoute 1 point de Développement à chacune des cartes FISA du joueur courant
		changeSustOrDura(getCurrentPlayer(game), SUSTAINABLE, FISA, 1);
		updateSustAndDura(getCurrentPlayer(game));
		break;
	
	case AA2:	//Ajoute 1 point de Durabilité à chacune des cartes FISA du joueur courant
		changeSustOrDura(getCurrentPlayer(game), DURABILITY, FISA, 1);
		updateSustAndDura(getCurrentPlayer(game));
		break;

	case RE1:	//Retire 1 point de Développement à chacune des cartes FISE du joueur non courant
		changeSustOrDura(getNotCurrentPlayer(game), SUSTAINABLE, FISE, -1);
		updateSustAndDura(getNotCurrentPlayer(game));
		break;

	case RE2:	//Retire 1 point de Durabilité à chacune des cartes FISE du joueur non courant
		changeSustOrDura(getNotCurrentPlayer(game), DURABILITY, FISE, -1);
		updateSustAndDura(getNotCurrentPlayer(game));
		break;

	case RA1: 	//Retire 1 point de Développement à chacune des cartes FISA du joueur non courant
		changeSustOrDura(getNotCurrentPlayer(game), SUSTAINABLE, FISA, -1);
		updateSustAndDura(getNotCurrentPlayer(game));
		break;
	
	case RA2:	//Retire 1 point de Durabilité à chacune des cartes FISA du joueur non courant
		changeSustOrDura(getNotCurrentPlayer(game), DURABILITY, FISA, -1);
		updateSustAndDura(getNotCurrentPlayer(game));
		break;

	case ADD:	//Fait gagner 1 DD supplémentaire à la fin du tour
		addAdditionalSustainablePoints(getCurrentPlayer(game), 1);
		break;

	case RDD:	//Retire un point de durabilité supplémentaire à la fin du tour de l'adversaire
		removeAdditionalSustainablePoints(getNotCurrentPlayer(game), 1);
		break;

	case DR:	//Permet de piocher 1 carte de plus dans la phase suivante
		//Traité dans la fonction numberCard()
		break;

	case E:		//Permet de mettre en jeu une carte Eleve de plus au début de sa phase
		//Traité dans la fonction numberStudent()
		break;

	case CDD:	//Fait gagner instantanément 1 DD au joueur courant
		addPlayerSustainablePoints(getCurrentPlayer(game), 1);
		break;

	case REC:	//Le joueur courant pioche une carte
		drawEnsiie(getCurrentPlayer(game));
		list_card = getHand(getCurrentPlayer(game));
		iterable_list = getList(list_card);

		//Permet de récupérer la carte jouée et de l'envoyer à la défausse (la carte n'est pas donnée en argument de la fonction) car drawEnsiie(...) induit une modification de l'emplacement mémoire de la liste
		int j = 0;
		while(j < getSize(list_card) && getCardId(iterable_list[j]) != RECRUTEMENT)
		{
			j++;
		}

		sendToGraveyard(game, getCurrentPlayer(game), list_card, iterable_list[j]);

		break;

	case RFISE:	//Mettre en jeu une carte FISE
		addEleve(FISE, getCurrentPlayer(game));
		addEnergy(getCurrentPlayer(game), 1);
		break;

	case RFISA:	//Mettre en jeu une carte FISA
		addEleve(FISA, getCurrentPlayer(game));
		if(isRoundEven(game) == 0)
			addEnergy(getCurrentPlayer(game), 2);	//On pense à ajouter l'énergie et pas la réinitialiser car sinon on récupère toute l'énergie dépensée dans la phase en cours
		break;

	case EV:	//Gagne 6 PE (donc en considérant le coût de la carte -> Gagne 2 PE)
		addEnergy(getCurrentPlayer(game), 6);
		break;

	case DIP:	//Retire une carte FISE et FISA du plateau de l'adversaire
		list_card = getStudentPool(getBoard(getNotCurrentPlayer(game)));
		iterable_list = getList(list_card);

		int FISE_removed = 0;
		int FISA_removed = 0;
		int i = 0;
		int length = getSize(list_card);
		
		//Parcours de la liste d'étudiant en ne supprimant bien qu'une carte FISE et une carte FISA
		while (i < length && (!FISE_removed || !FISA_removed)) {
			if(!FISE_removed && getCardId(iterable_list[i])==FISE)
			{
				destroyCard(removeElement(list_card, i));
				FISE_removed = 1;

				list_card = getStudentPool(getBoard(getNotCurrentPlayer(game)));	//On rappelle getStudentPool(...) car la donnée de la liste est perdue après le destroyCard(...)
				iterable_list = getList(list_card);
			}
			if(!FISA_removed && getCardId(iterable_list[i])==FISA)
			{
				destroyCard(removeElement(list_card, i));
				FISA_removed = 1;

				list_card = getStudentPool(getBoard(getNotCurrentPlayer(game)));	//de même
				iterable_list = getList(list_card);
			}
			i += 1;
			length = getSize(list_card);
		}
		break;
	
	case DCH:	//Mettez la première des cartes Personnel mise en jeu par l'adversaire dans sa défausse
		list_card = getStaffPool(getBoard(getNotCurrentPlayer(game)));
		iterable_list = getList(list_card);
		if(getSize(list_card) >= 1 )
			sendToGraveyard(game, getNotCurrentPlayer(game), list_card, iterable_list[0]);	//[0] correspond bien à la première carte car les cartes sont déposées au dessus de la liste
		break;

	case RCY:	//Mélangez votre défausse et cette carte avec votre pioche
		list_card = getHand(getCurrentPlayer(game));
		iterable_list = getList(list_card);

		//LA carte doit être envoyée à la défausse, or on a pas la carte donc on part la chercher dans la main
		int l = 0;
		while(l < getSize(list_card) && getCardId(iterable_list[l]) != RECYCLAGE)
		{
			l++;
		}

		sendToGraveyard(game, getCurrentPlayer(game), getHand(getCurrentPlayer(game)), iterable_list[l]);

		//Ici on applique son effet en déplacant toutes les cartes du cimetière vers le deck
		list_card = getGraveyard(getCurrentPlayer(game));
		iterable_list = getList(list_card);

		for(int i = 0; i < getSize(list_card); i++)
		{
			displaceElement(iterable_list[i], list_card, getDeck(getCurrentPlayer(game)));
			list_card = getGraveyard(getCurrentPlayer(game));	//displaceElement(...) fait perdre l'emplacement mémoire de la liste donc on le met à jour
			iterable_list = getList(list_card);
		}

		//On mélange le paquet
		shuffle(getDeck(getCurrentPlayer(game)));
		break;

	case ZPA:	//Vos cartes Eleves gagnent un point de Développement. Toute nouvelle carte Eleve arrivant en jeu gagne 1 point de développement
		applyEffect(game, AE1);
		applyEffect(game, AA1);
		break;

	case RVG:	//Vos cartes Eleves gagnent un point de Durabilité. Toute nouvelle carte Eleve arrivant en jeu gagne 1 point de Durabilité
		applyEffect(game, AE2);
		applyEffect(game, AA2);
		break;

	case FER:	//Retire du plateau toutes les cartes FISE et FISA
		list_card = getStudentPool(getBoard(getCurrentPlayer(game)));

		int len = getSize(list_card);
		while(0 < len)
		{
			destroyCard(removeElement(list_card, 0));
			len = getSize(list_card);
		}

		list_card = getStudentPool(getBoard(getNotCurrentPlayer(game)));
		len = getSize(list_card);
		while(0 < len)
		{
			destroyCard(removeElement(list_card, 0));
			len = getSize(list_card);
		}
		break;
	
	case PGL: //Donne aux cartes Eleves dans le plateau la spécialisation GL (si elles ne sont pas déjà spécialisées)
		for(int i=0; i < getSize(getStudentPool(getBoard(getCurrentPlayer(game)))); i++)
		{
			setSpecialisation(getList(getStudentPool(getBoard(getCurrentPlayer(game))))[i], GL);
		}
		updateSustAndDura(getCurrentPlayer(game));
		break;
		
	case PHPC: //Donne aux cartes Eleves dans le plateau la spécialisation HPC (si elles ne sont pas déjà spécialisées)
		for(int i=0; i < getSize(getStudentPool(getBoard(getCurrentPlayer(game)))); i++)
		{
			setSpecialisation(getList(getStudentPool(getBoard(getCurrentPlayer(game))))[i], HPC);
		}
		updateSustAndDura(getCurrentPlayer(game));
		break;
	
	case PMA: //Donne aux cartes Eleves dans le plateau la spécialisation MA (si elles ne sont pas déjà spécialisées)
		for(int i=0; i < getSize(getStudentPool(getBoard(getCurrentPlayer(game)))); i++)
		{
			setSpecialisation(getList(getStudentPool(getBoard(getCurrentPlayer(game))))[i], MA);
		}
		updateSustAndDura(getCurrentPlayer(game));
		break;

	case PIN: //Donne aux cartes Eleves dans le plateau la spécialisation IN (si elles ne sont pas déjà spécialisées)
		for(int i=0; i < getSize(getStudentPool(getBoard(getCurrentPlayer(game)))); i++)
		{
			setSpecialisation(getList(getStudentPool(getBoard(getCurrentPlayer(game))))[i], IN);
		}
		updateSustAndDura(getCurrentPlayer(game));
		break;

	case PPL: //Donne aux cartes Eleves dans le plateau la spécialisation PL (si elles ne sont pas déjà spécialisées)
		for(int i=0; i < getSize(getStudentPool(getBoard(getCurrentPlayer(game)))); i++)
		{
			setSpecialisation(getList(getStudentPool(getBoard(getCurrentPlayer(game))))[i], PL);
		}
		updateSustAndDura(getCurrentPlayer(game));
		break;

	case BDE: //Les cartes Eleves de l'adversaire perdent un point de Durabilité.
		applyEffect(game, RE2);
		applyEffect(game, RA2);
		break;

	case DIS: //La moitié des élèves FISE et FISA sont éliminés du plateau
		playDistanciation(getCurrentPlayer(game));
		playDistanciation(getNotCurrentPlayer(game));
		break;

	default:
		break;
	}
}



void removeEffect(Game game, Ensiie relative_player, card_effect effect)
{
	switch (effect)
	{
	case AE1:	//Retire 1 point de Développement à chacune des cartes FISE du joueur courant
		changeSustOrDura(relative_player, SUSTAINABLE, FISE, -1);
		updateSustAndDura(relative_player);
		
		break;

	case AE2:	//Retire 1 point de Durabilité à chacune des cartes FISE du joueur courant
		changeSustOrDura(relative_player, DURABILITY, FISE, -1);
		updateSustAndDura(relative_player);
		break;

	case AA1:	//Retire 1 point de Développement à chacune des cartes FISA du joueur courant
		changeSustOrDura(relative_player, SUSTAINABLE, FISA, -1);
		updateSustAndDura(relative_player);
		break;
	
	case AA2:	//Retire 1 point de Durabilité à chacune des cartes FISA du joueur courant
		changeSustOrDura(relative_player, DURABILITY, FISA, -1);
		updateSustAndDura(relative_player);		
		break;

	case RE1:	//Ajoute 1 point de Développement à chacune des cartes FISE du joueur non courant
		changeSustOrDura(getOtherPlayer(game, relative_player), SUSTAINABLE, FISE, 1);
		updateSustAndDura(getOtherPlayer(game, relative_player));
		break;

	case RE2:	//Ajoute 1 point de Durabilité à chacune des cartes FISE du joueur non courant
		changeSustOrDura(getOtherPlayer(game, relative_player), DURABILITY, FISE, 1);
		updateSustAndDura(getOtherPlayer(game, relative_player));
		break;

	case RA1: 	//Ajoute 1 point de Développement à chacune des cartes FISA du joueur non courant
		changeSustOrDura(getOtherPlayer(game, relative_player), SUSTAINABLE, FISA, 1);
		updateSustAndDura(getOtherPlayer(game, relative_player));
		break;
	
	case RA2:	//Ajoute 1 point de Durabilité à chacune des cartes FISA du joueur non courant
		changeSustOrDura(getOtherPlayer(game, relative_player), DURABILITY, FISA, 1);
		updateSustAndDura(getOtherPlayer(game, relative_player));
		break;

	case ADD:	//Enlève 1 point de DD de plus à la fin du tour
		removeAdditionalSustainablePoints(relative_player, 1);
		break;

	case RDD:	//L'autre élève gagne 1 DD de plus à la fin de son tour
		addAdditionalSustainablePoints(getOtherPlayer(game, relative_player), 1);
		break;

	case DR:	//Piocher 1 carte de moins au début de sa phase
		//Traité dans la fonction numberCard()
		break;

	case E:		// Met en jeu 1 carte Etudiant en moins au début de la phase
		//Traité dans la fonction numberStudent()
		break;

	default:
		break;
	}
}


int playCard(Card played_card, Game game)
{
	int is_played = 0;

	//Récupère les données nécessaires au traitement de la carte qui risquent d'être perdu après modification des listes
	type_card type = getType(played_card);
	id_cardname id = getCardId(played_card);

	if (getCardId(played_card) == END_PHASE)	//Gère le cas de la carte de fin de phase
		return 1;
	
	int size_effects = getSizeEffects(played_card);
	card_effect* effects = (card_effect*)malloc(size_effects * sizeof(card_effect));

	if (enoughEnergy(getCurrentPlayer(game), played_card))	//Si le joueur a suffisemment de PE pour jouer la carte
	{
		removeEnergy(getCurrentPlayer(game), getPE(played_card));	//On retire l'énergie
		is_played = 1;

		for (int i = 0; i < size_effects ; i++)
		{
			effects[i] = getEffects(played_card)[i];	//On copie la liste des effets de la carte car la carte peut être altérée dans applyEffect(...)
		}

		for (int i = 0; i < size_effects ; i++)
		{
			applyEffect(game, effects[i]);		//Applique un effet à la fois pour chacune des cartes
		}
	}
	else 
	{
		printNotEnoughPE();
	}

	if(is_played == 1)
	{
		if( type == ACTION && id != RECYCLAGE && id != RECRUTEMENT )	//Les cartes "Recyclage" et "Recrutement" ont déjà été envoyées à la défausse dans applyEffect(...) donc il ne faut pas les renvoyer une autre fois
			sendToGraveyard(game, getCurrentPlayer(game), getHand(getCurrentPlayer(game)), played_card);
		else if ( type == STAFF )
		{
			if(getAvailableSpotNumber(getBoard(getCurrentPlayer(game))) <= 0)	//Si le nombre d'emplacement Personnel n'est pas suffisant, on envoie la première carte Personnel à la défausse
				sendToGraveyard(game, getCurrentPlayer(game), getStaffPool(getBoard(getCurrentPlayer(game))), getList(getStaffPool(getBoard(getCurrentPlayer(game))))[0]);

			displaceElement(played_card, getHand(getCurrentPlayer(game)), getStaffPool(getBoard(getCurrentPlayer(game))));	//On déplace la carte Personnel dans l'emplacement Personnel du joueur
		}
				
			
	}
	updateSustAndDura(getPlayer(game, 1));
	updateSustAndDura(getPlayer(game, 2));

	free(effects);
	return 0;	
}



void sendToGraveyard(Game game, Ensiie player,  List_Card corresponding_list, Card card)
{
	for (int i = 0; i < getSizeEffects(card); i++)
	{
		removeEffect(game, player, getEffects(card)[i]);	//On retire les effets des cartes qu'on envoit à la défausse
	}

	displaceElement(card, corresponding_list, getGraveyard(player));
}










