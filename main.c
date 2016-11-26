/// @file main.c
/// @brief Main file of the project that contains the flux of all the functions implemented
/// @copyright

#include "libs/utils.h"
#include "libs/interface.h"
#include "libs/core.h"
#include "libs/files.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Project main function
 * where all the flow of the program will be managed
 * @param argc counter of the arguments passed when calling the program executable
 * @param argv array of the arguments passed
 * @return returns 0 when the program is finished successfully
 */
int main(int argc, char *argv[])
{
    int handSize, choice, numberOfHands = 0, validated = 0, maxSize = 0, path = 0, l = 0, c = 0, lin = 0, typeOfFile = 0, edited = 0;
    int game[MAX28][MAX2] = {};
    int hand[MAX28][MAX3] = {};
    char fileName[40];
//    int game[28][COLS] = {
//            {0,0},
//            {0,1},
//            {0,2},
//            {0,3},
//            {0,4},
//            {0,5},
//            {0,6},
//            {1,1},
//            {1,2},
//            {1,3},
//            {1,4},
//            {1,5},
//            {1,6},
//            {2,2},
//            {2,3},
//            {2,4},
//            {2,5},
//            {2,6},
//            {3,3},
//            {3,4},
//            {3,5},
//            {3,6},
//            {4,4},
//            {4,5},
//            {4,6},
//            {5,5},
//            {5,6},
//            {6,6},
//    };

//    int mao[15][MAX3] = {
//            {0,0},
//            {0,1},
//            {0,2},
//            {0,3},
//            {0,4},
//            {0,5},
//            {0,6},
//            {1,1},
//            {1,2},
//            {1,3},
//            {1,4},
//            {1,5},
//            {1,6},
//            {2,2},
//            {2,3}
//    };

    int mao[10][MAX3] = {
            {0,0,1},
            {0,1,1},
            {0,2,1},
            {0,3,1},
            {0,4,1},
            {0,5,1},
            {0,6,1},
            {1,1,1},
            {1,2,1},
            {1,3,1},
//            {1,4,1},
//            {1,5,1},
//            {1,6,1},
//            {2,2,1},
//            {2,3,1}
    };




    int sequence[MAX28][MAX2] = {};
    int allSequences[MAX2000][MAX57] = {};
    handSize = 10;

    initMat(allSequences, MAX2000, 57);
    generateSequence(mao, handSize, sequence, allSequences , 0);

    sortAllSequences(allSequences);
    return 0;

    /**
     *  Inicio do programa, para tras são testes (RETIRAR)
     */

    // First iteration of the menu is for the user to choose between starting a new game or loading a saved game from a file
    choice = printMenu(0);
    if(choice == 1){
        path += 1; // iterates in the menu
        // Second iteration of the menu asks for the number of hands the users wants the program to use
        numberOfHands = printMenu(path);
        path += 1;
        // The third iteration is to choose a game made randomly or manually (where the user chooses the number of blocks on each hand)
        choice = printMenu(path);
        path += 1;
        // Generate game matrix
        getGame(game);
        if(choice == 1){
            // Generate the hands by calculating the maximum amount of blocks possible on each hand
            handSize = MAX28 / numberOfHands;
            // Defining a max number of blocks per hand (7)
            if(handSize > 7) {
                handSize = 7;
            }
            generateRandomHand(game, hand, handSize, numberOfHands);
        }else if(choice == 2){
            // asks the user for the number of blocks each hand will have
            while(!validated){
                handSize = printMenu(path);
                // distribute the number of blocks chosen by the number of hands and it can't exceed 28 (total blocks existing)
                // all hands have the same number of blocks
                if(numberOfHands * handSize > 28){
                    // tells the user what is the max size each hand can have depending on how many hands he chose before
                    maxSize = 28 / numberOfHands;
                    printf("!!! Size too large! To use %d hands each one can have %d game maximum. !!!\n", numberOfHands, maxSize);
                }else{
                    validated = 1;
                }
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
        printf("\nFiles existing (.txt):\n");
        system("dir/b data\\*.txt"); // scans all files with the extension "txt" in the root of the folder where the program executable is and prints them
        printf("\nFiles existing (.bin):\n");
        system("dir/b data\\*.bin"); // scans all files with the extension "bin" in the root of the folder where the program executable is and prints them
        typeOfFile = printMenu(path); // choose between text file or binary file
        printf("\nFile name: ");
        scanf("%s", fileName);
        if(fileExists(fileName)) {
            openFile(fileName, typeOfFile, hand, game, &numberOfHands, &handSize);
        }
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
    return 0;
}