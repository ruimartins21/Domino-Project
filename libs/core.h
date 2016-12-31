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
int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, unsigned long *count, int handId, unsigned long *costOfGenerate);
int isConsistent(SEQUENCE *pSequence, BLOCK *newBlock, int inserted);
void invertBlock(BLOCK *pBlock);
void invertBlockSequence(SEQUENCE *pSequence);
void saveSequence(ALLSEQUENCES *allSequences, SEQUENCE pSequence);
STRINGSEQ *findSequenceOfSize(ALLSEQUENCES allSequences, int size, unsigned long *costModel);
void getAvailableBlocks(GAME *availableBlocks, ALLSEQUENCES allSequences, int sizeOfPattern);
int getSequencesOfSize(GAME *availableBlocks, STRINGSEQ firstSequence, int size);
void printSequence(SEQUENCE sequence);

// MERGESORT sorting
void sortAllSequences(ALLSEQUENCES *allSequences);
STRINGSEQ *sortedMerge(STRINGSEQ *a, STRINGSEQ *b, unsigned long *costModel);
void mergeSort(STRINGSEQ * *headRef, unsigned long *costModel);
void frontBackSplit(STRINGSEQ *source, STRINGSEQ* *frontRef, STRINGSEQ* *backRef);
void moveNode(STRINGSEQ **destRef, STRINGSEQ **sourceRef);

// KMP substring search
void preKMP(char *pat, int *Pi);
int KMP(STRINGSEQ text, char *pat);


#endif //DOMINO_PROJECT_CORE_H
