/// @file utils.c
/// @brief File that gathers all the utilities function used in the core project functions
/// @copyright

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Generates initial game filling a linked list with all the blocks needed
 * @param game is the structure that will store all the blocks created
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

/**
 * Frees the memory of a generated game structure and its blocks
 * @param game is the structure that will store all the blocks created
 */
void freeGame(GAME *game){
    BLOCK *blockAux = game->pfirstBlock, *delBlock = NULL;
    while(blockAux != NULL){
        delBlock = blockAux;
        blockAux = blockAux->pnextBlock;
        free(delBlock);
    }
//    free(game);
}

/**
 * Prints a certain given hand
 * @param hand is the hand to print
 * @param handSize is the size of the hand to print for limits porpuses
 */
void printSingleHand(HAND hand, int handSize){
    BLOCK *pblock = hand.pfirstBlock;
    int i;
    for (i = 0; i < handSize && pblock != NULL; i++) {
        printf("[%d , %d] ", pblock->leftSide, pblock->rightSide);
        pblock = pblock->pnextBlock;
    }
}

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
    }else{
        return NULL;
    }
    game->availableBlocks -= 1;
    return blockAux;
}

/**
 * Gets a certain block from the game structure and returns it to free it after
 * Updates the pointers to not include the block to remove
 * @param game is the structure that stores all the unused blocks
 * @param block is the block to return
 * @return returns the block
 */
BLOCK *removeBlock(GAME *game, BLOCK block){
    BLOCK *blockAux = game->pfirstBlock, *blockPrev = NULL;
    while(blockAux != NULL){
        if( ((blockAux->leftSide == block.leftSide) && (blockAux->rightSide == block.rightSide))
           || ((blockAux->leftSide == block.rightSide) && (blockAux->rightSide == block.leftSide)) ){
            if(blockPrev == NULL){
                game->pfirstBlock = blockAux->pnextBlock;
            }else{
                blockPrev->pnextBlock = blockAux->pnextBlock;
//                free(blockPrev);
            }
            return blockAux;
        }
        blockPrev = blockAux;
        blockAux = blockAux->pnextBlock;
    }
    return NULL;
}

/**
 * Returns a certain block at the index given but doesn't remove it until some verifications are made in another function
 * @param game structure that has the non-used blocks
 * @param index position of the block to return
 * @return returns the block that corresponds to the index
 */
BLOCK *peepBlock(GAME game, int index){
    int i = 0;
    BLOCK *blockAux = game.pfirstBlock;
    while(i != index && blockAux != NULL){
        blockAux = blockAux->pnextBlock;
        i++;
    }
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
 * Check if a certain block is present in the game
 * @param game is the structure that has the unused blocks of the game
 * @param block is the block to search
 * @return returns 1 if the block is found and 0 if not
 */
int blockIsPresent(GAME game, BLOCK block){
    BLOCK *blockAux = game.pfirstBlock;
    while(blockAux != NULL){
        if( ((blockAux->leftSide == block.leftSide) && (blockAux->rightSide == block.rightSide))
            || ((blockAux->leftSide == block.rightSide) && (blockAux->rightSide == block.leftSide)) ){
            return 1;
        }
        blockAux = blockAux->pnextBlock;
    }
    return 0;
}

/**
 * Checks the filename the user inputted for the extension and if it doesn't exist adds it at the end
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
 * @param fileName the name of the file
 * @return returns 0 if there's no file with that name and 1 if there is
 */
int fileExists(char fileName[]) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) return 0;
    return 1;
}

/**
 * Runs the structure that has the id of all sequences matching a certain pattern to check if the id the user
 * chose exists
 * @param sequenceIds is the structure with all the matching sequences' ids
 * @param id is the id the user chose
 * @return returns true if the id is present and false if not
 */
int checkId(IDS *sequenceIds, unsigned long id){
    ID *idAux = sequenceIds->firstId;
    ID *delId;
    int toReturn = 0;
    while(idAux != NULL){
        if(idAux->sequenceId == id){
            sequenceIds->firstId = idAux;
            sequenceIds->numberOfIds = 1;
            toReturn = 1;           // store the result to continue to run the list and free the memory of the remaining ids
            idAux = idAux->nextId;  // because we will only need the id that matched
            continue;
        }
        delId = idAux->nextId;
//        free(idAux);
        idAux = delId;
    }
    if(toReturn) sequenceIds->firstId->nextId = NULL;
    return toReturn;
}

/**
 * Receives a string, creates space on the memory for it and copies the string to that space
 * @param str is the string to be saved in the memory
 * @return returns the memory address where the string previously saved starts
 */
char *createDynamicString(char str[]){
    char *paux = NULL;
    int strLen = strlen(str) + 1;
    paux = (char*)malloc(sizeof(char)*strLen);
    strcpy(paux, str);
    return paux;
}