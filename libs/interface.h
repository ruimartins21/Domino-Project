/// @file interface.h
/// @brief Header of the interface.c file that initializes all the functions present in interface.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_INTERFACE_H
#define DOMINO_PROJECT_INTERFACE_H

#define MAX2 2
#define MAX3 3
#define MAX28 28
#define MAX57 57

int printMenu(int path);
void printHand(int hand[][MAX3], int size, int index);
void printMat(int matrix[][MAX2], int lines);
void printHands(int hand[][MAX3], int lines);
int blocksAvailable(int matrix[][MAX2]);
void generateManualHand(int matrix[][MAX2], int hand[][MAX3], int handSize, int numberOfHands);
int editHands(int matrix[][MAX2], int hand[][MAX3], int handSize, int numberOfHands);
void printMatDefault(int matrix[][MAX57], int lines, int cols);
void printSequences(int matrix[][MAX57], int lines);
void printArray(int* a, int N);


#endif //DOMINO_PROJECT_INTERFACE_H
