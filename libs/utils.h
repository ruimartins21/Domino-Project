//
// Created by RicardoBarbosa on 13-Oct-16.
//

#ifndef DOMINO_PROJECT_UTILS_H
#define DOMINO_PROJECT_UTILS_H

#define COLS 2
#define LINES 28

int getGame(int pieces[][COLS]);
void printHandVertically(int size);
void printHandHorizontally(int hand[][COLS], int size, int index);
void printHand_uglify(int hand[][COLS], int size, int index);
int printMenu(int path);
void generateRandomHand(int matrix[][COLS], int hand[][COLS], int linesHand, int qtSet);
void compressMatrix(int matrix[][COLS], int lines, int index);
void printMat(int matrix[][COLS], int lines);
int blocksAvailable(int matrix[][COLS]);
void generateManualHand(int matrix[][COLS], int hand[][COLS], int linesHand, int qtSet);
int editHands(int matrix[][COLS], int hand[][COLS], int handSize, int numberOfHands);
void inittMat(int m[][COLS], int lines);

int generateSequence(int matrix[][COLS], int handSize, int sequence[][COLS], int inserted) ;
int isConsistent(int sequence[][COLS], int index);
void invertBlock(int sequence[][COLS], int index);
void changeBlock(int mat[][COLS], int index, int inserted);

void openFile(char fileName[], int type, int handsMat[LINES][COLS], int gameMat[LINES][COLS], int *numberOfHands, int *handSize);
void editFile(char fileName[], int type, int handsMat[LINES][COLS], int gameMat[LINES][COLS], int numberOfHands, int handSize);
void createGameFile(int type, int handsMat[LINES][COLS], int gameMat[LINES][COLS], int numberOfHands, int handSize);
void checkExtension(char fileName[], char extension[]);
int fileExists(char fileName[]);
int toLower(char c);
int isValid(int input, int validationType);

#endif //DOMINO_PROJECT_UTILS_H
