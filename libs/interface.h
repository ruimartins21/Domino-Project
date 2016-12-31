/// @file interface.h
/// @brief Header of the interface.c file that initializes all the functions present in interface.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_INTERFACE_H
#define DOMINO_PROJECT_INTERFACE_H

#include "utils.h"

#define MAX28 28
#define MAX57 57

int printMenu(int path);
int blocksAvailable(GAME game);
void generateManualHand(GAME *game, HANDS *hands);
void findPatternInSequences(ALLSEQUENCES allSequences, char *pattern, IDS *sequenceIds, unsigned long *numberOfMatches);
int editHands(HANDS *hands, GAME *game);
void printSequences(ALLSEQUENCES allSequences, int size);
void printSequenceOfSize(STRINGSEQ sequence, int size);
char *createPattern(ALLSEQUENCES allSequences, int maxSequenceSize);
char *createReplacePattern(ALLSEQUENCES allSequences, IDS sequenceIds, char *pattern);
void printSequenceMatch(STRINGSEQ text, int index, int length, int withId);
void printSequence(SEQUENCE sequence);

#endif //DOMINO_PROJECT_INTERFACE_H
