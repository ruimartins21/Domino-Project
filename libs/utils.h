/// @file utils.h
/// @brief Header of the utils.c file that initializes all the functions present in utils.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_UTILS_H
#define DOMINO_PROJECT_UTILS_H

/**
 *  The block structure is where all the information about a block is stored, both sides, if it's available for use or not
 *  the pointer for the next block, and a pointer to the previous one since it's a doubly linked list
 */
typedef struct block{
    int leftSide;
    int rightSide;
    int available;
    struct block *pnextBlock;
    struct block *prevBlock;
}BLOCK;

/**
 *  The game structure is where all the blocks are initially stored before any hands are created
 *  and it's used to transfer the blocks for the hands and for swapping from other blocks existing on any hand
 *  this way there's no chance of repeating blocks
 */
typedef struct game{
    int availableBlocks;
    BLOCK *pfirstBlock;
}GAME;

/**
 * This structure stores all the blocks within a hand, it has a pointer to the first block since it's a linked list
 * and a pointer to the next hand
 */
typedef struct hand{
    BLOCK *pfirstBlock;
    struct hand *pnextHand;
}HAND;

/**
 * Structure that gathers all the hands used in a game, it stores each hand size (that is the same for all)
 * it stores the number of hands existing and the pointer to the first hand since it's a linked list
 */
typedef struct hands{
    int handSize;
    int numberOfHands;
    HAND *pfirstHand;
}HANDS;

/**
 * Structure that holds all the blocks used on a certain sequence generated, the sequence size and the next sequence, since it's a linked list
 */
typedef struct sequence{
    int sizeOfSequence;
    BLOCK *pfirstBlock;
    struct sequence *pnextSequence;
}SEQUENCE;

/**
 * Structure that does the same job as the SEQUENCE one but instead of a linked list of blocks and its side as integers
 * this one saves the hole sequence as a string for searching and replacing purposes
 */
typedef struct stringseq{
    int sizeOfSequence;
    unsigned long idSequence;
    char *sequence;
    struct stringseq *pnextStringSeq;
}STRINGSEQ;

/**
 * Structure that gathers all the sequences generated, saving the number of sequences and the first sequence of the linked list
 */
typedef struct allSequences{
    unsigned long numberOfSequences;
    STRINGSEQ *pfirstSequence;
}ALLSEQUENCES;

#define MAX2 2
#define MAX3 3
#define MAX28 28
#define MAX57 57

#if defined _WIN64 || defined _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif

int gettimeuseconds(long long * time_usec);
void getGame(GAME *game);
void freeGame(GAME *game);
void printGame(GAME game);
void printHand(HANDS hands);
void printSingleHand(HAND hand, int handSize);
BLOCK *popBlock(GAME *game, int index);
BLOCK *peepBlock(GAME *game, int index);
BLOCK *transferBlock(BLOCK *delBlock);
void swapBlock(GAME *game, BLOCK *handBlock, int index);
int blockIsPresent(GAME game, BLOCK block);
void initMat(int m[][MAX57], int lines, int cols);
void initArray(int array[MAX57]);
int compareIntValues(const void * a, const void * b);
void sortIntArray(int * v, int n);
void checkExtension(char fileName[], char extension[]);
int fileExists(char fileName[]);
char *createDynamicString(char str[]);

#endif //DOMINO_PROJECT_UTILS_H
