/// @file utils.c
/// @brief File that gathers all the utilities function used in the core project functions
/// @copyright

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

/**
 * Generates initial game matrix
 * @param pieces matrix to store the generated numbers
 * @return default (0): filled matrix is stored via its addresses so it isn't needed to return anything
 */
int getGame(int game[][MAX2]) {
    int l = 0, c = 0, lin = 0;
    for (l = 0; l <= 6; l++) {
        for (c = l; c <= 6; c++) {
            game[lin][0] = l;
            game[lin][1] = c;
            lin += 1;
        }
    }
    return 0;
}

///**
//* Prints the various menus that are needed
//* @param path tells the function at wich part of the menu it is
//* @param choice choice the user made, that together with the path given gives the function the proper infos to display
//*/
//int printMenu(int path) {
//    int choiceMade = 0;
//    switch (path) {
//        case 0:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\t1 - New Game\n");
//            printf("\t\t\t\t2 - Load Game from file\n");
//            printf("\t\t\t\tChoice: ");
//            scanf("%d", &choiceMade);
//            if (choiceMade < 1 || choiceMade > 2) {
//                printf("!!! Please choose a number between 1 & 2. !!!\n");
//                return printMenu(path);
//            } else {
//                return choiceMade;
//            }
//
//        case 1:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\tNumber of Hands: ");
//            scanf("%d", &choiceMade);
//            if (choiceMade < 1 || choiceMade > 28) {
//                printf("!!! Please choose a number between 1 & 28. !!!\n");
//                return printMenu(path);
//            } else {
//                return choiceMade;
//            }
//
//        case 2:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\t1 - Create Hand(s) randomly\n");
//            printf("\t\t\t\t2 - Create Hand(s) manually\n");
//            printf("\t\t\t\tChoice: ");
//            scanf("%d", &choiceMade);
//            if (choiceMade < 1 || choiceMade > 2) {
//                printf("!!! Please choose a number between 1 & 2. !!!\n");
//                return printMenu(path);
//            } else {
//                return choiceMade;
//            }
//
//        case 3:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\tNumber of blocks on each hand: ");
//            scanf("%d", &choiceMade);
//            return choiceMade;
//
//        case 4:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\t1 - Choose the blocks randomly\n");
//            printf("\t\t\t\t2 - Choose the blocks manually\n");
//            scanf("%d", &choiceMade);
//            return choiceMade;
//
//        case 5:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\t1 - Load game from text file\n");
//            printf("\t\t\t\t2 - Load game from binary file\n");
//            printf("\t\t\t\tChoice: ");
//            scanf("%d", &choiceMade);
//            if (choiceMade < 1 || choiceMade > 2) {
//                printf("!!! Please choose a number between 1 & 2. !!!\n");
//                return printMenu(path);
//            } else {
//                return choiceMade;
//            }
//
//        case 6:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\tSave game data in a file? (Y/N): ");
//            getchar(); // avoids empty symbols like previous enters
//            choiceMade = getchar(); // gets the character needed to answer by its ASCII code
//            if (choiceMade != 'Y' && choiceMade != 'y' && choiceMade != 'N' && choiceMade != 'n') {
//                printf("!!! Invalid answer !!!\n");
//                return printMenu(path);
//            } else {
//                if (choiceMade == 'Y' || choiceMade == 'y') return 1;
//                return 0;
//            }
//
//        case 7:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\t1 - Save game data in a text file\n");
//            printf("\t\t\t\t2 - Save game data in a binary file\n");
//            printf("\t\t\t\tChoice: ");
//            scanf("%d", &choiceMade);
//            if (choiceMade < 1 || choiceMade > 2) {
//                printf("!!! Please choose a number between 1 & 2. !!!\n");
//                return printMenu(path);
//            } else {
//                return choiceMade;
//            }
//
//        case 8:
//            printf("\t\t\t\t# # # # # # # # # #\n");
//            printf("\t\t\t\t#     M E N U     #\n");
//            printf("\t\t\t\t# # # # # # # # # #\n\n");
//            printf("\t\t\t\t1 - See the biggest sequence\n");
//            printf("\t\t\t\t2 - See all the sequences\n");
//            printf("\t\t\t\t3 - Search a sequence\n");
//            printf("\t\t\t\t4 - Search a pattern in the sequences\n");
//            printf("\t\t\t\t5 - Replace a pattern in the sequences\n");
//            printf("\t\t\t\tChoice: ");
//            scanf("%d", &choiceMade);
//            if (choiceMade < 1 || choiceMade > 5) {
//                printf("!!! Please choose a number between 1 & 5. !!!\n");
//                return printMenu(path);
//            } else {
//                return choiceMade;
//            }
//
//        default:
//            return -1;
//    }
//}

///**
// * Prints an hand of the game as a vector with its numbers
// * @param size size of the hand
// */
//void printHand(int hand[][MAX3], int size, int index) {
//    int i;
//    // move the first position to print according to the index
//    index = (index == 0 ? index : index * size);
//    for (i = index; i < index + size; i++) {
//        printf("[ %d , %d ] ", hand[i][0], hand[i][1]);
//    }
//}

///**
// * Function that generates player hand randomly
// * -> Runs the number of hands chosen by the user, for each one runs all the blocks of the hand
// * -> Generates a random number confined to the values 0 to 27
// * -> Drops index of generated number from the deck and puts it on the player hand
// * -> Compresses Matrix and inserts "-1" in the last position according to the number of lines withdrawned
// *
// * @param matrix Initial game matrix (all pieces)
// * @param hand Matrix with the player pieces (hand game)
// * @param linesHand Matrix lines of the player hand
// * @param qtSet Number of hands to generate
// */
//void generateRandomHand(int matrix[][MAX2], int hand[][MAX3], int linesHand, int qtSet) {
//    int l = 0, j = 0, randValue = 0, linesCount = 0, limit = 0;
//    limit = MAX28 / linesHand;
//    if (qtSet < limit)
//        limit = qtSet;
//
//    for (j = 0; j < limit; j++) {
//        for (l = 0; l < linesHand; l++) {
//            randValue = 0 + rand() % (MAX28 - linesCount);
//            hand[linesCount][0] = matrix[randValue][0];
//            hand[linesCount][1] = matrix[randValue][1];
//            hand[linesCount][2] = 1;
//
//            compressMatrix(matrix, MAX28 - linesCount, randValue);
//            linesCount++;
//        }
//    }
//
//}


/**
 * Function that compresses the game matrix
 * Used to generated random hands
 * -> Drops index of generated number from deck and put it on player hand
 * -> Compress Matrix and puts "-1" in the last position
 *
 * @param matrix Initial Matrix (with the number of blocks existing at the time)
 * @param lines Number of lines existing at the previous matrix
 * @param index Position of the block to be withdrawn to the player hand
 * if it's NULL it will get the lines given and "compress" the matrix to be that size only
 */
void compressMatrix(int matrix[][MAX2], int lines, int index) {
    int i;
    if (index == -1) {
        // it will compress the matrix to the size given from the lines parameter
        // after the size given fills with -1 until the limit size (28)
        for (i = lines; i < (lines + (28 - lines)); i++) {
            matrix[i][0] = -1;
            matrix[i][1] = -1;
        }
    } else {
        for (; index < lines; index++) {
            matrix[index][0] = matrix[index + 1][0];
            matrix[index][1] = matrix[index + 1][1];
        }
        matrix[index - 1][0] = -1;
        matrix[index - 1][1] = -1;
    }
}

///**
// * Prints an entire matrix until it finds -1 on it that means the matrix ended
// * !! This function is only used for debugging/testing !!
// * @param matrix is the matrix requested to print out
// * @param lines are the lines of that matrix
// */
//void printMat(int matrix[][MAX2], int lines) {
//    int l = 0;
//    while (l < lines && (matrix[l][0] != -1 || matrix[l][1] != -1)) {
//        printf("[%d %d] ", matrix[l][0], matrix[l][1]);
//        l++;
//    }
//}

///**
// * Prints the hands matrix, it couldn't be printed in the previous function because this matrix is 3 columns wide
// * !! This function is only used for debugging/testing !!
// * @param hand is the hands matrix
// * @param lines are the lines of that matrix, that is calculated by (numberOfHands*handSize)
// */
//void printHands(int hand[][MAX3], int lines){
//    int l = 0;
//    while (l < lines) {
//        printf("[%d %d] ", hand[l][0], hand[l][1]);
//        l++;
//    }
//}

///**
// * shows the user all the blocks that are available to choose (this prevents out of bounds selections from the user)
// * @param matrix is the game matrix that has the unused blocks
// * @return returns the counter of blocks available to choose from for further conditioning from the user inputs
// */
//int blocksAvailable(int matrix[][MAX2]) {
//    int i = 0;
//    printf("\n\t\t\t\t### Available Blocks ###\n");
//    while (i < MAX28 && (matrix[i][0] != -1 || matrix[i][1] != -1)) {
//        printf("\t#%2d = [%d|%d]", i + 1, matrix[i][0], matrix[i][1]);
//        if ((i + 1) % 5 == 0 && i != 0) {
//            printf("\n");
//        }
//        i++;
//    }
//    return i;
//}

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
//            compressMatrix(matrix, blocksLimit, blockId);
//            k++;
//        }
//    }
//}

///**
// * Function that handles all the editing the user wishes to do on the generated hands
// * It handles the changes of blocks between the hands matrix and the game matrix
// * @param matrix is the game matrix with the unused blocks
// * @param hand is the matrix with all the hands generated
// * @param handSize is the size of each hand
// * @param numberOfHands is the number of hands existing
// * @return returns 0 if the user doesn't want to edit anything and 1 if the user edited something
// */
//int editHands(int matrix[][MAX2], int hand[][MAX3], int handSize, int numberOfHands) {
//    int i, j, handId = 0, removeId, addId = 0, blocksLimit, edited = 0, validate = 0, choice = 'y';
//    while (1) {
//        for (i = 0; i < numberOfHands; i++) {
//            printf("\n#%2d = Hand %d: ", i + 1, i + 1);
//            printHand(hand, handSize, i);
//        }
//        while (!validate) {
//            printf("\nDo you wish to change anything before proceeding? (Y/N): ");
//            getchar();
//            choice = getchar();
//            if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
//                printf("!!! Invalid answer !!!\n");
//                validate = 0;
//                continue;
//            }
//            validate = 1;
//        }
//        validate = 0;
//        if (choice == 'n') {
//            // if the user decided to not edit, since it's inside a loop, we need to check if he edited anything before
//            return edited;
//        }
//        if (numberOfHands > 1) {
//            printf("\nEnter the id of the hand to edit: ");
//            scanf("%d", &handId);
//            handId -= 1;
//            handId = (handId == 0 ? handId : handId *
//                                             handSize); // arithmetic to reach the desired hand on the matrix of hands
//        }
//        for (i = 0, j = handId; i < handSize; i++, j++) {
//            printf(" #%2d = [%d|%d]", i + 1, hand[j][0], hand[j][1]);
//        }
//        printf("\nWhich block do you want to change? ");
//        scanf("%d", &removeId);
//        removeId -= 1;
//        // to this removeId it's needed to add the previous handId index so we can reach the correct hand inside the hands matrix and then move the desired index
//        removeId += handId;
//        blocksLimit = blocksAvailable(matrix);
//        while (addId < 1 || addId > blocksLimit) {
//            printf("\nChoose a block to insert from the available blocks above: ");
//            scanf("%d", &addId);
//        }
//        addId -= 1;
//        // swaps the block chosen from the game matrix with the block chosen on the hand
//        i = matrix[addId][0];
//        j = matrix[addId][1];
//        matrix[addId][0] = hand[removeId][0];
//        matrix[addId][1] = hand[removeId][1];
//        hand[removeId][0] = i;
//        hand[removeId][1] = j;
//        edited = 1;
//        // reset variables
//        addId = 0;
//        removeId = 0;
//    }
//}

///**
// * Function that prints the allSequences matrix to show all of the sequences as the name refers
// * !! This function is only used for debugging/testing !!
// * @param matrix is the allSequences matrix
// * @param lines are the number of sequences on it
// * @param cols are the columns to print, maximum is 57
// */
//void printMatDefault(int matrix[][MAX57], int lines, int cols) {
//    int l = 0, c = 0;
//
//    for (l = 0; l < lines; l++) {
//        for (c = 0; c < cols && matrix[l][c] != -1; c++) {
//            printf("|%d ", matrix[l][c]);
//        }
//        printf("\n");
//    }
//
//}

/**
 * Fills a matrix with "-1" that we defined as the number that means the matrix is empty on that place
 * @param m is the matrix passed
 * @param lines are the lines of that matrix
 * @param cols are the columns of the matrix
 */
void initMat(int m[][MAX57], int lines, int cols) {
    int l = 0, c = 0;

    for (l = 0; l < lines; l++) {
        for (c = 0; c < cols; c++) {
            m[l][c] = -1;
        }
    }

}

/**
 *  Fills an array with "-1" that we defined as the number that means the matrix is empty on that place
 * @param array is the array passed
 */
void initArray(int array[MAX57]) {
    int i = 0;
    for (i = 0; i < MAX57; i++) {
        array[i] = -1;
    }
}

///**
// * Prints a certain array
// * !! This function is only used for debugging/testing !!
// * @param a is the array passed
// * @param N is the number of elements
// */
//void printArray(int *a, int N) {
//    int i;
//    for (i = 0; i < N; i++) {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
//}

/***
 * Function used by the qsort algorithm
 * @param a
 * @param b
 * @return
 */
int compareIntValues(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

/**
 *  Sorts integer arrays using the quick sort algorithm from the C library
 *  @param v integer array to sort
 *  @param n size of the array
 */
void sortIntArray(int *v, int n) {
    qsort(v, n, sizeof(int), compareIntValues);
}

// /**
//  * Function to generate sequences from one hand
//  * Checks if the block that is inserted in the sequence matrix is consistent, if it is tries to insert the next block
//  * if it's not consistent checks the next blocks for consistency with the last inserted block until a block is considered consistent
//  * than it inserts it in the sequence and each time a block is inserted in the sequence, the 3rd column of the hands matrix is changed to 0
//  * that means the block is currently being used
//  * That way when the algorithm runs again to check another block, it ignores the blocks that have that 3rd column at 0
//  * @param matrix Initial matrix (with the number of blocks existing at the time)
//  * @param handSize size of the hand
//  * @param sequence sequence matrix with the blocks that are consistent
//  * @param allSequences is the matrix that will store all the eligible sequences
//  * @param inserted number of blocks inserted in sequence matrix
//  * @return
//  */
//int generateSequence(int matrix[][MAX3], int handSize, int sequence[][MAX2], int allSequences[][MAX57], int inserted) {
//    int i = 0;
//
////    printf("\nMao:");
////    printMat(matrix, handSize);
////    printf("\n");
////    printf("Sequencia:");
////    printMat(sequence, inserted);
////    printf("\n");
//
//
//    for (i = 0; i < handSize; i++) {
//
////        se peca disponivel
//        if (matrix[i][2] == 1) {
//
//            sequence[inserted][0] = matrix[i][0];
//            sequence[inserted][1] = matrix[i][1];
//
////            printf("Iteracao (%d): \nPeça em jogo: [%d %d]\n", i, sequence[inserted][0], sequence[inserted][1]);
//
//            if (isConsistent(sequence, inserted) == 1) {
////                printf("Valor do I: %d\n", i);
//
//                inserted++;
//                matrix[i][2] = 0; // peca fica indisponivel
//                saveSequence(sequence, allSequences, inserted * 2, handSize);
//
////                printf("Peças inseridas: %d\n", inserted);
//
//                generateSequence(matrix, handSize, sequence, allSequences, inserted);
//
//
//                matrix[i][2] = 1; // colocar a peça que não deu na sequencia novamente disponivel
//                inserted--;
//            }
//        }
//    }
//    printf("allSequences --------:\n");
//    printMatDefault(allSequences, 100, 57);
//    printf("\n");
//    return 0;
//}

// /**
//  * Function responsible for storing all eligible sub-sequences / sequences in the sequences matrix
//  * Inserts in the first column of all sequences the size of it
//  * All the columns not used for a certain sequence (since the matrix that is storing them has to have a maximum size)
//  * are going to be "-1" to be considered "empty" spaces
//  * @param sequence is the sequence that is going to be stored
//  * @param allSequences is the matrix that stores all the sequences
//  * @param sizeOfSequence the size of the sequence to store
//  * @param handSize is the size of the hands, required for some conditions
//  */
//void saveSequence(int sequence[][MAX2], int allSequences[][MAX57], int sizeOfSequence, int handSize) {
//    int i = 0, j = 0, k = 0;
////    procuro ate encontrar o primiero -1, que sera a primeira linha livre para guardar a sequencia em questao
//    while (allSequences[i][0] != -1) {
//        i++; // incremento primeiro pois a proxima linha pode ser a disponivel para guardar a sequencia
////        if (allSequences[i][0] == -1 && handSize <= 10) {
////            allSequences[i][0] = sizeOfSequence;
////            for (j = 1, k = 0; j < sizeOfSequence; j += 2, k++) {
////                allSequences[i][j] = sequence[k][0];
////                allSequences[i][j + 1] = sequence[k][1];
////            }
////            return;
////        }
//
////        se a mao de jogo for maior que 10 só grava as sequencias maiores que metade do tamanho da mao
////        o tamanho de uma sequencia é duas vezes o numero de peças, ao comparar o handSize queremos sequencias com metade do tamanaho da mao
//        printf("handSize: %d\n", handSize);
//        printf("sizeofsequence: %d\n", sizeOfSequence);
//        if (allSequences[i][0] == -1 && (sizeOfSequence >= handSize )) {
//            allSequences[i][0] = sizeOfSequence;
//            for (j = 1, k = 0; j < sizeOfSequence; j += 2, k++) {
//                allSequences[i][j] = sequence[k][0];
//                allSequences[i][j + 1] = sequence[k][1];
//            }
//            return;
//        }
//
//
//    }
////    se for a primeira insiro na primeira linha ele nem vai entrar no clico while de cima por isso insiro a sequencia
//    if (i == 0 && (sizeOfSequence >= handSize )) {
//        allSequences[i][0] = sizeOfSequence;
//        for (j = 1, k = 0; j < sizeOfSequence; j += 2, k++) {
//            allSequences[i][j] = sequence[k][0];
//            allSequences[i][j + 1] = sequence[k][1];
//        }
//    }
//
//}

// /**
//  * Function responsible for sorting the allSequences matrix in descending order of the size of each sequences
//  * Orders by an ordered array that has the size of each hand, and searches in the first column of the allSequences matrix that size
//  * @param allSequences matrix that has all the sequences and sub-sequences
//  */
//void sortAllSequences(int allSequences[][MAX57]) {
//    int numberOfSequences = 0, j = 0, k = 0, l = 0, m = 0, arraySorted[MAX2000], auxMatrix[MAX2000][MAX57];
//    while (allSequences[numberOfSequences][0] != -1) {
//        arraySorted[numberOfSequences] = allSequences[numberOfSequences][0];
//        numberOfSequences++;
//
//    }
////    printf("Number of Sequences generated: %d\n", numberOfSequences);
//    // order array by descending order -> quick sort
////    sortIntArray(arraySorted, numberOfSequences);
////    printf("\nAux sorted:");
////    printArray(arraySorted, numberOfSequences);
////    printf("\n");
//
////    printf("allSequences for sort:\n");
////    printMatDefault(allSequences, numberOfSequences, 56);
////    printf("\n");
//    // fills an auxiliar matrix with -1
//    initMat(auxMatrix, MAX2000, 57);
//    k = numberOfSequences - 1;
////    printf("Number of Sequences generated: %d\n", numberOfSequences);
//    for (j = 0; j < numberOfSequences; j++) {
//        if (arraySorted[k] == allSequences[j][0]) {
//            for (l = 0; l <= allSequences[j][0]; l++) {
//                auxMatrix[m][l] = allSequences[j][l];
//            }
//            allSequences[j][0] = -1;
//            m++; // increments a line in the auxiliar matrix
//            k--; // decrements a line in the arraySorted array
//            j = -1; // when this cycle ends it restarts the outer cycle so it starts searching the next sequence from the beginning
//            // (-1 because the cycle will still increment after this)
//        }
//    }
//    // copy back to allSequences matrix
//    for (j = 0; j < numberOfSequences; j++) {
//        for (l = 0; l <= auxMatrix[j][0]; l++) {
//            allSequences[j][l] = auxMatrix[j][l];
//        }
//        allSequences[j][l] = -1;
//
//    }
////    printf("allSequences:\n");
////    printMatDefault(allSequences, numberOfSequences, 57);
////    printf("\n");
//}


///***
// * verifica se uma determinada peça é consistente na sequencia de jogo
// *
// * @param sequence matriz sequencia de pecas consistentes
// * @param index posicao da peça a ser inserida
// * @return 1 se consistente
// */
// /**
//  * Checks if a block is consistent with the last placed block on the sequence matrix
//  * @param sequence is the matrix of the current sequence
//  * @param index is the index of the block to insert
//  * @return returns 1 if it is consistent, and 0 if not
//  */
//int isConsistent(int sequence[][MAX2], int index) {
//     // first block is always consistent
//    if (index == 0) {
//        return 1;
//    }
//    // if the left side of the block to insert is equal to the right side of the last block
//    else if (sequence[index - 1][1] == sequence[index][0]) {
//        return 1;
//    }
//    // if the right side of the block to insert is equal to the right side of the last block then invert the block and inserts it
//    else if (sequence[index - 1][1] == sequence[index][1]) {
//        invertBlock(sequence, index);
//        return 1;
//    }
//    // if it's the second block to be inserted and if it's not consistent, it's tested inverting the first block inserted
//    else if (index == 1 && sequence[index - 1][0] == sequence[index][0]) {
//        invertBlock(sequence, index - 1);
//        return 1;
//    }
//    // if the right side of the block is equal to the left side of the last block
//    else if (index == 1 && sequence[index - 1][0] == sequence[index][1]) {
//        invertBlock(sequence, index - 1);
//        invertBlock(sequence, index);
//        return 1;
//    }
//    // if it's not consistent
//    else {
//        return 0;
//    }
//}
//
// /**
//  * Inverts a block
//  * @param block is the block to be inverted
//  * @param index is the blocks' index on the matrix passed
//  */
//void invertBlock(int block[][MAX2], int index) {
//    int aux = 0;
//    aux = block[index][1];
//    block[index][1] = block[index][0];
//    block[index][0] = aux;
//
//}

///**
// * Opens the file with the name the user inputs if it exists, if not, keeps asking for a valid name
// * @param type type = 1 means it's a text file, type = 2 means it's a binary file
// * @param handsMat matrix where will be stored the hands stored in the file
// * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
// * @param numberOfHands number of hands in the hands matrix
// * @param handSize size of each hand
// */
//void openFile(char fileName[], int type, int hand[][MAX3], int gameMat[][MAX2], int *numberOfHands, int *handSize) {
//    FILE *file = NULL;
//    int i = 0, auxInt, j = 0;
//    char fOut[30];
//    char path[] = "data/";
//    strcat(path, fileName);
//    switch (type) {
//        // Text files
//        case 1:
//            checkExtension(fileName, ".txt");
//            if ((file = fopen(path, "r")) != NULL) {
//                while (fgets(fOut, 29, file)) {
//                    // first line of the file, to extract the size of each hand and how many hands there are
//                    if (i == 0) {
//                        // arithmetic to get the first 2 digits of the first line from char to int type (correspondent to the number of hands)
//                        *numberOfHands = fOut[0] - '0';
//                        *numberOfHands *= 10;
//                        *numberOfHands += (fOut[1] - '0');
//                        // arithmetic to get the second 2 digits of the first line from char to int type (correspondent to the hands size)
//                        *handSize = fOut[2] - '0';
//                        *handSize *= 10;
//                        *handSize += (fOut[3] - '0');
//                        // saves the matrix of the hands that are after the first line until (numberOfHands*handSize) lines
//                    } else if (i < ((*numberOfHands) * (*handSize)) + 1) {
//                        hand[i - 1][0] = fOut[0] - '0';
//                        hand[i - 1][1] = fOut[1] - '0';
//                    } else {
//                        gameMat[j][0] = fOut[0] - '0';
//                        gameMat[j][1] = fOut[1] - '0';
//                        j++;
//                    }
//                    i++;
//                }
//                // compresses the game matrix to the size extracted from the file
//                compressMatrix(gameMat, j, -1);
//                // fills the 3rd column of the hands matrix with 1 necessary for the generate sequence function
//                fillHands(hand, *handSize, *numberOfHands);
//            }
//            fclose(file);
//            break;
//
//            // Binary files
//        case 2:
//            checkExtension(fileName, ".bin");
//            if ((file = fopen(path, "rb")) != NULL) {
//                while (!feof(file)) {
//                    if (i == 0) {
//                        fread(numberOfHands, sizeof(int), 1, file);
//                        fread(handSize, sizeof(int), 1, file);
//                    } else if (i < ((*numberOfHands) * (*handSize)) + 1) {
//                        fread(&auxInt, sizeof(int), 1, file);
//                        hand[i - 1][0] = auxInt;
//                        fread(&auxInt, sizeof(int), 1, file);
//                        hand[i - 1][1] = auxInt;
//                    } else {
//                        fread(&auxInt, sizeof(int), 1, file);
//                        gameMat[j][0] = auxInt;
//                        fread(&auxInt, sizeof(int), 1, file);
//                        gameMat[j][1] = auxInt;
//                        j++;
//                    }
//                    i++;
//                }
//                // compresses the game matrix to the size extracted from the file
//                // needed to decrese by 1 the size because of the cycles the reading does
//                compressMatrix(gameMat, j - 1, -1);
//            }
//            fclose(file);
//            break;
//
//        default:
//            break;
//    }
//}
//
///**
// * Rewrites the file the user loaded with the new hands and game matrix after he edited them
// * @param fileName name of the file to edit
// * @param type the type of file (txt or bin)
// * @param handsMat matrix where will be stored the hands stored in the file
// * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
// * @param numberOfHands number of hands in the hands matrix
// * @param handSize size of each hand
// */
//void editFile(char fileName[], int type, int hand[][MAX3], int gameMat[][MAX2], int numberOfHands, int handSize) {
//    FILE *file = NULL;
//    int i = 0, auxInt;
//    char path[40] = "data/";
//    strcat(path, fileName);
//    switch (type) {
//        // Text files
//        case 1:
//            if (!fileExists(path)) {
//                printf("\nxx Error: The file '%s' doesnt exist xx\n", fileName);
//                return;
//            }
//            if ((file = fopen(path, "w")) != NULL) {
//                // stores the numberOfHands and the handSize
//                // checks if the number is 2 digit or not, if not, adds a 0 before, so we maintain the structure
//                if (numberOfHands / 10 == 0) {
//                    fprintf(file, "0%d", numberOfHands);
//                } else {
//                    fprintf(file, "%d", numberOfHands);
//                }
//                if (handSize / 10 == 0) {
//                    fprintf(file, "0%d", handSize);
//                } else {
//                    fprintf(file, "%d", handSize);
//                }
//                // stores the matrix of the hands generated
//                for (i = 0; i < (numberOfHands * handSize); i++) {
//                    fprintf(file, "\n%d%d", hand[i][0], hand[i][1]);
//                }
//                // stores the game matrix with the unused blocks
//                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
//                    fprintf(file, "\n%d%d", gameMat[i][0], gameMat[i][1]);
//                }
//            } else {
//                printf("\nxx Error: Impossible to write to the file '%s' xx\n", fileName);
//                return;
//            }
//            fclose(file);
//            break;
//
//        // Binary files
//        case 2:
//            if (!fileExists(path)) {
//                printf("\nxx Error: The file '%s' doesnt exist xx\n", fileName);
//                return;
//            }
//            if ((file = fopen(path, "wb")) != NULL) {
//                // stores the numberOfHands and the handSize
//                fwrite(&numberOfHands, sizeof(int), 1, file);
//                fwrite(&handSize, sizeof(int), 1, file);
//                // stores the matrix of the hands generated
//                for (i = 0; i < (numberOfHands * handSize); i++) {
//                    auxInt = hand[i][0];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                    auxInt = hand[i][1];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                }
//                // stores the game matrix with the unused blocks
//                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
//                    auxInt = gameMat[i][0];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                    auxInt = gameMat[i][1];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                }
//            } else {
//                printf("\nxx Error: Impossible to write to the file '%s' xx\n", fileName);
//                return;
//            }
//            fclose(file);
//            break;
//
//        default:
//            break;
//    }
//}
//
///**
// *  Creates a file with the game generated and the name and type of file the user chooses
// *  Afterwards the user can load the game, edit it and play
// * @param type the type of file (txt or bin)
// * @param handsMat matrix where will be stored the hands stored in the file
// * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
// * @param numberOfHands number of hands in the hands matrix
// * @param handSize size of each hand
// */
//void createGameFile(int type, int hand[][MAX3], int gameMat[][MAX2], int numberOfHands, int handSize) {
//    FILE *file = NULL;
//    int i = 0, auxInt;
//    char fileName[40], path[40] = "data/";
//    switch (type) {
//        // create txt file
//        case 1:
//            printf("\nSave the game as: ");
//            scanf("%s", fileName);
//            checkExtension(fileName, ".txt");
//            strcat(path, fileName);
//            if (fileExists(path)) {
//                printf("\nxx Error: The file '%s' already exists xx\n", fileName);
//                createGameFile(type, hand, gameMat, numberOfHands, handSize);
//                return;
//            }
//            if ((file = fopen(path, "w")) != NULL) {
//                // stores the numberOfHands and the handSize
//                // checks if the number is 2 digit or not, if not, adds a 0 before, so we maintain the structure
//                if (numberOfHands / 10 == 0) {
//                    fprintf(file, "0%d", numberOfHands);
//                } else {
//                    fprintf(file, "%d", numberOfHands);
//                }
//                if (handSize / 10 == 0) {
//                    fprintf(file, "0%d", handSize);
//                } else {
//                    fprintf(file, "%d", handSize);
//                }
//                // stores the matrix of the hands generated
//                for (i = 0; i < (numberOfHands * handSize); i++) {
//                    fprintf(file, "\n%d%d", hand[i][0], hand[i][1]);
//                }
//                // stores the game matrix with the unused blocks
//                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
//                    fprintf(file, "\n%d%d", gameMat[i][0], gameMat[i][1]);
//                }
//            } else {
//                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
//                createGameFile(type, hand, gameMat, numberOfHands, handSize);
//            }
//            fclose(file);
//            break;
//
//        // create bin file
//        case 2:
//            printf("\nSave the game as: ");
//            scanf("%s", fileName);
//            checkExtension(fileName, ".bin");
//            strcat(path, fileName);
//            if (fileExists(path)) {
//                printf("\nxx Error: The file '%s' already exists xx\n", fileName);
//                createGameFile(type, hand, gameMat, numberOfHands, handSize);
//                return;
//            }
//            if ((file = fopen(path, "wb")) != NULL) {
//                // stores the numberOfHands and the handSize
//                fwrite(&numberOfHands, sizeof(int), 1, file);
//                fwrite(&handSize, sizeof(int), 1, file);
//                // stores the matrix of the hands generated
//                for (i = 0; i < (numberOfHands * handSize); i++) {
//                    auxInt = hand[i][0];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                    auxInt = hand[i][1];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                }
//                // stores the game matrix with the unused blocks
//                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
//                    auxInt = gameMat[i][0];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                    auxInt = gameMat[i][1];
//                    fwrite(&auxInt, sizeof(int), 1, file);
//                }
//            } else {
//                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
//                createGameFile(type, hand, gameMat, numberOfHands, handSize);
//            }
//            fclose(file);
//            break;
//
//        default:
//            break;
//    }
//}

/**
 * checks the filename the user inputted for the extension and if it doesn't exist adds it at the end
 * @param fileName name of the file requested by the user
 */
void checkExtension(char fileName[], char extension[]) {
    if (strstr(fileName, extension) == NULL) { // searches for the extension in the filename the user inputted
        strcat(fileName, extension);
    }
}

/**
 * tries to open a file with the name inputted to check if it exists before writing on it
 * prevents rewriting on an existing file with the name the user wrote
 * @param fileName
 * @return returns 0 if there's no file with that name and 1 if there is
 */
int fileExists(char fileName[]) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) return 0;
    return 1;
}

/**
 * Puts the 3rd column of the hands matrix equals to 1 to use on the generate sequence logic
 * @param hand matrix with the hands
 * @param handSize size of each hand
 * @param numberOfHands number of hands
 */
void fillHands(int hand[][MAX3], int handSize, int numberOfHands){
    int i;
    for (i = 0; i < (handSize*numberOfHands); i++) {
        hand[i][2] = 1; // 3rd column
    }
}