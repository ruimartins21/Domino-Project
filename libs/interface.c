/// @file interface.c
/// @brief Gathers all the functions that interact with the user
/// @copyright

#include "interface.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
* Prints the multiple menus that are needed
* @param path tells the function at wich part of the menu it is
* @param choice choice the user made, that together with the path given gives the function the proper infos to display
*/
int printMenu(int path) {
    int choiceMade = 0;
    switch (path) {
        case 0:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - New Game\n");
            printf("\t\t\t\t2 - Load Game from file\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 1:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tNumber of Hands: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 28) {
                printf("!!! Please choose a number between 1 & 28. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 2:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Create Hand(s) randomly\n");
            printf("\t\t\t\t2 - Create Hand(s) manually\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 3:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tNumber of blocks on each hand: ");
            scanf("%d", &choiceMade);
            return choiceMade;

        case 4:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Choose the blocks randomly\n");
            printf("\t\t\t\t2 - Choose the blocks manually\n");
            scanf("%d", &choiceMade);
            return choiceMade;

        case 5:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Load game from text file\n");
            printf("\t\t\t\t2 - Load game from binary file\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 6:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tSave game data in a file? (Y/N): ");
            getchar(); // avoids empty symbols like previous enters
            choiceMade = getchar(); // gets the character needed to answer by its ASCII code
            if (choiceMade != 'Y' && choiceMade != 'y' && choiceMade != 'N' && choiceMade != 'n') {
                printf("!!! Invalid answer !!!\n");
                return printMenu(path);
            } else {
                if (choiceMade == 'Y' || choiceMade == 'y') return 1;
                return 0;
            }

        case 7:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Save game data in a text file\n");
            printf("\t\t\t\t2 - Save game data in a binary file\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 8:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - See the biggest sequence\n");
            printf("\t\t\t\t2 - See all the sequences\n");
//            printf("\t\t\t\t3 - Search a sequence\n");
//            printf("\t\t\t\t4 - Search a pattern in the sequences\n");
//            printf("\t\t\t\t5 - Replace a pattern in the sequences\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
//            if (choiceMade < 1 || choiceMade > 5) {
            if (choiceMade < 1 || choiceMade > 2) {
//                printf("!!! Please choose a number between 1 & 5. !!!\n");
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        default:
            return -1;
    }
}

/**
 * Prints an hand of the game as a vector with its numbers
 * @param size size of the hand
 */
//void printHand(int hand[][MAX3], int size, int index) {
//    int i;
//    // move the first position to print according to the index
//    index = (index == 0 ? index : index * size);
//    for (i = index; i < index + size; i++) {
//        printf("[ %d , %d ] ", hand[i][0], hand[i][1]);
//    }
//}

/**
 * Prints an entire matrix until it finds -1 on it that means the matrix ended
 * !! This function is only used for debugging/testing !!
 * @param matrix is the matrix requested to print out
 * @param lines are the lines of that matrix
 */
void printMat(int matrix[][MAX2], int lines) {
    int l = 0;
    while (l < lines && (matrix[l][0] != -1 || matrix[l][1] != -1)) {
        printf("[%d %d] ", matrix[l][0], matrix[l][1]);
        l++;
    }
}

/**
 * Prints the hands matrix, it couldn't be printed in the previous function because this matrix is 3 columns wide
 * !! This function is only used for debugging/testing !!
 * @param hand is the hands matrix
 * @param lines are the lines of that matrix, that is calculated by (numberOfHands*handSize)
 */
void printHands(int hand[][MAX3], int lines){
    int l = 0;
    while (l < lines) {
        printf("[%d %d] ", hand[l][0], hand[l][1]);
        l++;
    }
}

/**
 * shows the user all the blocks that are available to choose (this prevents out of bounds selections from the user)
 * @param matrix is the game matrix that has the unused blocks
 * @return returns the counter of blocks available to choose from for further conditioning from the user inputs
 */
int blocksAvailable(GAME game) {
    int i = 0;
    BLOCK *blockAux = game.pfirstBlock;
    printf("\n\t\t\t\t### Available Blocks ###\n");
    while (blockAux != NULL) {
        printf("\t#%2d = [%d|%d]", i + 1, blockAux->leftSide, blockAux->rightSide);
        // putting breaks after a certain number of blocks printed to improve the visualization
        if ((i + 1) % 5 == 0 && i != 0) {
            printf("\n");
        }
        i++;
        blockAux = blockAux->pnextBlock;
    }
    return i;
}

void generateManualHand(GAME *game, HANDS *hands) {
    int i, j, blocksLimit, blockId;
    hands->pfirstHand = NULL;
    HAND *handAux = NULL;
    BLOCK *delBlock = NULL, *blockAux = NULL;
    for (i = 0; i < hands->numberOfHands; i++) {
        handAux = (HAND*)malloc(sizeof(HAND));
        printf("\n## %2d hand ##\n", i + 1);
        for (j = 0; j < hands->handSize; j++) {
            blocksLimit = blocksAvailable(*game);
            printf("\n%2d block: ", j + 1);
            scanf("%d", &blockId);
            if (blockId < 1 || blockId > blocksLimit) {
                printf("!!! Choose a valid number !!!");
                j--;
                continue;
            }
            blockId -= 1;
            // gets the block chosen from the game, removing it from there, and inserting it in the respective hand
            delBlock = popBlock(game, blockId);
            blockAux = transferBlock(delBlock);
            if(handAux->pfirstBlock == NULL){ // it's the first block to be inserted in the hand
                blockAux->pnextBlock = NULL; // it will be used the insertion at the head, so the first block to be inserted will be the one at the tail
            }else{
                blockAux->pnextBlock = handAux->pfirstBlock;
            }
            handAux->pfirstBlock = blockAux;
        }
        handAux->pnextHand = hands->pfirstHand;
        hands->pfirstHand = handAux;
    }
}

///**
// * The user chooses block by block wich ones he wants in each hand
// * it's showed the game matrix so he can see the available blocks
// * after each choice the game matrix goes through the compressMatrix
// * because a block was "removed" from it and passed to the hands matrix
// * @param matrix game matrix with the unused blocks
// * @param hand matrix with all the hands generated
// * @param handSize size of each hand
// * @param numberOfHands number of hands existing
// */
//void generateManualHand(int matrix[][MAX2], int hand[][MAX3], int handSize, int numberOfHands) {
//    int i, j, k = 0, blocksLimit, blockId;
//    for (i = 0; i < numberOfHands; i++) {
//        printf("\n## %2d hand ##\n", i + 1);
//        for (j = 0; j < handSize; j++) {
//            blocksLimit = blocksAvailable(matrix);
//            printf("\n%2d block: ", j + 1);
//            scanf("%d", &blockId);
//            if (blockId < 1 || blockId > blocksLimit) {
//                printf("!!! Choose a valid number !!!");
//                j--;
//                continue;
//            }
//            blockId -= 1;
//            // gets the block chosen in the game matrix and stores it in the hands matrix
//            hand[k][0] = matrix[blockId][0];
//            hand[k][1] = matrix[blockId][1];
//            hand[k][2] = 1;
//            // sends to compressMatrix to remove the block chosen from the game matrix
////            compressMatrix(matrix, blocksLimit, blockId);
//            k++;
//        }
//    }
//}

/**
 * Function that handles all the editing the user wishes to do on the generated hands
 * It handles the changes of blocks between the hands matrix and the game matrix
 * @param matrix is the game matrix with the unused blocks
 * @param hand is the matrix with all the hands generated
 * @param handSize is the size of each hand
 * @param numberOfHands is the number of hands existing
 * @return returns 0 if the user doesn't want to edit anything and 1 if the user edited something
 */
int editHands(int matrix[][MAX2], int hand[][MAX3], int handSize, int numberOfHands) {
    int i, j, handId = 0, removeId, addId = 0, blocksLimit, edited = 0, validate = 0, choice = 'y';
    while (1) {
        for (i = 0; i < numberOfHands; i++) {
            printf("\n#%2d = Hand %d: ", i + 1, i + 1);
//            printHand(hand, handSize, i);
        }
        while (!validate) {
            printf("\nDo you wish to change anything before proceeding? (Y/N): ");
            getchar();
            choice = getchar();
            if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                printf("!!! Invalid answer !!!\n");
                validate = 0;
                continue;
            }
            validate = 1;
        }
        validate = 0;
        if (choice == 'n') {
            // if the user decided to not edit, since it's inside a loop, we need to check if he edited anything before
            return edited;
        }
        if (numberOfHands > 1) {
            printf("\nEnter the id of the hand to edit: ");
            scanf("%d", &handId);
            handId -= 1;
            handId = (handId == 0 ? handId : handId *
                                             handSize); // arithmetic to reach the desired hand on the matrix of hands
        }
        for (i = 0, j = handId; i < handSize; i++, j++) {
            printf(" #%2d = [%d|%d]", i + 1, hand[j][0], hand[j][1]);
        }
        printf("\nWhich block do you want to change? ");
        scanf("%d", &removeId);
        removeId -= 1;
        // to this removeId it's needed to add the previous handId index so we can reach the correct hand inside the hands matrix and then move the desired index
        removeId += handId;
//        blocksLimit = blocksAvailable(matrix);
        while (addId < 1 || addId > blocksLimit) {
            printf("\nChoose a block to insert from the available blocks above: ");
            scanf("%d", &addId);
        }
        addId -= 1;
        // swaps the block chosen from the game matrix with the block chosen on the hand
        i = matrix[addId][0];
        j = matrix[addId][1];
        matrix[addId][0] = hand[removeId][0];
        matrix[addId][1] = hand[removeId][1];
        hand[removeId][0] = i;
        hand[removeId][1] = j;
        edited = 1;
        // reset variables
        addId = 0;
        removeId = 0;
    }
}

/**
 * Function that prints the allSequences matrix to show all of the sequences as the name refers
 * !! This function is only used for debugging/testing !!
 * @param matrix is the allSequences matrix
 * @param lines are the number of sequences on it
 * @param cols are the columns to print, maximum is 57
 */
void printMatDefault(int matrix[][MAX57], int lines, int cols) {
    int l = 0, c = 0;

    for (l = 0; l < lines; l++) {
        for (c = 0; c < cols && matrix[l][c] != -1; c++) {
            printf("%d ", matrix[l][c]);
        }
        printf("\n");
    }
}

/**
 * Function that prints the allSequences matrix with the proper info for the user to see
 * @param matrix is the allSequences matrix
 * @param lines are the number of sequences on it
 * @param cols are the columns to print, maximum is 57
 */
void printSequences(ALLSEQUENCES allSequences) {
    int l = 0, c = 0;
    unsigned long lines = allSequences.numberOfSequences;
    SEQUENCE *paux = allSequences.pfirstSequence;
    for (l = 0; l < lines; l++) {
        BLOCK *pblocks = paux->pfirstBlock;
        for (c = 0; c < paux->sizeOfSequence && pblocks != NULL; c++) {
            printf("[%d, %d] ", pblocks->leftSide, pblocks->rightSide);
            pblocks = pblocks->pnextBlock;
        }
        paux++;
    }
}

/**
 * Prints a certain array
 * !! This function is only used for debugging/testing !!
 * @param a is the array passed
 * @param N is the number of elements
 */
void printArray(int *a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}