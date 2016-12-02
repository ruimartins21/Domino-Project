/// @file utils.h
/// @brief Header of the utils.c file that initializes all the functions present in utils.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_UTILS_H
#define DOMINO_PROJECT_UTILS_H

typedef struct block{
    int rightSide;
    int leftSide;
    int available;
    struct block *pnextBlock;
}BLOCK;

typedef struct game{
    unsigned int availableBlocks;
    BLOCK *blocks;
}GAME;

typedef struct hand{
    BLOCK *pfirstBlock;
    struct hand *pnextHand;
}HAND;

typedef struct hands{
    int handSize;
    int numberOfHands;
    HAND *pfirstHand;
}HANDS;

typedef struct sequence{
    BLOCK *pfirstBlock;
    int sizeOfSequence;
}SEQUENCE;

typedef struct allSequences{
    SEQUENCE *pfirstSequence;
    int numberOfSequences;
}ALLSEQUENCES;

#define MAX2 2
#define MAX3 3
#define MAX28 28
#define MAX57 57
#define MAX2000 2000

void getGame(GAME *game);
void printGame(GAME game);
void compressMatrix(int matrix[][MAX2], int lines, int index);
void initMat(int m[][MAX57], int lines, int cols);
void initArray(int array[MAX57]);
int compareIntValues(const void * a, const void * b);
void sortIntArray(int * v, int n);
void checkExtension(char fileName[], char extension[]);
int fileExists(char fileName[]);
void fillHands(int hand[][MAX3], int handSize, int numberOfHands);

#endif //DOMINO_PROJECT_UTILS_H
