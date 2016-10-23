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
void printHand_uglify(int size);
int printMenu(int path);
void generateRandomHand(int matrix[][MAX2], int hand[][MAX2], int linesHand, int qtSet);
void compressMatrix(int matrix[][MAX2], int lines, int index);
void printMat(int matrix[][MAX2], int lines);

#endif //DOMINO_PROJECT_UTILS_H
