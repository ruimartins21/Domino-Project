/// @file files.h
/// @brief Header of the files.c file that initializes all the functions present in files.c and its macros
/// @copyright

#ifndef DOMINO_PROJECT_FILES_H
#define DOMINO_PROJECT_FILES_H

#include "utils.h"

void openFile(char fileName[], int type, HANDS *hands, GAME *game);
void editFile(char fileName[], int type, HANDS hands, GAME game);
void createGameFile(int type, HANDS hands, GAME game);

#endif //DOMINO_PROJECT_FILES_H
