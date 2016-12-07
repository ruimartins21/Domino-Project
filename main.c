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
//#include <dir.h>

/**
 * Project main function
 * where all the flow of the program will be managed
 * @param argc counter of the arguments passed when calling the program executable
 * @param argv array of the arguments passed
 * @return returns 0 when the program is finished successfully
 */
int main(int argc, char *argv[])
{
//    int handSize = 10, choice, numberOfHands = 0, path = 0, typeOfFile = 0, edited = 0, numberOfSequences;
//    int validated = 0, maxSize = 0; // variables needed for more than one hand conditions commented below because it's not yet working
//    int game[MAX28][MAX2] = {};
//    int hand[MAX28][MAX3] = {};
//    char fileName[40], filePath[40] = "data/";
//    int sequence[MAX28][MAX2] = {};
//    int allSequences[MAX2000][MAX57] = {};
    int i = 0, j;

    GAME game = {0, NULL};
    HANDS hands = {10, 1, NULL};
    BLOCK *pblock = NULL;
    getGame(&game);
//    free(blockAux);
//    generateRandomHand(&game, &hands, hands.handSize, hands.numberOfHands);
//    openFile2("teste.txt", 1, &hands, &game);
//    printGame(game);
    pblock = popBlock(&game, 24);
    printf("[%d,%d]", pblock->leftSide, pblock->rightSide);
    /*

    // First iteration of the menu is for the user to choose between starting a new game or loading a saved game from a file
    choice = printMenu(0);
    if(choice == 1){
        path += 1; // iterates in the menu
        // Second iteration of the menu asks for the number of hands the users wants the program to use
//        numberOfHands = printMenu(path);
        // at the first phase of this project we still couldn't make the sequences work with more than one hand
        numberOfHands = 1;
        path += 1;
        // The third iteration is to choose a game made randomly or manually (where the user chooses the number of blocks on each hand)
        choice = printMenu(path);
        path += 1;
        // Generate game matrix
        getGame(game);
        if(choice == 1){
            // Generate the hands by calculating the maximum amount of blocks possible on each hand
            handSize = MAX28 / numberOfHands;
            // Defining a max number of blocks per hand (10)
            if(handSize > 10) {
                handSize = 10;
            }
            // at the first phase of this project we couldn't generate and save all the sequences possible because there is no hardware capacity
            // for so many sequences possible with more than 10 blocks, so we limit the user choice at 10 block maximum
            generateRandomHand(game, hand, handSize, numberOfHands);
        }else if(choice == 2){
            // asks the user for the number of blocks each hand will have
//            while(!validated){
//                handSize = printMenu(path);
//                // distribute the number of blocks chosen by the number of hands and it can't exceed 28 (total blocks existing)
//                // all hands have the same number of blocks
//                if(numberOfHands * handSize > 28){
//                    // tells the user what is the max size each hand can have depending on how many hands he chose before
//                    maxSize = 28 / numberOfHands;
//                    printf("!!! Size too large! To use %d hands each one can have %d game maximum. !!!\n", numberOfHands, maxSize);
//                }else{
//                    validated = 1;
//                }
//            }
            // at the first phase of this project we couldn't generate and save all the sequences possible because there is no hardware capacity
            // for so many sequences possible with more than 10 blocks, so we limit the user choice at 10 block maximum
            while(handSize > 10){
                handSize = printMenu(path);
            }
            path += 1;
            // asks the user if he wants to choose the blocks for each hand randomly or manually
            choice = printMenu(path);
            if(choice == 1){
                // choose the blocks randomly
                generateRandomHand(game, hand, handSize, numberOfHands);
            }else{
                // choose the blocks manually
                generateManualHand(game, hand, handSize, numberOfHands);
            }
        }
    }else if(choice == 2){
        // load a game from file
        path = 5;
        // not sure if it works cross-systems, not working in linux since it's needed 2 parameters
//        mkdir("data/"); // creates the folder if it doesn't yet exists
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
            openFile(fileName, typeOfFile, hand, game, &numberOfHands, &handSize);
        }
        // adds the 3rd column to the hands matrix to generate the sequences correctly
        fillHands(hand, handSize, numberOfHands);
    }
    // if the game matrix is empty there's no blocks that can be edited
    if(game[0][0] != -1){
        // Editing part: shows the user all the hands made before and asks if he wants to change anything
        edited = editHands(game, hand, handSize, numberOfHands);
    }
    if(!edited && path == 5) {
        // if the user loaded the game from a file and didn't edit that data, it will skip this next step that is to save the data in a file
    }else {
        // loaded the game from file and edited? then edit the existing file
        if(path == 5){
            editFile(fileName, typeOfFile, hand, game, numberOfHands, handSize);
        }else{
            path = 6;
            choice = printMenu(path);
            // if the user chose to save the game in a file
            if (choice) {
                path += 1;
                typeOfFile = printMenu(path);
                createGameFile(typeOfFile, hand, game, numberOfHands, handSize);
            }
        }
    }
    // at this point the game is ready to be played so we move on to generating the sequences
    initMat(allSequences, MAX2000, 57);
    generateSequence(hand, handSize, sequence, allSequences , 0);
    numberOfSequences = sortAllSequences(allSequences);
    printf("\t\t\t\t#  GAME COMPLETED  #\n\n");
    choice = printMenu(8);
    if(choice == 1){
        printf("\n# The biggest sequence generated was:\n");
        printSequences(allSequences, 1);
    }else{
        printf("\n# All sequences generated:\n");
        printSequences(allSequences, numberOfSequences);
    }

     */
    return 0;
}