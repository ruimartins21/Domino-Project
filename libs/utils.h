//
// Created by RicardoBarbosa on 13-Oct-16.
//

#ifndef DOMINO_PROJECT_UTILS_H
#define DOMINO_PROJECT_UTILS_H

#define MAX2 2
#define LINES 28

int getGame(int pieces[][MAX2]);
void printHandVertically(int size);
void printHandHorizontally(int hand[][MAX2], int size, int index);
void printHand_uglify(int hand[][MAX2], int size, int index);
int printMenu(int path);
void generateRandomHand(int matrix[][MAX2], int hand[][MAX2], int linesHand, int qtSet);
void compressMatrix(int matrix[][MAX2], int lines, int index);
void printMat(int matrix[][MAX2], int lines);
void inittMat(int m[][MAX2], int lines);

int generateSequence(int matrix[][MAX2], int handSize, int sequence[][MAX2], int inserted) ;
int isConsistent(int sequence[][MAX2], int index);
void invertBlock(int sequence[][MAX2], int index);
void changeBlock(int mat[][MAX2], int index, int inserted);

//int fileExists(const char *filename);
void openFile(int type, int aux[LINES][MAX2], int *numberOfHands, int *handSize);
void createGameFile(int content[LINES][MAX2], int numberOfHands, int handSize);
void checkExtension(char *fileName);

#endif //DOMINO_PROJECT_UTILS_H
