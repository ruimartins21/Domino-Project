/// @file interface.h
/// @brief Header of the interface.c file that initializes all the functions present in interface.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_INTERFACE_H
#define DOMINO_PROJECT_INTERFACE_H

#include "utils.h"

#define MAX2 2
#define MAX3 3
#define MAX28 28
#define MAX57 57

int printMenu(int path);
void printMat(int matrix[][MAX2], int lines);
void printHands(int hand[][MAX3], int lines);
int blocksAvailable(GAME game);
void generateManualHand(GAME *game, HANDS *hands);
int editHands(HANDS *hands, GAME *game);
void printMatDefault(int matrix[][MAX57], int lines, int cols);
void printSequences(ALLSEQUENCES allSequences, int size);
void printSequenceOfSize(STRINGSEQ sequence, int size);
void printArray(int* a, int N);


#endif //DOMINO_PROJECT_INTERFACE_H
