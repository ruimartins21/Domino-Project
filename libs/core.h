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


void generateRandomHand(GAME *pGame, HANDS *pHands);
int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, int *count);
//int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, int *count, int handId);
int isConsistent(SEQUENCE *pSequence, BLOCK *newBlock, int inserted);
void invertBlock(BLOCK *pBlock);
void invertBlockSequence(SEQUENCE *pSequence);
void saveSequence(ALLSEQUENCES *allSequences, SEQUENCE pSequence);
STRINGSEQ *findSequenceOfSize(ALLSEQUENCES allSequences, int size, unsigned long *costModel);
void sortAllSequences(ALLSEQUENCES *allSequences);
SEQUENCE *sortedMerge(SEQUENCE *a, SEQUENCE *b);
void mergeSort(struct sequence** headRef);
void frontBackSplit(SEQUENCE *source, struct sequence* *frontRef, struct sequence* *backRef);

//void mergeSort(ALLSEQUENCES *allsequences, ALLSEQUENCES *paux, int lo, unsigned long hi);
//void merge(ALLSEQUENCES *allsequences, ALLSEQUENCES *paux, int lo, int mid, int hi);

#endif //DOMINO_PROJECT_CORE_H
