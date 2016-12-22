/// @file main.c
/// @brief Main file of the project that contains the flux of all the functions implemented
/// @copyright

#include "libs/utils.h"
#include "libs/interface.h"
#include "libs/core.h"
#include "libs/files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <io.h>
//#include <dir.h>

void merge_sort_td(int a[], int aux[], int lo, int hi);
void merge_arrays(int a[], int aux[], int lo, int mid, int hi);
void client_Merge_Sort_td();

/**
 * Project main function
 * where all the flow of the program will be managed
 * @param argc counter of the arguments passed when calling the program executable
 * @param argv array of the arguments passed
 * @return returns 0 when the program is finished successfully
 */
int main(int argc, char *argv[])
{
    int choice, path = 0, typeOfFile = 0, edited = 0, numberOfSequences;
    int validated = 0, maxSize = 0; // variables needed for more than one hand conditions commented below because it's not yet working
    int i = 0, j;
    srand((unsigned)time(NULL));
    char fileName[40], filePath[40] = "data/";

    GAME game = {0, NULL};
    HANDS hands = {0, 0, NULL};
    SEQUENCE sequence = { 0, NULL};
    ALLSEQUENCES allsequences = { 0, NULL};
//    BLOCK *pblock = NULL;
    getGame(&game);
    int count = 0;
    hands.handSize = 8;



    hands.numberOfHands = 1;
    generateRandomHand(&game, &hands);
//    generateManualHand(&game, &hands);
    printf("\n## Game (%d) ##\n", game.availableBlocks);
    printGame(game);
    printf("\n## Hands ##\n");
    printHand(hands);
    generateSequence(&hands, &sequence, &allsequences, 0, &count);
    printf("Nº sequencias: %d\n", count);
    printf("Nº sequencias saved: %d\n", allsequences.numberOfSequences);
//    printAllSequence(allsequences);

//    client_Merge_Sort_td();

//    free(blockAux);
//    generateRandomHand(&game, &hands);
//    openFile("teste.bin", 2, &hands, &game);
//    printf("\n## Game ##\n");
//    printGame(game);
//    printf("\n## Hands ##\n");
//    printHand(hands);
//    pblock = popBlock(&game, 30);
//    if(pblock != NULL){
//        printf("[%d,%d]", pblock->leftSide, pblock->rightSide);
//    }

    // First iteration of the menu is for the user to choose between starting a new game or loading a saved game from a file
    choice = printMenu(0);
    if(choice == 1) {
        path += 1; // iterates in the menu
        // Second iteration of the menu asks for the number of hands the users wants the program to use
        hands.numberOfHands = printMenu(path);
        path += 1;
        // The third iteration is to choose a game made randomly or manually (where the user chooses the number of blocks on each hand)
        choice = printMenu(path);
        path += 1;
        // Generate the game structure
        getGame(&game);
        if (choice == 1) {
            // Generate the hands by calculating the maximum amount of blocks possible on each hand
            hands.handSize = MAX28 / hands.numberOfHands;
            // Defining a max number of blocks per hand (7 is default, and depending on the number of hands it can be less)
            if (hands.handSize > 7) {
                hands.handSize = 7;
            }
            generateRandomHand(&game, &hands);
        } else if (choice == 2) {
            // asks the user for the number of blocks each hand will have
            while (!validated) {
                hands.handSize = printMenu(path);
                // distribute the number of blocks chosen by the number of hands and it can't exceed 28 (total blocks existing)
                // all hands have the same number of blocks
                if (hands.numberOfHands * hands.handSize > 28) {
                    // tells the user what is the max size each hand can have depending on how many hands he chose before
                    maxSize = 28 / hands.numberOfHands;
                    printf("!!! Size too large! To use %d hands each one can have %d blocks maximum. !!!\n",
                           hands.numberOfHands, maxSize);
                } else {
                    validated = 1;
                }
            }
            path += 1;
            // asks the user if he wants to choose the blocks for each hand randomly or manually
            choice = printMenu(path);
            if (choice == 1) {
                // choose the blocks randomly
                generateRandomHand(&game, &hands);
            } else {
                // choose the blocks manually
                generateManualHand(&game, &hands);
            }
        }
    }else if(choice == 2){
        // load a game from file
        path = 5;
        // not sure if it works cross-systems, not working in linux since it's needed 2 parameters
        mkdir("data/"); // creates the folder if it doesn't yet exists
        printf("\nFiles existing (.txt):\n");
        system("dir/b data\\*.txt"); // scans all files with the extension "txt" in the root of the folder where the program executable is and prints them
        printf("\nFiles existing (.bin):\n");
        system("dir/b data\\*.bin"); // scans all files with the extension "bin" in the root of the folder where the program executable is and prints them
        typeOfFile = printMenu(path); // choose between text file or binary file
        while(fileExists(filePath) != 1){
            strcpy(filePath, "data/"); // restores the string to its original string after some concatenation that might have occurred inside the loop
            printf("\nFile name: ");
            scanf("%s", fileName);
            if(typeOfFile == 1){
                checkExtension(fileName, ".txt");
            }else{
                checkExtension(fileName, ".bin");
            }
            strcat(filePath, fileName);
        }
        if(fileExists(filePath)) {
            openFile(fileName, typeOfFile, &hands, &game);
        }
    }
    // if the game has no blocks, it's not possible to edit
    if(game.availableBlocks > 0){
        // Editing part: shows the user all the hands made before and asks if he wants to change anything
        edited = editHands(&hands, &game);
    }
    if(!edited && path == 5) {
        // if the user loaded the game from a file and didn't edit that data, it will skip this next step that is to save the data in a file
    }else {
        if(path == 5){ // loaded the game from file and edited? then edit the existing file
            editFile(fileName, typeOfFile, hands, game);
        }else{ // if it enter here, the game wasn't loaded from a file so asks the user if he wants to save the game
            path = 6;
            choice = printMenu(path);
            // if the user chose to save the game in a file
            if (choice) {
                path += 1;
                typeOfFile = printMenu(path);
                createGameFile(typeOfFile, hands, game);
            }
        }
    }
//    printf("\n## Game (%d) ##\n", game.availableBlocks);
//    printGame(game);
//    printf("\n## Hands ##\n");
//    printHand(hands);
    // at this point the game is ready to be played so we move on to generating the sequences
//    initMat(allSequences, MAX2000, 57);
//    generateSequence(hand, handSize, sequence, allSequences , 0);
//    numberOfSequences = sortAllSequences(allSequences);
//    printf("\t\t\t\t#  GAME COMPLETED  #\n\n");
//    choice = printMenu(8);
//    if(choice == 1){
//        printf("\n# The biggest sequence generated was:\n");
//        printSequences(allSequences, 1);
//    }else{
//        printf("\n# All sequences generated:\n");
//        printSequences(allSequences, numberOfSequences);
//    }

    return 0;
}
/*
void merge_sort_td(int a[], int aux[], int lo, int hi) {
        int mid = lo + (hi - lo) / 2;
        if (hi <= lo) return;
        merge_sort_td(a, aux, lo, mid);
        merge_sort_td(a, aux, mid + 1, hi);
        merge_arrays(a, aux, lo, mid, hi);
}

void merge_arrays(int a[], int aux[], int lo, int mid, int hi) {
        int i = lo, j = mid + 1, k;
        for (k = lo; k <= hi; k++) // copy
            aux[k] = a[k];
        for (k = lo; k <= hi; k++) { // merge
                if (i > mid) a[k] = aux[j++];
                else if (j > hi) a[k] = aux[i++];
                else if (aux[j] < aux[i]) a[k] = aux[j++];
                else a[k] = aux[i++];
            }
}
void client_Merge_Sort_td() {
        int i;
        int v[] = {10, 33, 22, 4, 75, 3, 68, 13, 55, 34};
        int N = 10;
        int v2[10];
        merge_sort_td(v, v2, 0, N - 1);
        for (i = 0; i < N; i++) {
                printf("%d ", v[i]);
            }
}*/