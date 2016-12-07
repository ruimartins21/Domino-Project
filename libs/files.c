/// @file files.c
/// @brief Gathers all the functions that handles files (read, write, append)
/// @copyright

#include "files.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <dir.h> // this library only works as it should on windows

void openFile2(char fileName[], int type, HANDS *hands, GAME *game){
    FILE *file = NULL;
    int i = 0, auxInt = 0, j = 0;
    char fOut[30];
    char path[40] = "data/";
    strcat(path, fileName);
    HAND *handAux   = NULL;
    BLOCK *blockAux = NULL;
    switch (type) {
        // Text files
        case 1:
            if ((file = fopen(path, "r")) != NULL) {
                while (fgets(fOut, 29, file)) {
                    // first line of the file, to extract the size of each hand and how many hands there are
                    if (i == 0) {
                        // arithmetic to get the first 2 digits of the first line from char to int type (correspondent to the number of hands)
                        hands->numberOfHands = fOut[0] - '0';
                        hands->numberOfHands *= 10;
                        hands->numberOfHands += (fOut[1] - '0');
                        // arithmetic to get the second 2 digits of the first line from char to int type (correspondent to the hands size)
                        hands->handSize = fOut[2] - '0';
                        hands->handSize *= 10;
                        hands->handSize += (fOut[3] - '0');
                        hands->pfirstHand  = (HAND*)malloc(sizeof(HAND)); // allocates space for the first hand
                        handAux = hands->pfirstHand;
                        // allocates space for the remaining hands because they're saved in another element of the structure HAND
                        for (j = 1; j < hands->numberOfHands; j++) {
                            handAux->pnextHand = (HAND*)malloc(sizeof(HAND));
                            handAux = handAux->pnextHand;
                        }
                        handAux = hands->pfirstHand;
                        // allocates memory for all the blocks, being used on the hands or the game doesn't matter yet
                        blockAux = (BLOCK*)malloc(sizeof(BLOCK) * MAX28);
                        // funçao para inicializar estruturas
                        // funcao insertSort que cria as peças ordenadas por um index
                        blockAux->available  = 1;
                        blockAux->leftSide   = 0;
                        blockAux->rightSide  = 0;
                        blockAux->pnextBlock = NULL;
                        handAux->pfirstBlock = blockAux;
                    // saves the hands and respective blocks that are after the first line until (numberOfHands*handSize) lines
                    } else if (i < (hands->numberOfHands * hands->handSize) + 1) {
                        if(auxInt < hands->handSize){
                            blockAux->leftSide  = fOut[0] - '0';
                            blockAux->rightSide = fOut[1] - '0';
//                            printf("\n[%d, %d]", blockAux->leftSide, blockAux->rightSide);
                            blockAux++;
                            auxInt++;
                        }else{
                            handAux              = handAux->pnextHand;
                            handAux->pfirstBlock = blockAux;
                            blockAux->leftSide   = fOut[0] - '0';
                            blockAux->rightSide  = fOut[1] - '0';
                            blockAux++;
                            auxInt = 1;
                        }
                    } else {
                        game->pfirstBlock = blockAux;

//                        gameMat[j][0] = fOut[0] - '0';
//                        gameMat[j][1] = fOut[1] - '0';
                        j++;
                    }
                    i += 1;
                }

                printHand(*hands);
                // compresses the game matrix to the size extracted from the file
                // se nao for lista ligada tenho de iterarçao
//                compressMatrix(gameMat, j, -1);
            }
            fclose(file);
            break;

            // Binary files
//        case 2:
//            if ((file = fopen(path, "rb")) != NULL) {
//                while (!feof(file)) {
//                    if (i == 0) {
//                        fread(numberOfHands, sizeof(int), 1, file);
//                        fread(handSize, sizeof(int), 1, file);
//                    } else if (i < ((*numberOfHands) * (*handSize)) + 1) {
//                        fread(&auxInt, sizeof(int), 1, file);
//                        hand[i - 1][0] = auxInt;
//                        fread(&auxInt, sizeof(int), 1, file);
//                        hand[i - 1][1] = auxInt;
//                    } else {
//                        fread(&auxInt, sizeof(int), 1, file);
//                        gameMat[j][0] = auxInt;
//                        fread(&auxInt, sizeof(int), 1, file);
//                        gameMat[j][1] = auxInt;
//                        j++;
//                    }
//                    i++;
//                }
//                // compresses the game matrix to the size extracted from the file
//                // needed to decrease by 1 the size because of the cycles the reading does
//                compressMatrix(gameMat, j - 1, -1);
//            }
//            fclose(file);
//            break;

        default:
            break;
    }
}

/**
 * Opens the file with the name the user inputs if it exists, if not, keeps asking for a valid name
 * @param type type = 1 means it's a text file, type = 2 means it's a binary file
 * @param handsMat matrix where will be stored the hands stored in the file
 * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
 * @param numberOfHands number of hands in the hands matrix
 * @param handSize size of each hand
 */
void openFile(char fileName[], int type, int hand[][MAX3], int gameMat[][MAX2], int *numberOfHands, int *handSize) {
    FILE *file = NULL;
    int i = 0, auxInt, j = 0;
    char fOut[30];
    char path[40] = "data/";
    strcat(path, fileName);
    switch (type) {
        // Text files
        case 1:
            if ((file = fopen(path, "r")) != NULL) {
                while (fgets(fOut, 29, file)) {
                    // first line of the file, to extract the size of each hand and how many hands there are
                    if (i == 0) {
                        // arithmetic to get the first 2 digits of the first line from char to int type (correspondent to the number of hands)
                        *numberOfHands = fOut[0] - '0';
                        *numberOfHands *= 10;
                        *numberOfHands += (fOut[1] - '0');
                        // arithmetic to get the second 2 digits of the first line from char to int type (correspondent to the hands size)
                        *handSize = fOut[2] - '0';
                        *handSize *= 10;
                        *handSize += (fOut[3] - '0');
                        // saves the matrix of the hands that are after the first line until (numberOfHands*handSize) lines
                    } else if (i < ((*numberOfHands) * (*handSize)) + 1) {
                        hand[i - 1][0] = fOut[0] - '0';
                        hand[i - 1][1] = fOut[1] - '0';
                    } else {
                        gameMat[j][0] = fOut[0] - '0';
                        gameMat[j][1] = fOut[1] - '0';
                        j++;
                    }
                    i++;
                }
                // compresses the game matrix to the size extracted from the file
                compressMatrix(gameMat, j, -1);
                // fills the 3rd column of the hands matrix with 1 necessary for the generate sequence function
//                fillHands(hand, *handSize, *numberOfHands);
            }
            fclose(file);
            break;

            // Binary files
        case 2:
            if ((file = fopen(path, "rb")) != NULL) {
                while (!feof(file)) {
                    if (i == 0) {
                        fread(numberOfHands, sizeof(int), 1, file);
                        fread(handSize, sizeof(int), 1, file);
                    } else if (i < ((*numberOfHands) * (*handSize)) + 1) {
                        fread(&auxInt, sizeof(int), 1, file);
                        hand[i - 1][0] = auxInt;
                        fread(&auxInt, sizeof(int), 1, file);
                        hand[i - 1][1] = auxInt;
                    } else {
                        fread(&auxInt, sizeof(int), 1, file);
                        gameMat[j][0] = auxInt;
                        fread(&auxInt, sizeof(int), 1, file);
                        gameMat[j][1] = auxInt;
                        j++;
                    }
                    i++;
                }
                // compresses the game matrix to the size extracted from the file
                // needed to decrease by 1 the size because of the cycles the reading does
                compressMatrix(gameMat, j - 1, -1);
            }
            fclose(file);
            break;

        default:
            break;
    }
}

/**
 * Rewrites the file the user loaded with the new hands and game matrix after he edited them
 * @param fileName name of the file to edit
 * @param type the type of file (txt or bin)
 * @param handsMat matrix where will be stored the hands stored in the file
 * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
 * @param numberOfHands number of hands in the hands matrix
 * @param handSize size of each hand
 */
void editFile(char fileName[], int type, int hand[][MAX3], int gameMat[][MAX2], int numberOfHands, int handSize) {
    FILE *file = NULL;
    int i = 0, auxInt;
    char path[40] = "data/";
    // not sure if it works cross-systems, not working in linux since it's needed 2 parameters
//    mkdir(path); // creates the folder if it doesn't yet exists
    strcat(path, fileName);
    switch (type) {
        // Text files
        case 1:
            if (!fileExists(path)) {
                printf("\nxx Error: The file '%s' doesnt exist xx\n", fileName);
                return;
            }
            if ((file = fopen(path, "w")) != NULL) {
                // stores the numberOfHands and the handSize
                // checks if the number is 2 digit or not, if not, adds a 0 before, so we maintain the structure
                if (numberOfHands / 10 == 0) {
                    fprintf(file, "0%d", numberOfHands);
                } else {
                    fprintf(file, "%d", numberOfHands);
                }
                if (handSize / 10 == 0) {
                    fprintf(file, "0%d", handSize);
                } else {
                    fprintf(file, "%d", handSize);
                }
                // stores the matrix of the hands generated
                for (i = 0; i < (numberOfHands * handSize); i++) {
                    fprintf(file, "\n%d%d", hand[i][0], hand[i][1]);
                }
                // stores the game matrix with the unused blocks
                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
                    fprintf(file, "\n%d%d", gameMat[i][0], gameMat[i][1]);
                }
            } else {
                printf("\nxx Error: Impossible to write to the file '%s' xx\n", fileName);
                return;
            }
            fclose(file);
            break;

            // Binary files
        case 2:
            if (!fileExists(path)) {
                printf("\nxx Error: The file '%s' doesnt exist xx\n", fileName);
                return;
            }
            if ((file = fopen(path, "wb")) != NULL) {
                // stores the numberOfHands and the handSize
                fwrite(&numberOfHands, sizeof(int), 1, file);
                fwrite(&handSize, sizeof(int), 1, file);
                // stores the matrix of the hands generated
                for (i = 0; i < (numberOfHands * handSize); i++) {
                    auxInt = hand[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = hand[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
                // stores the game matrix with the unused blocks
                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
                    auxInt = gameMat[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = gameMat[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
            } else {
                printf("\nxx Error: Impossible to write to the file '%s' xx\n", fileName);
                return;
            }
            fclose(file);
            break;

        default:
            break;
    }
}

/**
 *  Creates a file with the game generated and the name and type of file the user chooses
 *  Afterwards the user can load the game, edit it and play
 * @param type the type of file (txt or bin)
 * @param handsMat matrix where will be stored the hands stored in the file
 * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
 * @param numberOfHands number of hands in the hands matrix
 * @param handSize size of each hand
 */
void createGameFile(int type, int hand[][MAX3], int gameMat[][MAX2], int numberOfHands, int handSize) {
    FILE *file = NULL;
    int i = 0, auxInt;
    char fileName[40], path[40] = "data/";
    // not sure if it works cross-systems, not working in linux since it's needed 2 parameters
//    mkdir(path); // creates the folder if it doesn't yet exists
    switch (type) {
        // create txt file
        case 1:
            printf("\nSave the game as: ");
            scanf("%s", fileName);
            checkExtension(fileName, ".txt");
            strcat(path, fileName);
            if (fileExists(path)) {
                printf("\nxx Error: The file '%s' already exists xx\n", fileName);
                createGameFile(type, hand, gameMat, numberOfHands, handSize);
                return;
            }
            if ((file = fopen(path, "w")) != NULL) {
                // stores the numberOfHands and the handSize
                // checks if the number is 2 digit or not, if not, adds a 0 before, so we maintain the structure
                if (numberOfHands / 10 == 0) {
                    fprintf(file, "0%d", numberOfHands);
                } else {
                    fprintf(file, "%d", numberOfHands);
                }
                if (handSize / 10 == 0) {
                    fprintf(file, "0%d", handSize);
                } else {
                    fprintf(file, "%d", handSize);
                }
                // stores the matrix of the hands generated
                for (i = 0; i < (numberOfHands * handSize); i++) {
                    fprintf(file, "\n%d%d", hand[i][0], hand[i][1]);
                }
                // stores the game matrix with the unused blocks
                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
                    fprintf(file, "\n%d%d", gameMat[i][0], gameMat[i][1]);
                }
            } else {
                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
                createGameFile(type, hand, gameMat, numberOfHands, handSize);
            }
            fclose(file);
            break;

            // create bin file
        case 2:
            printf("\nSave the game as: ");
            scanf("%s", fileName);
            checkExtension(fileName, ".bin");
            strcat(path, fileName);
            if (fileExists(path)) {
                printf("\nxx Error: The file '%s' already exists xx\n", fileName);
                createGameFile(type, hand, gameMat, numberOfHands, handSize);
                return;
            }
            if ((file = fopen(path, "wb")) != NULL) {
                // stores the numberOfHands and the handSize
                fwrite(&numberOfHands, sizeof(int), 1, file);
                fwrite(&handSize, sizeof(int), 1, file);
                // stores the matrix of the hands generated
                for (i = 0; i < (numberOfHands * handSize); i++) {
                    auxInt = hand[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = hand[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
                // stores the game matrix with the unused blocks
                for (i = 0; i < (28 - (numberOfHands * handSize)); i++) {
                    auxInt = gameMat[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = gameMat[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
            } else {
                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
                createGameFile(type, hand, gameMat, numberOfHands, handSize);
            }
            fclose(file);
            break;

        default:
            break;
    }
}