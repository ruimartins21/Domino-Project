//
// Created by RicardoBarbosa on 13-Oct-16.
//

#ifndef DOMINO_PROJECT_UTILS_H
#define DOMINO_PROJECT_UTILS_H

#define MAX3 3
#define LINES 28
#define MAX57 57

int getGame(int pieces[][MAX3]);
void printHandVertically(int size);
void printHandHorizontally(int hand[][MAX3], int size, int index);
void printHand_uglify(int hand[][MAX3], int size, int index);
int printMenu(int path);
void generateRandomHand(int matrix[][MAX3], int hand[][MAX3], int linesHand, int qtSet);
void compressMatrix(int matrix[][MAX3], int lines, int index);
void printMat(int matrix[][MAX3], int lines);
void printMatDefault(int matrix[][MAX57], int lines, int cols);
void initMat(int m[][MAX57], int lines, int cols);
void initArray(int array[MAX57]);
void saveSequence(int sequence[][MAX3], int allSequences[][MAX57], int sizeOfSequence);
void sortAllSequences(int allSequences[][MAX57]);
void printArray(int* a, int N);
int compareIntValues(const void * a, const void * b);
void sortIntArray(int * v, int n);

int generateSequence(int matrix[][MAX3], int handSize, int sequence[][MAX3], int allSequences[][MAX57], int inserted);
int isConsistent(int sequence[][MAX3], int index);
void invertBlock(int sequence[][MAX3], int index);

//int fileExists(const char *filename);
void openFile(int type, int aux[][MAX3], int *numberOfHands, int *handSize);
void createGameFile(int content[][MAX3], int numberOfHands, int handSize);
void checkExtension(char *fileName);

#endif //DOMINO_PROJECT_UTILS_H
