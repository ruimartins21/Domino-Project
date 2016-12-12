/// @file files.c
/// @brief Gathers all the functions that handles files (read, write, append)
/// @copyright

#include "files.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <dir.h> // this library only works as it should on windows

/**
 * Opens the file with the name the user inputs if it exists, if not, keeps asking for a valid name
 * @param type type = 1 means it's a text file, type = 2 means it's a binary file
 * @param handsMat matrix where will be stored the hands stored in the file
 * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
 * @param numberOfHands number of hands in the hands matrix
 * @param handSize size of each hand
 */
void openFile(char fileName[], int type, HANDS *hands, GAME *game){
    FILE *file = NULL;
    int i = 0, auxInt = 0, j = 0, auxInt2 = 0;
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
                        game->pfirstBlock  = (BLOCK*)malloc(sizeof(BLOCK)); // allocates space for the first block of the game structure
                        handAux = hands->pfirstHand;
                        // allocates space for the remaining hands because they're saved in another element of the structure HAND
                        for (j = 1; j < hands->numberOfHands; j++) {
                            handAux->pnextHand = (HAND*)malloc(sizeof(HAND));
                            handAux = handAux->pnextHand;
                        }
                        handAux = hands->pfirstHand;
                        // allocates memory for all the blocks, being used on the hands
                        handAux->pfirstBlock = (BLOCK*)malloc(sizeof(BLOCK));
                        blockAux = handAux->pfirstBlock;
                        for (j = 1; j < (hands->numberOfHands * hands->handSize); j++) {
                            blockAux->pnextBlock = (BLOCK*)malloc(sizeof(BLOCK));
                            blockAux = blockAux->pnextBlock;
                        }
                        blockAux = handAux->pfirstBlock;
                    // saves the hands and respective blocks that are after the first line until (numberOfHands*handSize) lines
                    } else if (i < (hands->numberOfHands * hands->handSize) + 1) {
                        if(auxInt < hands->handSize){
                            auxInt++;
                        }else{
                            handAux = handAux->pnextHand;
                            handAux->pfirstBlock = blockAux;
                            auxInt = 1;
                        }
                        blockAux->leftSide   = fOut[0] - '0';
                        blockAux->rightSide  = fOut[1] - '0';
                        blockAux->available  = 1;
                        blockAux = blockAux->pnextBlock;
                    } else {
                        // first time it enters here it points to the first block of the game structure
                        if(i == (hands->numberOfHands * hands->handSize) + 1) {
                            // available blocks are the number of total blocks subtracted by the blocks already used by the hands
                            // substracts by 29 because the value of i is one step further than what's real
                            game->availableBlocks = 29 - i;
                            blockAux = game->pfirstBlock;
                        }
                        blockAux->leftSide   = fOut[0] - '0';
                        blockAux->rightSide  = fOut[1] - '0';
                        blockAux->available  = 1;
                        if(i < 28){ // while it's not the last cycle, because if it is the nextBlock pointer is NULL
                            blockAux->pnextBlock = (BLOCK*)malloc(sizeof(BLOCK));
                            blockAux = blockAux->pnextBlock;
                        }
                    }
                    i++;
                }
            }
            fclose(file);
            break;

        // Binary files
        case 2:
            if ((file = fopen(path, "rb")) != NULL) {
                while (!feof(file)) {
                    if (i == 0) {
                        fread(&hands->numberOfHands, sizeof(int), 1, file);
                        fread(&hands->handSize, sizeof(int), 1, file);
                        // initialize structures
                        hands->pfirstHand  = (HAND*)malloc(sizeof(HAND)); // allocates space for the first hand
                        game->pfirstBlock  = (BLOCK*)malloc(sizeof(BLOCK)); // allocates space for the first block of the game structure
                        handAux = hands->pfirstHand;
                        // allocates space for the remaining hands because they're saved in another element of the structure HAND
                        for (j = 1; j < hands->numberOfHands; j++) {
                            handAux->pnextHand = (HAND*)malloc(sizeof(HAND));
                            handAux = handAux->pnextHand;
                        }
                        handAux = hands->pfirstHand;
                        handAux->pfirstBlock = (BLOCK*)malloc(sizeof(BLOCK));
                        blockAux = handAux->pfirstBlock;
                        for (j = 1; j < (hands->numberOfHands * hands->handSize); j++) {
                            blockAux->pnextBlock = (BLOCK*)malloc(sizeof(BLOCK));
                            blockAux = blockAux->pnextBlock;
                        }
                        blockAux = handAux->pfirstBlock;
                        j = 0;
                    } else if (i < ((hands->numberOfHands) * (hands->handSize)) + 1) {
                        if(auxInt2 < hands->handSize){
                            auxInt2++;
                        }else{
                            handAux = handAux->pnextHand;
                            handAux->pfirstBlock = blockAux;
                            auxInt2 = 1;
                        }
                        fread(&auxInt, sizeof(int), 1, file);
                        blockAux->leftSide = auxInt;
                        fread(&auxInt, sizeof(int), 1, file);
                        blockAux->rightSide = auxInt;
                        blockAux->available  = 1;
                        blockAux = blockAux->pnextBlock;
                    } else {
                        if(j == 0){
                            // available blocks are the number of total blocks subtracted by the blocks already used by the hands
                            // substracts by 29 because the value of i is one step further than what's real
                            game->availableBlocks = 29 - i;
                            blockAux = game->pfirstBlock;
                        }
                        fread(&auxInt, sizeof(int), 1, file);
                        blockAux->leftSide = auxInt;
                        fread(&auxInt, sizeof(int), 1, file);
                        blockAux->rightSide = auxInt;
                        blockAux->available  = 1;
                        if(i < 28){ // while it's not the last cycle, because if it is the nextBlock pointer is NULL
                            blockAux->pnextBlock = (BLOCK*)malloc(sizeof(BLOCK));
                            blockAux = blockAux->pnextBlock;
                        }
                        j++;
                    }
                    i++;
                }
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