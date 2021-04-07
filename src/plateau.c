#include <stdlib.h>

#include "../headers/plateau.h"

/*********************** STRUCTURE ************************/

/**Structure de plateau
	Une structure de plateau simplifiee avec uniquement les elements relatifs au plateau + une structure ensiie qui dispose des 6 tirets indiques dans le 1.2 du sujet
	Chaque Ensiie dispose de son propre plateau, donc son student_pool et son staff_pool
*/
struct str_board {
	List_Card student_pool; //ensemble des cartes eleves posees sur le plateau
	List_Card staff_pool; //ensemble des cartes personnel posees sur le plateau
	unsigned int unlocked_spots; //de 1 à 3 : nombre d'emplacement de carte personnel débloqué
};



Board createBoard()
{
    Board board = (Board)malloc(sizeof(struct str_board));
    board->student_pool=createListCard();
    board->staff_pool=createListCard();
    board->unlocked_spots=1;

    return board;
}


void destroyBoard(Board board)
{
    destroyListCard(board->student_pool);
    destroyListCard(board->staff_pool);
    free(board);
}


List_Card getStudentPool(Board board)
{
    return (board->student_pool);
}


List_Card getStaffPool(Board board)
{
    return board->staff_pool;
}


unsigned int getUnlockedSpotNumber(Board board)
{
    return board->unlocked_spots;
}

int getAvailableSpotNumber(Board board)
{
    return getUnlockedSpotNumber(board) - getSize(getStaffPool(board));
}

void updateUnlockedSpots(Board board, int round)
{
    if (round >= 6 && round < 11)
        board->unlocked_spots=2;
    else if (round >= 11)
        board->unlocked_spots=3;
}


int isStaffSpecialised(Board board, card_specialise specialisation)
{
    for(int i = 0; i < getSize(getStaffPool(board)); i++)
    {
        if( getSpecialisation(getList(getStaffPool(board))[i]) == specialisation)
            return 1;
    }

    return 0;
}
