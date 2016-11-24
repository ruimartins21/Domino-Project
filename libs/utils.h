//
// Created by RicardoBarbosa on 13-Oct-16.
//

#ifndef DOMINO_PROJECT_UTILS_H
#define DOMINO_PROJECT_UTILS_H

#define MAX2 2
#define MAX3 3
#define MAX28 28
#define MAX57 57
#define MAX2000 2000


int getGame(int pieces[][MAX2]);
void printHandVertically(int size);
void printHandHorizontally(int hand[][MAX2], int size, int index);
void printHand_uglify(int hand[][MAX2], int size, int index);
int printMenu(int path);
int blocksAvailable(int matrix[][MAX2]);
void generateManualHand(int matrix[][MAX2], int hand[][MAX2], int linesHand, int qtSet);
int editHands(int matrix[][MAX2], int hand[][MAX2], int handSize, int numberOfHands);
void generateRandomHand(int matrix[][MAX2], int hand[][MAX3], int linesHand, int qtSet); // verificar se esta a dar para dinamicamente com 3 colunas
void compressMatrix(int matrix[][MAX2], int lines, int index);
void printMat(int matrix[][MAX2], int lines);
void printMatDefault(int matrix[][MAX57], int lines, int cols);
void initMat(int m[][MAX57], int lines, int cols);
void initArray(int array[MAX57]);
void saveSequence(int sequence[][MAX2], int allSequences[][MAX57], int sizeOfSequence, int handSize);
void sortAllSequences(int allSequences[][MAX57]);
void printArray(int* a, int N);
int compareIntValues(const void * a, const void * b);
void sortIntArray(int * v, int n);

int generateSequence(int matrix[][MAX3], int handSize, int sequence[][MAX2], int allSequences[][MAX57], int inserted);
int isConsistent(int sequence[][MAX2], int index);
void invertBlock(int sequence[][MAX2], int index);

void openFile(char fileName[], int type, int handsMat[MAX28][MAX2], int gameMat[MAX28][MAX2], int *numberOfHands, int *handSize);
void editFile(char fileName[], int type, int handsMat[MAX28][MAX2], int gameMat[MAX28][MAX2], int numberOfHands, int handSize);
void createGameFile(int type, int handsMat[MAX28][MAX2], int gameMat[MAX28][MAX2], int numberOfHands, int handSize);
void checkExtension(char fileName[], char extension[]);
int fileExists(char fileName[]);

#endif //DOMINO_PROJECT_UTILS_H
