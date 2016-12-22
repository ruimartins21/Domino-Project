/// @file core.h
/// @brief Header of the core.c file that initializes all the functions present in core.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_CORE_H
#define DOMINO_PROJECT_CORE_H

#define MAX2 2
#define MAX3 3
#define MAX28 28
#define MAX57 57

#include "utils.h"

//void generateRandomHand(int matrix[][MAX2], int hand[][MAX3], int linesHand, int qtSet);
void generateRandomHand(GAME *pGame, HANDS *pHands);
//int generateSequence(int matrix[][MAX3], int handSize, int sequence[][MAX2], int allSequences[][MAX57], int inserted);
int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, int *count);
void saveSequence(ALLSEQUENCES *allSequences, SEQUENCE *pSequence);
//int sortAllSequences(int allSequences[][MAX57]);
void sortAllSequences(ALLSEQUENCES *allSequences);
//int isConsistent(int sequence[][MAX2], int index);
int isConsistent(SEQUENCE *pSequence, BLOCK *newBlock, int inserted);
//void invertBlock(int sequence[][MAX2], int index);
void invertBlock(BLOCK *pBlock);
void invertBlockSequence(SEQUENCE *pSequence);

#endif //DOMINO_PROJECT_CORE_H
