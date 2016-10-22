///
///
///

#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 *
 * NOME FUNÇÕES
 * @params xpto
 *
 */

int main(int argc, char *argv[]) {
    srand((unsigned) time(NULL));
    //    SMALL_RECT windowSize = {0 , 0 , 75 , 70}; //change the values
//    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
    int handSize = 1, choice, numberOfHands, validated = 0, maxSize = 0, path = 0, l = 0, c = 0;
    int pieces[28][MAX2] = {};
//    int pieces[28][MAX2] = {
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

    // Generate game matrix automatically
//    for (l = 0; l < 28; l++) {
//        for (c = 0; c <= 6; c++) {
//            pieces[l][0] = c;
//            pieces[l][1] = c;
//        }
//    }
//    for (l = 0; l < 28; l++) {
//        printf("%d %d\n", pieces[l][0], pieces[l][1]);
//    }

    // First iteration of the menu asks for the number of hands the users wants the program to use
    numberOfHands = printMenu(0);
    printf("Hands = %d\n", numberOfHands);

    path += 1;
    // The second iteration is to choose a game made randomly or manually (where the user chooses the number of blocks on each hand)
    choice = printMenu(path);
    printf("Random = 1 & Manual = 2 => %d\n", choice);

    path += 1;
    if(choice == 1){

        // Generate the hands by calculating the ammount of blocks on each hand
        /// (if numberOfHands < 4 use 7 blocks for each hand)

    }else if(choice == 2){

        while(!validated){
            handSize = printMenu(path);
            printf("HandSize = %d\n", handSize);
            // algorithm to check if the number of blocks to use on each hands is according to the number of blocks on the game
            // all hands have the same number of blocks
            printf("Number of blocks used = %d\n", numberOfHands*handSize);
            // distribute the number of blocks chosen by the number of hands and it can't exceed 28 (total blocks existing)
            if(numberOfHands * handSize > 28){
                // tells the user what is the max size each hand can have to use all the blocks
                maxSize = 28 / numberOfHands;
                printf("!!! Size too large! To use %d hands each one can have %d pieces maximum. !!!\n", numberOfHands, maxSize);
            }else{
                validated = 1;
            }
        }

    }
    for(l = 0; l < numberOfHands; l++){
        printf("\t### Hand %d ###\n", l+1);
        printHandHorizontally(handSize);
        printf("\n");
    }

    return 0;
}