///
///
///

#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

/**
 *
 * NOME FUNÇÕES
 * @params xpto
 *
 */

int main(int argc, char *argv[])
{
    int handSize = 7, choice, numberOfHands = 0, validated = 0, maxSize = 0, path = 0, l = 0, c = 0, lin = 0, typeOfFile = 0;
    srand((unsigned) time(NULL));
    int pieces[LINES][MAX3] = {};
    int hand[LINES][MAX3] = {};
//    int pieces[28][MAX3] = {
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




    int mao[5][MAX3] = {
            {0,0,1},
            {1,0,1},
            {3,2,1},
            {0,3,1},
            {1,3,1}
    };


    int sequence[LINES][MAX3] = {};
    int allSequences[500][MAX57] = {};
    handSize = 5;

    initMat(allSequences, 500, 57);

//    printf("\nMatriz sequence main:\n");
//    printMat(mao, handSize);
//    inittMat(sequence, handSize);
//    printMat(sequence, handSize);
//    printf("\n\n");

    printf("----------------\n\n");
//    invertBlock(mao, 1);
//    printf("consitence: %d\n",isConsistent(mao, 1) );
//    printMat(sequence, 28);
//    printf("mao [0] %d %d \n", mao[1][0], mao[1][1]);

    generateSequence(mao, handSize, sequence, allSequences , 0);

    sortAllSequences(allSequences);
    return 0;

    /**
     *  Inicio do programa, para tras são testes
     */

    // Generate game matrix
    getGame(pieces);
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
        if(choice == 1){
            // Generate the hands by calculating the maximum amount of blocks possible on each hand
            handSize = LINES / numberOfHands;
            // Defining a max number of blocks per hand (7)
            if(handSize > 7){
                handSize = 7;
            }
        }else if(choice == 2){
            while(!validated){
                handSize = printMenu(path);
                // distribute the number of blocks chosen by the number of hands and it can't exceed 28 (total blocks existing)
                // all hands have the same number of blocks
                if(numberOfHands * handSize > 28){
                    // tells the user what is the max size each hand can have depending on how many hands he chose before
                    maxSize = 28 / numberOfHands;
                    printf("!!! Size too large! To use %d hands each one can have %d pieces maximum. !!!\n", numberOfHands, maxSize);
                }else{
                    validated = 1;
                }
            }
        }
        generateRandomHand(pieces, hand, handSize, numberOfHands);
        // GUARDAR NUM FICHEIRO (pedir nome para ficheiro) a matriz das maos juntamente com nº de maos e nº de peças por mao)
        createGameFile(hand, numberOfHands, handSize);
    }else if(choice == 2){
        typeOfFile = printMenu(4); // choose between text file or binary file
        openFile(typeOfFile, hand, &numberOfHands, &handSize);
        printf("\nnumberOfHands = %d | handSize = %d\n", numberOfHands, handSize);
    }

//    printf(" ### Matrix of Hands ###\n");
//    printMat(hand, handSize*numberOfHands);
    for(l = 0; l < numberOfHands; l++){
//        printf("\t### Hand %d ###\n", l+1);
//        printHandHorizontally(hand, handSize, l);
        printf("\nHand %d: ", l+1);
        printHand_uglify(hand, handSize, l);
        printf("\n");
    }

    return 0;
}