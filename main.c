///
///
///

#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/**
 *
 * NOME FUNÇÕES
 * @params xpto
 *
 */

int main(int argc, char *argv[])
{
    int handSize, choice, numberOfHands = 0, validated = 0, maxSize = 0, path = 0, l = 0, c = 0, lin = 0, typeOfFile = 0, edited;
    int game[LINES][COLS] = {};
    int hand[LINES][COLS] = {};
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

    int mao[5][COLS] = {
            {0, 0},
            {1, 0},
            {3, 2},
            {0, 3},
            {1, 3}
    };
    int sequence[LINES][COLS] = {};
    int aux[5][COLS] = {};
    handSize = 5;

//    printf("\nMatriz sequence main:\n");
//    printMat(mao, handSize);
//    inittMat(sequence, handSize);
//    printMat(sequence, handSize);
//    printf("\n\n");

//    printf("----------------\n\n");
//    invertBlock(mao, 1);
//    printf("consitence: %d\n",isConsistent(mao, 1) );
//    printMat(sequence, 28);
//    printf("mao [0] %d %d \n", mao[1][0], mao[1][1]);

//    generateSequence(mao, handSize, sequence, 0);

//    return 0;

    /**
     *  Inicio do programa, para tras são testes
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
            handSize = LINES / numberOfHands;
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
            // asks the user if he wants to choose the blocks for each hand manually or automatically
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
        typeOfFile = printMenu(path); // choose between text file or binary file
        printf("\nFile name: ");
        scanf("%s", fileName);
        openFile(fileName, typeOfFile, hand, game, &numberOfHands, &handSize);
    }
    // Editing part: shows the user all the hands made before and asks if he wants to change anything
    edited = editHands(game, hand, handSize, numberOfHands);
    if(!edited && path == 5) {
        // if the user loaded the game from a file and didn't edit that data, it will skip this next step that is to save the data in a file
    }else {
        // loaded the game from file and edited? then edit the existing file
        if(path == 5){
            editFile(fileName, typeOfFile, hand, game, numberOfHands, handSize);
        }else{
            path = 6;
            choice = printMenu(path);
            if (choice) {
                path += 1;
                typeOfFile = printMenu(path);
                createGameFile(typeOfFile, hand, game, numberOfHands, handSize);
            }
        }
    }
    printf(" ### Matrix of Hands ###\n");
    printMat(hand, handSize*numberOfHands);
    printf("\n ### Matrix of the Game ###\n");
    printMat(game, LINES);
//    for(l = 0; l < numberOfHands; l++){
////        printf("\t### Hand %d ###\n", l+1);
////        printHandHorizontally(hand, handSize, l);
//        printf("\nHand %d: ", l+1);
//        printHand_uglify(hand, handSize, l);
//        printf("\n");
//    }

    return 0;
}