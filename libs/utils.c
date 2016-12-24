/// @file utils.c
/// @brief File that gathers all the utilities function used in the core project functions
/// @copyright

#include "utils.h"
#include <stdio.h>

#ifdef WIN32
int gettimeuseconds(long long * time_usec) {
    union {
        long long ns100; //time since 1 Jan 1601 in 100ns units
        FILETIME ft;
    } now;

    GetSystemTimeAsFileTime( &(now.ft) ); // win32 function!
    *time_usec=(long long) (now.ns100 / 10LL);
    return 0;
}
#else
int gettimeuseconds(long long * time_usec) {
    struct timeval time;
    gettimeofday(&time,NULL);

    *time_usec=(long long) (time.tv_sec * 1000000 + time.tv_usec);
    return 0;
}
#endif

/**
 * Generates initial game matrix
 * @param pieces matrix to store the generated numbers
 * @return default (0): filled matrix is stored via its addresses so it isn't needed to return anything
 */
void getGame(GAME *game) {
    int l, c, i = 0;
    BLOCK *blockAux = NULL;
    game->availableBlocks = MAX28;
    game->pfirstBlock = (BLOCK*)malloc(sizeof(BLOCK));
    blockAux = game->pfirstBlock;
    for (l = 0; l <= 6; l++) {
        for (c = l; c <= 6; c++) {
            blockAux->leftSide   = l;
            blockAux->rightSide  = c;
            blockAux->available  = 1;
            blockAux->prevBlock  =  NULL;
            if(i == 27){
                blockAux->pnextBlock = NULL;
            }else{
                blockAux->pnextBlock = (BLOCK*)malloc(sizeof(BLOCK));
                blockAux             = blockAux->pnextBlock;
            }
            i++;
        }
    }
}

void printGame(GAME game){
    BLOCK *blockAux = game.pfirstBlock;
    while(blockAux != NULL){
        printf("[%d, %d]\n", blockAux->leftSide, blockAux->rightSide);
        blockAux = blockAux->pnextBlock;
    }
}

void printHand(HANDS hands){
    HAND  *handAux  = hands.pfirstHand;
    BLOCK *blockAux = NULL;
    int i,j;
    for (i = 0; i < hands.numberOfHands && handAux != NULL; i++) {
        blockAux = handAux->pfirstBlock;
        for (j = 0; j < hands.handSize; j++) {
            printf("[%d, %d] [%d]\n", blockAux->leftSide, blockAux->rightSide, blockAux->available);
            blockAux = blockAux->pnextBlock;
        }
        printf("\n");
        handAux = handAux->pnextHand;
    }
}

void printSingleHand(HAND hand, int handSize){
    BLOCK *pblock = hand.pfirstBlock;
    int i;
    for (i = 0; i < handSize && pblock != NULL; i++) {
        printf("[%d , %d] ", pblock->leftSide, pblock->rightSide);
        pblock = pblock->pnextBlock;
    }
}

void printSequence(SEQUENCE sequence){
    BLOCK *blockAux = sequence.pfirstBlock;;
    int i;
    for (i = 0; i < sequence.sizeOfSequence; i++) {
        printf("[%d, %d]", blockAux->leftSide, blockAux->rightSide);
        blockAux = blockAux->pnextBlock;
    }
    printf("\n");
}

void printAllSequence(ALLSEQUENCES allsequences){
    SEQUENCE *pauxSequence = allsequences.pfirstSequence;
    BLOCK *blockAux = pauxSequence->pfirstBlock;;
    int i;
    while (pauxSequence != NULL){
        for (i = 0; i < pauxSequence->sizeOfSequence; i++) {
            printf("[%d, %d]", blockAux->leftSide, blockAux->rightSide);
            blockAux = blockAux->pnextBlock;
        }
        printf("\n");
        pauxSequence = pauxSequence->pnextSequence;
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
//void compressMatrix(int matrix[][MAX2], int lines, int index) {
//    int i;
//    if (index == -1) {
//        // it will compress the matrix to the size given from the lines parameter
//        // after the size given fills with -1 until the limit size (28)
//        for (i = lines; i < (lines + (28 - lines)); i++) {
//            matrix[i][0] = -1;
//            matrix[i][1] = -1;
//        }
//    } else {
//        for (; index < lines; index++) {
//            matrix[index][0] = matrix[index + 1][0];
//            matrix[index][1] = matrix[index + 1][1];
//        }
//        matrix[index - 1][0] = -1;
//        matrix[index - 1][1] = -1;
//    }
//}

/**
 * Returns a certain block at the index given and removes it from the linked list
 * @param game structure that has the non-used blocks
 * @param index position of the block to pop
 * @return returns the block that corresponds to the index
 */
BLOCK *popBlock(GAME *game, int index){
    int i = 0;
    if(index > game->availableBlocks){
        printf("\n!! The block you are trying to get isn't available !!\n");
        return NULL;
    }
    BLOCK *blockAux = game->pfirstBlock;
    BLOCK *blockAuxPrev = NULL;
    while(i != index && blockAux != NULL){
        blockAuxPrev = blockAux;
        blockAux = blockAux->pnextBlock;
        i++;
    }
    if(blockAux != NULL){
        if(blockAuxPrev == NULL){// if the index is for the first block
            game->pfirstBlock = blockAux->pnextBlock;
        }else{
            blockAuxPrev->pnextBlock = blockAux->pnextBlock;
        }
//        if(blockAuxPrev == NULL && blockAux->pnextBlock == NULL) { // if the index is for the first block AND there's only one block
//            game->pfirstBlock = NULL;
//        }else if(blockAuxPrev == NULL){// if the index is for the first block
//            game->pfirstBlock = blockAux->pnextBlock;
//        }else{
//            blockAuxPrev->pnextBlock = blockAux->pnextBlock;
//        }
    }else{
        return NULL;
    }
    game->availableBlocks -= 1;
    return blockAux;
}

/**
 * Receives a certain block to copy its content to a new one and to remove the previous one from the memory
 * @param delBlock is the block to be copied from and removed
 * @return returns the address of the new block
 */
BLOCK *transferBlock(BLOCK *delBlock){
    BLOCK *blockAux = (BLOCK*)malloc(sizeof(BLOCK));
    blockAux->leftSide   = delBlock->leftSide;
    blockAux->rightSide  = delBlock->rightSide;
    blockAux->available  = delBlock->available;
    blockAux->pnextBlock = NULL;
    blockAux->prevBlock = NULL;
    free(delBlock);
    return blockAux;
}

/**
 * Swaps the contents of the given block with the block existing in the game structure at the given index
 * @param handBlock is the block to wich will be copied the contents of the game block wanted
 * @param index is where the game block wanted is located
 */
void swapBlock(GAME *game, BLOCK *handBlock, int index){
    int i = 0;
    if(index > game->availableBlocks){
        printf("\n!! The block you are trying to get isn't available !!\n");
        return;
    }
    BLOCK *blockAux = game->pfirstBlock;
    BLOCK *blockTemp = (BLOCK*)malloc(sizeof(BLOCK));
    while(i != index && blockAux != NULL){
        blockAux = blockAux->pnextBlock;
        i++;
    }
    if(blockAux != NULL){
        // swapping manually because we don't want to change the pointers to the pnextSequence block
        blockTemp->leftSide  = handBlock->leftSide;
        blockTemp->rightSide = handBlock->rightSide;
        blockTemp->available = handBlock->available;
        handBlock->leftSide  = blockAux->leftSide;
        handBlock->rightSide = blockAux->rightSide;
        handBlock->available = blockAux->available;
        blockAux->leftSide   = blockTemp->leftSide;
        blockAux->rightSide  = blockTemp->rightSide;
        blockAux->available  = blockTemp->available;
    }
    free(blockTemp);
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