/// @file files.h
/// @brief Header of the files.c file that initializes all the functions present in files.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_FILES_H
#define DOMINO_PROJECT_FILES_H

#include "utils.h"

#define MAX2 2
#define MAX3 3

void openFile(char fileName[], int type, HANDS *hands, GAME *game);
void editFile(char fileName[], int type, int hand[][MAX3], int gameMat[][MAX2], int numberOfHands, int handSize);
void createGameFile(int type, int hand[][MAX3], int gameMat[][MAX2], int numberOfHands, int handSize);

#endif //DOMINO_PROJECT_FILES_H
