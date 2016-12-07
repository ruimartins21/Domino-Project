/// @file core.c
/// @brief Gathers all the core functions of the project
/// @copyright

#include "core.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Function that generates player hand randomly
 * -> Runs the number of hands chosen by the user, for each one runs all the blocks of the hand
 * -> Generates a random number confined to the values 0 to 27
 * -> Drops index of generated number from the deck and puts it on the player hand
 * -> Compresses Matrix and inserts "-1" in the last position according to the number of lines withdrawned
 *
 * @param matrix Initial game matrix (all pieces)
 * @param hand Matrix with the player pieces (hand game)
 * @param linesHand Matrix lines of the player hand
 * @param qtSet Number of hands to generate
 */
void generateRandomHand(GAME *game, HANDS *hands) {
    int l = 0, j = 0, randValue = 0, linesCount = 0;
    HAND *handAux = NULL;
    BLOCK *blockAux = NULL;
    BLOCK *delBlock = NULL;
    hands->pfirstHand = (HAND*)malloc(sizeof(HAND)); // allocates space for the first hand
    handAux = hands->pfirstHand;
    for (j = 0; j < hands->numberOfHands; j++) {
        handAux->pfirstBlock = (BLOCK*) malloc(sizeof(BLOCK)); // allocates space for the first block
        blockAux = handAux->pfirstBlock;
        for (l = 0; l < hands->handSize; l++) {
            randValue = 0 + rand() % ((MAX28-1) - linesCount);
            delBlock = popBlock(game,randValue);
            blockAux->leftSide  = delBlock->leftSide;
            blockAux->rightSide = delBlock->rightSide;
            blockAux->available = 1;
            free(delBlock);
            blockAux->pnextBlock = (BLOCK*)malloc(sizeof(BLOCK));
            blockAux = blockAux->pnextBlock;
            linesCount++;
        }
        if(j+1 == hands->numberOfHands){ // if the cycle will end at the next increment, the next pointer will be NULL
            handAux->pnextHand = NULL;
        }else{
            handAux->pnextHand = (HAND*)malloc(sizeof(HAND));
            handAux = handAux->pnextHand;
        }
    }
}

/**
  * Function to generate sequences from one hand
  * Checks if the block that is inserted in the sequence matrix is consistent, if it is tries to insert the next block
  * if it's not consistent checks the next blocks for consistency with the last inserted block until a block is considered consistent
  * than it inserts it in the sequence and each time a block is inserted in the sequence, the 3rd column of the hands matrix is changed to 0
  * that means the block is currently being used
  * That way when the algorithm runs again to check another block, it ignores the blocks that have that 3rd column at 0
  * @param matrix Initial matrix (with the number of blocks existing at the time)
  * @param handSize size of the hand
  * @param sequence sequence matrix with the blocks that are consistent
  * @param allSequences is the matrix that will store all the eligible sequences
  * @param inserted number of blocks inserted in sequence matrix
  * @return
  */
int generateSequence(int matrix[][MAX3], int handSize, int sequence[][MAX2], int allSequences[][MAX57], int inserted) {
    int i = 0;
    for (i = 0; i < handSize; i++) {
        // if the block is available
        if (matrix[i][2] == 1) {
            sequence[inserted][0] = matrix[i][0];
            sequence[inserted][1] = matrix[i][1];
            if (isConsistent(sequence, inserted) == 1) {
                inserted++;
                matrix[i][2] = 0; // block is now unavailable
                saveSequence(sequence, allSequences, inserted * 2, handSize);
                generateSequence(matrix, handSize, sequence, allSequences, inserted);
                matrix[i][2] = 1; // block is available if it didn't fit
                inserted--;
            }
        }
    }
    return 0;
}

/**
 * Function responsible for storing all eligible sub-sequences / sequences in the sequences matrix
 * Inserts in the first column of all sequences the size of it
 * All the columns not used for a certain sequence (since the matrix that is storing them has to have a maximum size)
 * are going to be "-1" to be considered "empty" spaces
 * @param sequence is the sequence that is going to be stored
 * @param allSequences is the matrix that stores all the sequences
 * @param sizeOfSequence the size of the sequence to store
 * @param handSize is the size of the hands, required for some conditions
 */
void saveSequence(int sequence[][MAX2], int allSequences[][MAX57], int sizeOfSequence, int handSize) {
    int i = 0, j = 0, k = 0;
    // searches until it finds the first -1, that will be the first available line to store the new sequence
    while (allSequences[i][0] != -1) {
        i++; // increments before anything else because if the first line is available it will jump to the next condition and won't enter the while
        if (allSequences[i][0] == -1 ) {
            allSequences[i][0] = sizeOfSequence;
            for (j = 1, k = 0; j < sizeOfSequence; j += 2, k++) {
                allSequences[i][j] = sequence[k][0];
                allSequences[i][j + 1] = sequence[k][1];
            }
            return;
        }
    }
    // if it's the first line of the matrix it will jump out of the previous while and will insert the sequence here
    if (i == 0) {
        allSequences[i][0] = sizeOfSequence;
        for (j = 1, k = 0; j < sizeOfSequence; j += 2, k++) {
            allSequences[i][j] = sequence[k][0];
            allSequences[i][j + 1] = sequence[k][1];
        }
    }
}

/**
  * Function responsible for sorting the allSequences matrix in descending order of the size of each sequences
  * Orders by an ordered array that has the size of each hand, and searches in the first column of the allSequences matrix that size
  * @param allSequences matrix that has all the sequences and sub-sequences
  */
int sortAllSequences(int allSequences[][MAX57]) {
    int numberOfSequences = 0, j = 0, k = 0, l = 0, m = 0, arraySorted[MAX2000], auxMatrix[MAX2000][MAX57];
    while (allSequences[numberOfSequences][0] != -1) {
        arraySorted[numberOfSequences] = allSequences[numberOfSequences][0];
        numberOfSequences++;

    }
    // order array by descending order -> quick sort
    sortIntArray(arraySorted, numberOfSequences);
    // fills an auxiliary matrix with -1
    initMat(auxMatrix, MAX2000, 57);
    k = numberOfSequences - 1;
    for (j = 0; j < numberOfSequences; j++) {
        if (arraySorted[k] == allSequences[j][0]) {
            for (l = 0; l <= allSequences[j][0]; l++) {
                auxMatrix[m][l] = allSequences[j][l];
            }
            allSequences[j][0] = -1;
            m++; // increments a line in the auxiliary matrix
            k--; // decrements a line in the arraySorted array
            j = -1; // when this cycle ends it restarts the outer cycle so it starts searching the next sequence from the beginning
            // (-1 because the cycle will still increment after this)
        }
    }
    // copy back to allSequences matrix
    for (j = 0; j < numberOfSequences; j++) {
        for (l = 0; l <= auxMatrix[j][0]; l++) {
            allSequences[j][l] = auxMatrix[j][l];
        }
        allSequences[j][l] = -1;
    }
    printf("\t\t\t# Number of sequences generated: %d #\n", numberOfSequences);
    return numberOfSequences;
}

/**
 * Checks if a block is consistent with the last placed block on the sequence matrix
 * @param sequence is the matrix of the current sequence
 * @param index is the index of the block to insert
 * @return returns 1 if it is consistent, and 0 if not
 */
int isConsistent(int sequence[][MAX2], int index) {
    // first block is always consistent
    if (index == 0) {
        return 1;
    }
        // if the left side of the block to insert is equal to the right side of the last block
    else if (sequence[index - 1][1] == sequence[index][0]) {
        return 1;
    }
        // if the right side of the block to insert is equal to the right side of the last block then invert the block and inserts it
    else if (sequence[index - 1][1] == sequence[index][1]) {
        invertBlock(sequence, index);
        return 1;
    }
        // if it's the second block to be inserted and if it's not consistent, it's tested inverting the first block inserted
    else if (index == 1 && sequence[index - 1][0] == sequence[index][0]) {
        invertBlock(sequence, index - 1);
        return 1;
    }
        // if the right side of the block is equal to the left side of the last block
    else if (index == 1 && sequence[index - 1][0] == sequence[index][1]) {
        invertBlock(sequence, index - 1);
        invertBlock(sequence, index);
        return 1;
    }
        // if it's not consistent
    else {
        return 0;
    }
}

/**
 * Inverts a block
 * @param block is the block to be inverted
 * @param index is the blocks' index on the matrix passed
 */
void invertBlock(int block[][MAX2], int index) {
    int aux = 0;
    aux = block[index][1];
    block[index][1] = block[index][0];
    block[index][0] = aux;
}