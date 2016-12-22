/// @file core.c
/// @brief Gathers all the core functions of the project
/// @copyright

#include "core.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * Function that generates player hand randomly
 * -> Runs the number of hands chosen by the user, for each one runs all the blocks of the hand
 * -> Generates a random number confined to the values 0 to 27
 * -> Returns the block positioned at the index generated and copies its content to another place and frees the space on memory of the previous one
 *
 * @param matrix Initial game matrix (all pieces)
 * @param hand Matrix with the player pieces (hand game)
 * @param linesHand Matrix lines of the player hand
 * @param qtSet Number of hands to generate
 */
void generateRandomHand(GAME *game, HANDS *hands) {

    long ultime;
    time(&ultime);
    srand((unsigned)ultime);

    int i = 0, j = 0, randValue = 0, linesCount = 0;
    HAND *handAux = NULL;
    BLOCK *delBlock = NULL, *blockAux = NULL;
    hands->pfirstHand = NULL;
    for (i = 0; i < hands->numberOfHands; i++) {
        handAux = (HAND*)malloc(sizeof(HAND));
        for (j = 0; j < hands->handSize; j++) {
            if(linesCount < 27){
                randValue = 0 + rand() % ((MAX28-1) - linesCount); // it needs to be sent MAX28 - 1 because the popBlock function works with numbers between 0 and 27
            }else{
                randValue = 0;
            }
            delBlock = popBlock(game, randValue); // retrieves the block to pass it to the hand and remove from the game structure
            blockAux = transferBlock(delBlock);
            if(handAux->pfirstBlock == NULL){ // it's the first block to be inserted in the hand
                blockAux->pnextBlock = NULL; // it will be used the insertion at the head, so the first block to be inserted will be the one at the tail
            }else{
                blockAux->pnextBlock = handAux->pfirstBlock;
            }
            handAux->pfirstBlock = blockAux;
            linesCount++;
        }
        handAux->pnextHand = hands->pfirstHand;
        hands->pfirstHand  = handAux;
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

int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, int *count) {
    int i = 0;
    BLOCK *blockAux = NULL;
    HAND *handAux = NULL;

    handAux = pHands->pfirstHand; // vai ser usado para varias maos
    blockAux = handAux->pfirstBlock;

    for (i = 0; i < pHands->handSize; i++) {
//         if the block is available
        if (blockAux->available == 1) {

            BLOCK *pnew = (BLOCK *) malloc(sizeof(BLOCK));
//            nova peca a inserir na sequencia
            pnew->leftSide = blockAux->leftSide;
            pnew->rightSide = blockAux->rightSide;
            pnew->available = 0;
            pnew->pnextBlock = NULL;
            pnew->prevBlock = NULL;

//            tenho que mandar a ultima peca da sequencia
            if (isConsistent(pSequence, pnew, inserted) == 1) {
                if(inserted == 0) { // se for a primeira peça na sequencia

                    pSequence->pfirstBlock = pnew;
                    pSequence->pfirstBlock->pnextBlock = pnew;
                    pSequence->pfirstBlock->prevBlock = pnew;
                }else{
                    pSequence->pfirstBlock->prevBlock->pnextBlock = pnew;
                    pnew->prevBlock = pSequence->pfirstBlock->prevBlock;
                    pnew->pnextBlock = pSequence->pfirstBlock;
                    pSequence->pfirstBlock->prevBlock = pnew;
                }


                inserted++;
                pSequence->sizeOfSequence++;
                blockAux->available = 0; // block is now unavailable

                if(pSequence->sizeOfSequence == pHands->handSize)
                    (*count)++;

                printSequence(*pSequence);

                saveSequence(pAllsequences, pSequence);
                generateSequence(pHands, pSequence, pAllsequences, inserted, count);

                BLOCK *paux = pSequence->pfirstBlock->prevBlock;
                blockAux->available = 1; // block is available if it didn't fit
                pSequence->pfirstBlock->prevBlock = pSequence->pfirstBlock->prevBlock->prevBlock;
                pSequence->pfirstBlock->prevBlock->pnextBlock = pSequence->pfirstBlock;
                free(paux);
//                pSequence->pfirstBlock->prevBlock->prevBlock = pSequence->pfirstBlock->prevBlock->pnextBlock;
//                free()
//                pSequence->pfirstBlock->prevBlock = pSequence->pfirstBlock->prevBlock->prevBlock;
//                pSequence->pfirstBlock->prevBlock = pSequence->pfirstBlock->prevBlock->pnextBlock->pnextBlock;
                pSequence->sizeOfSequence --;
                inserted--;
//                printSequence(*pSequence);
            }
        }
        if(blockAux->pnextBlock != NULL)
            blockAux = blockAux->pnextBlock;
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
void saveSequence(ALLSEQUENCES *allSequences, SEQUENCE *pSequence) {
//    if( allSequences->numberOfSequences < MAX5000){
        SEQUENCE *pnew = (SEQUENCE*)malloc(sizeof(SEQUENCE));
        *pnew = *pSequence;
        if(allSequences->pfirstSequence == NULL){
            allSequences->pfirstSequence = pnew;
            allSequences->numberOfSequences++;
            return;
        }
        pnew->pnextSequence = allSequences->pfirstSequence;
        allSequences->pfirstSequence = pnew;
        allSequences->numberOfSequences++;

    sortAllSequences(allSequences);

//    } else if(allSequences->numberOfSequences == MAX5000){
//        printf("chegou aos 5000\n");

//    printAllSequence(*allSequences);

//        FILE *fp=NULL;
//        SEQUENCE *pauxSequence = allSequences->pfirstSequence;
//        int i = 0;
//        fp=fopen("/Users/ruimartins/ClionProjects/Domino-Project/data/teste.txt","w");
//
//        fprintf(fp,"\ntotal de sequencias:%d\n", allSequences->numberOfSequences);
//
//        BLOCK *blockAux = pauxSequence->pfirstBlock;
//        while (pauxSequence != NULL && allSequences->numberOfSequences < MAX5000){
//            for (i = 0; i < pauxSequence->sizeOfSequence; i++) {
//                printf("[%d, %d]", blockAux->leftSide, blockAux->rightSide);
//                blockAux = blockAux->pnextBlock;
//            }
//            printf("\n");
//            pauxSequence = pauxSequence->pnextSequence;
//        }

//    }



}

/**
  * Function responsible for sorting the allSequences matrix in descending order of the size of each sequences
  * Orders by an ordered array that has the size of each hand, and searches in the first column of the allSequences matrix that size
  * @param allSequences matrix that has all the sequences and sub-sequences
  */
//

void sortAllSequences(ALLSEQUENCES *allSequences) {


}


/**
 * Checks if a block is consistent with the last placed block on the sequence matrix
 * @param sequence is the matrix of the current sequence
 * @param index is the index of the block to insert
 * @return returns 1 if it is consistent, and 0 if not
// */
int isConsistent(SEQUENCE *pSequence, BLOCK *newBlock, int inserted) {
    // first block is always consistent
    if (inserted == 0) {
        return 1;
    }

        // if the left side of the block to insert is equal to the right side of the last block
    if (newBlock->leftSide == pSequence->pfirstBlock->prevBlock->rightSide) {
        return 1;
    }
        // if the right side of the block to insert is equal to the right side of the last block then invert the block and inserts it
    else if (newBlock->rightSide == pSequence->pfirstBlock->prevBlock->rightSide) {
        invertBlock(newBlock);
        return 1;
    }
        // if it's the second block to be inserted and if it's not consistent, it's tested inverting the first block inserted
    else if (inserted == 1 && newBlock->leftSide == pSequence->pfirstBlock->leftSide ) {
        invertBlockSequence(pSequence);
        return 1;
    }
        // if the right side of the block is equal to the left side of the last block
    else if (inserted == 1 && newBlock->rightSide == pSequence->pfirstBlock->leftSide ) {
        invertBlockSequence(pSequence);
        invertBlock(newBlock);
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

void invertBlock(BLOCK *pBlock) {
    int aux = 0;
    aux = pBlock->leftSide;
    pBlock->leftSide = pBlock->rightSide;
    pBlock->rightSide = aux;
}

void invertBlockSequence(SEQUENCE *pSequence) {
    int aux = 0;
    aux = pSequence->pfirstBlock->leftSide;
    pSequence->pfirstBlock->leftSide = pSequence->pfirstBlock->rightSide;
    pSequence->pfirstBlock->rightSide = aux;
}