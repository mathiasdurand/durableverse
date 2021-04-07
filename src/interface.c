#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "../headers/interface.h"

#define MAX_STRING 100

int whichStudent()
{
    printf("Souhaitez-vous prendre un FISE (1) ou un FISA (2) ? ");
    char* carte = malloc(MAX_STRING*sizeof(char));
    scanf("%s",carte); //entrée de l'utilisateur

    if (strcasecmp(carte,"FISE") == 0||atoi(carte)==1) //strcmp non sensible à la casse
    {
        free(carte);
        return FISE; //renvoie FISE si le joueur choisit un FISE
    }
    else if (strcasecmp(carte,"FISA") == 0||atoi(carte)==2) //strcmp non sensible à la casse
    {
        free(carte);
        return FISA; //renvoie FISA si le joueur choisit un FISA
    }

    else //si l'entrée du joueur ne correspond à aucune des deux cartes
    {
        free(carte);
        printf("Carte non valide ! \n");
        return whichStudent(); //rappel de la fonction
    }
}

Card askCard(Ensiie player)
{
    printf("Vous disposez de %d PE \n", getEnergy(player));
    printf("Votre main : \n");
    printHand(getHand(player), getEnergy(player)); //imprime sur le flux de sortie standard lamain du joueur passé en argument
    printf("\nQuelle carte jouer ? Entrez un numéro : ");
    char* id = malloc(MAX_STRING*sizeof(char));
    scanf("%s", id);  //demande au jour l'id (affiché dans le printHand) de la carte qu'il veut jouer
    //L'id donné par le joueur correspond à la place de la carte dans sa main

    //Dans le cas de fin de phase renvoie une carte préalablement définie "fin de phase" toujours jouable par le joueur(reste présente dans sa main) if (id > getSize(list_hand))
    int cpt = 0;
    char* correct_id = malloc(MAX_STRING*sizeof(char));
    int new_cpt = 0;
    while (id[cpt] != '\0' && ((id[cpt] >= '0' && id[cpt] <= '9') || id[cpt] == ' ')) {
        if (id[cpt] != ' ') {
            correct_id[new_cpt] = id[cpt];
            new_cpt += 1;
        }
        cpt += 1;
    }
    correct_id[new_cpt] = '\0';

    if (id[cpt] != '\0') { //On a rencontré un caractère qui n'était ni un chiffre ni un espace
        printf("Index non valide\n");
        free(id);
        free(correct_id);
        return askCard(player); //Rappel de la fonction
    }
    else if (atoi(correct_id) < 0 || atoi(correct_id) >= getSize(getHand(player))) { // L'index n'est pas compris entre 0 et SizeOfHand-1
        printf("Cette carte n'est pas présente dans votre main.\n");
        free(id);
        free(correct_id);
        return askCard(player);
    }
    else {
        Card* hand = getList(getHand(player));
        int n = atoi(correct_id);
        free(id);
        free(correct_id);
        return hand[n]; //renvoie la carte correspondante. La vérification du coût de la carte jouée est réalisée dans playCard() et s'assurer qu'un joueur ne joue pas une carte pour laquelle il ne dispose pas d'assez de PE
    }
}

void printNotEnoughPE(){
    //si la carte a un cout superieur a la quantité d'energie dont dispose le joueur
    printf("Vous n'avez pas assez de PE pour jouer cette carte\n");
}

void printStateOfGame(Ensiie player1, Ensiie player2, int round) //fait appel aux fonctions printBoard et printHand afin de n'avoir qu'à utiliser une ligne de code pour imprimer sur le flux standard de sortie l'état du jeu
{
    Board board_E1 = getBoard(player1);
    Board board_E2 = getBoard(player2);

    if (isCurrentPlayer(player2)) {
        printf("Plateau de %s\n-------------------------------\n\n", getPlayerName(player1));
        printf("Cartes élèves :\n\n");
        printStudentPool(getStudentPool(board_E1),round);
        printf("\n-------------------------------\n");
        printf("Cartes staff :\n\n");
        printListCard(getStaffPool(board_E1));

        printf("\n\n-------------------------------\n");
        printf("Tour n°%d | DD %s: %d | DD %s : %d | PE %s : %d | PE %s: %d", round, getPlayerName(player1), getPlayerSustainablePoints(player1), getPlayerName(player2), getPlayerSustainablePoints(player2), getPlayerName(player1), getEnergy(player1), getPlayerName(player2), getEnergy(player2));
        printf("\n-------------------------------\n\n");

        printf("Plateau %s\n-------------------------------\n\n", getPlayerName(player2));
        printf("Cartes élèves :\n\n");
        printStudentPool(getStudentPool(board_E2),round);
        printf("\n-------------------------------\n");
        printf("Cartes staff :\n\n");
        printListCard(getStaffPool(board_E2));
    }
    else {
        printf("Plateau %s\n-------------------------------\n\n",getPlayerName(player2));
        printf("Cartes élèves :\n\n");
        printStudentPool(getStudentPool(board_E2),round);
        printf("\n-------------------------------\n");
        printf("Cartes staff :\n\n");
        printListCard(getStaffPool(board_E2));

        printf("\n\n-------------------------------\n");
        printf("Tour n°%d | DD %s : %d | DD %s : %d | PE %s : %d | PE %s : %d", round, getPlayerName(player1), getPlayerSustainablePoints(player1), getPlayerName(player2), getPlayerSustainablePoints(player2), getPlayerName(player1), getEnergy(player1), getPlayerName(player2), getEnergy(player2));
        printf("\n-------------------------------\n\n");

        printf("Plateau %s\n-------------------------------\n\n",getPlayerName(player1));
        printf("Cartes élèves :\n\n");
        printStudentPool(getStudentPool(board_E1),round);
        printf("\n-------------------------------\n");
        printf("Cartes staff :\n\n");
        printListCard(getStaffPool(board_E1));
    }
    printf("\n");
    printf("\n");
}

void printHand(List_Card list_hand,int energy)
{
    Card* hand = getList(list_hand);
    for (int i=0; i<getSize(list_hand) ;i++)
    {
        Card card=hand[i];
        type_card int_type = getType(card);
        char* type;
        if (int_type == 1) {
            type = "PERSONNEL";
        }
        else {
            type = "ACTION";
        }

        card_specialise int_spe = getSpecialisation(card);
        char* spe;
        switch (int_spe)
        {
        case NOT_SPECIALISED:
            spe="---";
            break;
        case PL:
            spe = "PL";
            break;
        case GL:
            spe="GL";
            break;
        case HPC:
            spe="HPC";
            break;
        case MA:
            spe="MA";
            break;
        case IN:
            spe="IN";
            break;

        default : break;
        }


        if (getPE(card) <= energy)// si la carte dans la main a un coût inférieur au nombre de PE disponibles
        {
            printf("%2d -- %30s | %9s | %3s | Coût: %2d PE\n", i, getName(card), type, spe , getPE(card)); //on la montre comme disponible
        }
        else //sinon
        {
            printf("%2d XX %30s | %9s | %3s | Coût: %2d PE\n", i, getName(card), type, spe, getPE(card)); //on l'affiche comme non jouable et n'affiche pas son id
        }
    }
}

void printListCard(List_Card liste_cartes)
{
    Card* cartes = getList(liste_cartes);
    for (int i = 0; i < getSize(liste_cartes); i++)
    {
        Card card = cartes[i];

        card_specialise int_spe = getSpecialisation(card);
        char *spe;
        switch (int_spe)
        {
        case NOT_SPECIALISED:
            spe = "---";
            break;
        case PL:
            spe = "PL";
            break;
        case GL:
            spe = "GL";
            break;
        case HPC:
            spe = "HPC";
            break;
        case MA:
            spe = "MA";
            break;
        case IN:
            spe = "IN";
            break;

        default:
            break;
        }
        printf("%2d -- %24s | %3s\n", i+1,getName(card),spe);
    }
}

void printGraveyard(List_Card graveyard)
{
    printListCard(graveyard);
}

void printStudentPool(List_Card pool, int round){

    Card* cartes = getList(pool);
    for (int i = 0; i < getSize(pool); i++)
    {
        Card card = cartes[i];

        card_specialise int_spe = getSpecialisation(card);
        char *spe;
        switch (int_spe)
        {
        case NOT_SPECIALISED:
            spe = "---";
            break;
        case PL:
            spe = "PL";
            break;
        case GL:
            spe = "GL";
            break;
        case HPC:
            spe = "HPC";
            break;
        case MA:
            spe = "MA";
            break;
        case IN:
            spe = "IN";
            break;

        default:
            break;
        }
        
        if (round%2 == 0 && getCardId(card)==FISA) {
            printf("%2d XX %s | %3s | Points de Développement: %2d ; Points de durabilité: %2d\n",i+1,getName(card), spe, getCardSustainable(card),getDurability(card));
        }
        else {
            printf("%2d -- %s | %3s | Points de Développement: %2d ; Points de durabilité: %2d\n", i + 1, getName(card), spe, getCardSustainable(card), getDurability(card));
        }
    }
}

void printEndGame(int status, Ensiie player1, Ensiie player2)
{
    if (status == 1) // si le joueur 1 a gagné
    {
        printf("AND THE WINNER IIIIIS... %s!\n",getPlayerName(player1));
    }
    else if (status == 2) // si le joueur 2 a gagné
    {
        printf("AND THE WINNER IIIIIS... %s!\n", getPlayerName(player2));
    }
    else if (status == 3) //S'il y a égalité entre les 2 joueurs
    {
        printf("AND THE WINNER IIIIIS... NOBODY! EGALITE\n");
    }
       
}

void printNewRound(int round)
{
    printf("Nouveau tour \n");
    if (round == 1){
        printf("%d er tour\n",round);
    }
    else {
        printf("%d ème tour\n",round); //affichage du numéro du tour
    }
    if(round == 6) //au tour 6 débloque un emplacement personnel
    {
        printf("Vous disposez maintenant de 2 emplacements personnel\n");
    }
    else if (round== 11) //au tour 11 débloque un emplacement personnel
    {
        printf("Vous disposez maintenant de 3 emplacements personnel\n");
    }
}

void printNewPhase(Ensiie player1, Ensiie player2)
{
    if (isCurrentPlayer(player1)) //si le joueur courant est le joueur 1
    {
        printf("Au tour de %s\n",getPlayerName(player1));
    }
    else //si le joueur courant est le joueur 2
    {
        printf("Au tour de %s\n",getPlayerName(player2));
    }
    
}

void printNewGame(Ensiie player1, Ensiie player2) {
    printf("Une nouvelle partie commence ...\n");

    printf("Entrez le nom du Joueur 1 : ");
    char* name1 = malloc((MAX_STRING+1)*sizeof(char));
    char* name = malloc((MAX_STRING+1)*sizeof(char));
    fgets(name1,101,stdin);
    if (name1[0] == '\n') {
        setPlayerName(player1,"J1");
    }
    else {
        int i = 0;
        while (name1[i] != '\n') {
            name[i]=name1[i];
            i+=1;
        }
        name[i]='\0';
        setPlayerName(player1,name);
    }
    printf("Entrez le nom du Joueur 2 : ");
    char* name2 = malloc((MAX_STRING+1)*sizeof(char));
    char* namebis = malloc((MAX_STRING+1)*sizeof(char));
    fgets(name2,101,stdin);
    if (name2[0] == '\n') {
        setPlayerName(player2,"J2");
    }
    else {
        int j = 0;
        while (name2[j] != '\n') {
            namebis[j]=name2[j];
            j+=1;
        }
        namebis[j]='\0';
        setPlayerName(player2,namebis);
    }
    free(name1);
    free(name2);
}