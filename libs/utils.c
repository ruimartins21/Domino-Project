/// @file utils.c
/// @brief File that gathers all the utilities function used in the core project functions
/// @copyright

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Generates initial game matrix
 * @param pieces matrix to store the generated numbers
 * @return default (0): filled matrix is stored via its addresses so it isn't needed to return anything
 */
void getGame(GAME *game) {
    int l, c;
    BLOCK *paux = NULL;
    game->availableBlocks = MAX28;
    game->pblocks = (BLOCK*)malloc(sizeof(BLOCK)*MAX28);
    paux = game->pblocks;
    for (l = 0; l <= 6; l++) {
        for (c = l; c <= 6; c++) {
            paux->leftSide = l;
            paux->rightSide = c;
            paux->available = 1;
            paux->pnextBlock = NULL;
            paux++;
        }
    }
}

void printGame(GAME game){
    BLOCK *paux = game.pblocks;
    int i = game.availableBlocks;
    while(i != 0){
        printf("[%d, %d]\n", paux->leftSide, paux->rightSide);
        paux++;
        i--;
    }
}
void printHand(HANDS hands){
    HAND *handAux = hands.pfirstHand;
    BLOCK *blockAux = NULL;
    int i,j;
    for (i = 0; i < hands.numberOfHands && handAux != NULL; i++) {
        blockAux = handAux->pfirstBlock;
        for (j = 0; j < hands.handSize; j++) {
            printf("[%d, %d]\n", blockAux->leftSide, blockAux->rightSide);
            blockAux++;
        }
        printf("\n");
        handAux = handAux->pnextHand;
    }
}

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
//void fillHands(int hand[][MAX3], int handSize, int numberOfHands){
//    int i;
//    for (i = 0; i < (handSize*numberOfHands); i++) {
//        hand[i][2] = 1; // 3rd column
//    }
//}