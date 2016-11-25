/// @file core.h
/// @brief Header of the core.c file that initializes all the functions present in core.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_CORE_H
#define DOMINO_PROJECT_CORE_H

#define MAX2 2
#define MAX3 3
#define MAX28 28
#define MAX57 57

void generateRandomHand(int matrix[][MAX2], int hand[][MAX3], int linesHand, int qtSet);
int generateSequence(int matrix[][MAX3], int handSize, int sequence[][MAX2], int allSequences[][MAX57], int inserted);
void saveSequence(int sequence[][MAX2], int allSequences[][MAX57], int sizeOfSequence, int handSize);
void sortAllSequences(int allSequences[][MAX57]);
int isConsistent(int sequence[][MAX2], int index);
void invertBlock(int sequence[][MAX2], int index);

#endif //DOMINO_PROJECT_CORE_H
