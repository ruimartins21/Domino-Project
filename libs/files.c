/// @file files.c
/// @brief Gathers all the functions that handles files (read and write)
/// @copyright

#include "files.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/stat.h> // library for the mkdir for Mac
#include <string.h>
#include <stdlib.h>
#include <io.h> // library for the mkdir for Windows

/**
 * Opens the file with the name the user inputs if it exists, if not, keeps asking for a valid name
 * @param fileName it's the file to be open and where the data is stored
 * @param type type = 1 means it's a text file, type = 2 means it's a binary file
 * @param hands it's the structure that stores all the hands and respective blocks
 * @param game it's the structure that stores all the blocks not being used by any hands
 */
void openFile(char fileName[], int type, HANDS *hands, GAME *game){
    FILE *file = NULL;
    int i = 0, auxInt = 0, auxInt2 = 0;
    char fOut[30];
//    char path[40] = "data/";
    char path[100] = "/Users/ruimartins/ClionProjects/Domino-Project/cmake-build-debug/data/"; // on mac it needs to be an absolute path
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
                    // saves the hands and respective blocks that are after the first line until (numberOfHands*handSize) lines
                    } else if (i < (hands->numberOfHands * hands->handSize) + 1) {
                        blockAux = (BLOCK*)malloc(sizeof(BLOCK));
                        if(auxInt < hands->handSize && auxInt != 0){ // enters here while it's the same hand, otherwise it changes the hand and adds it to the new one
                            auxInt++;
                        }else{
                            if(hands->pfirstHand == NULL){ // first hand to be inserted
                                handAux = (HAND*)malloc(sizeof(HAND));
                                handAux->pnextHand = NULL;
                                hands->pfirstHand = handAux;
                            }else{
                                while(handAux->pnextHand != NULL){ // gets the last inserted hand
                                    handAux = handAux->pnextHand;
                                }
                                handAux->pnextHand = (HAND*)malloc(sizeof(HAND));
                                handAux = handAux->pnextHand;
                                handAux->pnextHand = NULL; // last hand points to null
                            }
                            handAux->pfirstBlock = NULL;
                            auxInt = 1; // restarts the counter with 1 block already inserted
                        }
                        blockAux->leftSide   = fOut[0] - '0';
                        blockAux->rightSide  = fOut[1] - '0';
                        blockAux->available  = 1;
                        blockAux->pnextBlock = NULL;
                        if(handAux->pfirstBlock == NULL){ // first block of the hand
                            blockAux->prevBlock = blockAux;
                            handAux->pfirstBlock = blockAux;
                        }else{
                            handAux->pfirstBlock->prevBlock->pnextBlock = blockAux; // inserts at the tail
                            handAux->pfirstBlock->prevBlock = blockAux; // links the first and the last block inserted
                        }
                    } else {
                        if(i == (hands->numberOfHands * hands->handSize) + 1) { // first time it enters here
                            // available blocks are the number of total blocks subtracted by the blocks already used by the hands
                            // subtracts by 29 because the value of i is one step further than what's real
                            game->availableBlocks = 29 - i;
                        }
                        blockAux = (BLOCK*)malloc(sizeof(BLOCK));
                        blockAux->leftSide   = fOut[0] - '0';
                        blockAux->rightSide  = fOut[1] - '0';
                        blockAux->available  = 1;
                        blockAux->pnextBlock = game->pfirstBlock;
                        game->pfirstBlock = blockAux;
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
                    } else if (i < ((hands->numberOfHands) * (hands->handSize)) + 1) {
                        blockAux = (BLOCK*)malloc(sizeof(BLOCK));
                        if(auxInt2 < hands->handSize && auxInt2 != 0){
                            auxInt2++;
                        }else{
                            if(hands->pfirstHand == NULL){ // first hand to be inserted
                                handAux = (HAND*)malloc(sizeof(HAND));
                                handAux->pnextHand = NULL;
                                hands->pfirstHand = handAux;
                            }else{
                                while(handAux->pnextHand != NULL){ // gets the last inserted hand
                                    handAux = handAux->pnextHand;
                                }
                                handAux->pnextHand = (HAND*)malloc(sizeof(HAND));
                                handAux = handAux->pnextHand;
                                handAux->pnextHand = NULL; // last hand points to null
                            }
                            handAux->pfirstBlock = NULL;
                            auxInt2 = 1; // restarts the counter with 1 block already inserted
                        }
                        fread(&auxInt, sizeof(int), 1, file);
                        blockAux->leftSide = auxInt;
                        fread(&auxInt, sizeof(int), 1, file);
                        blockAux->rightSide = auxInt;
                        blockAux->available  = 1;
                        blockAux->pnextBlock = NULL;
                        if(handAux->pfirstBlock == NULL){ // first block of the hand
                            blockAux->prevBlock = blockAux;
                            handAux->pfirstBlock = blockAux;
                        }else{
                            handAux->pfirstBlock->prevBlock->pnextBlock = blockAux; // inserts at the tail
                            handAux->pfirstBlock->prevBlock = blockAux; // links the first and the last block inserted
                        }
                    } else {
                        if(i == (hands->numberOfHands * hands->handSize) + 1){ // first time it enters here
                            // available blocks are the number of total blocks subtracted by the blocks already used by the hands
                            // substracts by 29 because the value of i is one step further than what's real
                            game->availableBlocks = 29 - i;
                        }
                        if(i < 29) { // this cycle runs one more time after the game is completely loaded
                            blockAux = (BLOCK *) malloc(sizeof(BLOCK));
                            fread(&auxInt, sizeof(int), 1, file);
                            blockAux->leftSide = auxInt;
                            fread(&auxInt, sizeof(int), 1, file);
                            blockAux->rightSide = auxInt;
                            blockAux->available = 1;
                            blockAux->pnextBlock = game->pfirstBlock;
                            game->pfirstBlock = blockAux;
                        }else{
                            break;
                        }
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
 * Rewrites the file the user loaded with the new hands and game structures after he edited them
 * @param fileName name of the file to edit
 * @param type type = 1 means it's a text file, type = 2 means it's a binary file
 * @param hands it's the structure that stores all the hands and respective blocks
 * @param game it's the structure that stores all the blocks not being used by any hands
 */
void editFile(char fileName[], int type, HANDS hands, GAME game) {
    FILE *file = NULL;
    int auxInt;
//    char path[40] = "data/";
    char path[100] = "/Users/ruimartins/ClionProjects/Domino-Project/cmake-build-debug/data/"; // on mac it needs to be an absolute path
//    mkdir(path); // creates the folder if it doesn't yet exists on Windows
    mkdir(path, 0777); // creates the folder if it doesn't yet exists on MAC
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
                // checks if the number is 2 digit or not, if not, adds a 0 before to help on reading 2 digits numbers from files
                if (hands.numberOfHands / 10 == 0) {
                    fprintf(file, "0%d", hands.numberOfHands);
                } else {
                    fprintf(file, "%d", hands.numberOfHands);
                }
                if (hands.handSize / 10 == 0) {
                    fprintf(file, "0%d", hands.handSize);
                } else {
                    fprintf(file, "%d", hands.handSize);
                }
                HAND *handAux = hands.pfirstHand;
                BLOCK *blockAux = NULL;
                // stores the hands generated
                while(handAux != NULL){
                    blockAux = handAux->pfirstBlock;
                    while(blockAux != NULL){
                        fprintf(file, "\n%d%d", blockAux->leftSide, blockAux->rightSide);
                        blockAux = blockAux->pnextBlock;
                    }
                    handAux = handAux->pnextHand;
                }
                // stores the game with the unused blocks
                blockAux = game.pfirstBlock;
                while(blockAux != NULL){
                    fprintf(file, "\n%d%d", blockAux->leftSide, blockAux->rightSide);
                    blockAux = blockAux->pnextBlock;
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
                fwrite(&hands.numberOfHands, sizeof(int), 1, file);
                fwrite(&hands.handSize, sizeof(int), 1, file);
                HAND *handAux = hands.pfirstHand;
                BLOCK *blockAux = NULL;
                // stores the hands generated
                while(handAux != NULL){
                    blockAux = handAux->pfirstBlock;
                    while(blockAux != NULL){
                        auxInt = blockAux->leftSide;
                        fwrite(&auxInt, sizeof(int), 1, file);
                        auxInt = blockAux->rightSide;
                        fwrite(&auxInt, sizeof(int), 1, file);
                        blockAux = blockAux->pnextBlock;
                    }
                    handAux = handAux->pnextHand;
                }
                // stores the game with the unused blocks
                blockAux = game.pfirstBlock;
                while(blockAux != NULL){
                    auxInt = blockAux->leftSide;
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = blockAux->rightSide;
                    fwrite(&auxInt, sizeof(int), 1, file);
                    blockAux = blockAux->pnextBlock;
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
 * Creates a file with the game generated and the name and type of file the user chooses
 * @param type type = 1 means it's a text file, type = 2 means it's a binary file
 * @param hands it's the structure that stores all the hands and respective blocks
 * @param game it's the structure that stores all the blocks not being used by any hands
 */
void createGameFile(int type, HANDS hands, GAME game) {
    FILE *file = NULL;
    int auxInt, i;
    char fileName[40];
//    char path[40] = "data/";
    char path[100] = "/Users/ruimartins/ClionProjects/Domino-Project/cmake-build-debug/data/"; // on mac it needs to be an absolute path
//    mkdir(path); // creates the folder if it doesn't yet exists on Windows
    mkdir(path,0777); // creates the folder if it doesn't yet exists on MAC
    switch (type) {
        // create txt file
        case 1:
            printf("\nSave the game as: ");
            scanf("%s", fileName);
            checkExtension(fileName, ".txt");
            strcat(path, fileName);
            if (fileExists(path)) {
                printf("\nxx Error: The file '%s' already exists xx\n", fileName);
                createGameFile(type, hands, game);
                return;
            }
            if ((file = fopen(path, "w")) != NULL) {
                // stores the numberOfHands and the handSize
                // checks if the number is 2 digit or not, if not, adds a 0 before to help on reading 2 digits numbers from files
                if (hands.numberOfHands / 10 == 0) {
                    fprintf(file, "0%d", hands.numberOfHands);
                } else {
                    fprintf(file, "%d", hands.numberOfHands);
                }
                if (hands.handSize / 10 == 0) {
                    fprintf(file, "0%d", hands.handSize);
                } else {
                    fprintf(file, "%d", hands.handSize);
                }
                HAND *handAux = hands.pfirstHand;
                BLOCK *blockAux = NULL;
                // stores the hands generated
                while(handAux != NULL){
                    blockAux = handAux->pfirstBlock;
                    i = 0;
                    while(blockAux != NULL && i < hands.handSize){
                        fprintf(file, "\n%d%d", blockAux->leftSide, blockAux->rightSide);
                        blockAux = blockAux->pnextBlock;
                        i++;
                    }
                    handAux = handAux->pnextHand;
                }
                // stores the game with the unused blocks
                blockAux = game.pfirstBlock;
                while(blockAux != NULL){
                    fprintf(file, "\n%d%d", blockAux->leftSide, blockAux->rightSide);
                    blockAux = blockAux->pnextBlock;
                }
            } else {
                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
                createGameFile(type, hands, game);
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
                createGameFile(type, hands, game);
                return;
            }
            if ((file = fopen(path, "wb")) != NULL) {
                // stores the numberOfHands and the handSize
                fwrite(&hands.numberOfHands, sizeof(int), 1, file);
                fwrite(&hands.handSize, sizeof(int), 1, file);
                HAND *handAux = hands.pfirstHand;
                BLOCK *blockAux = NULL;
                // stores the hands generated
                while(handAux != NULL){
                    blockAux = handAux->pfirstBlock;
                    i = 0;
                    while(blockAux != NULL && i < hands.handSize){
                        auxInt = blockAux->leftSide;
                        fwrite(&auxInt, sizeof(int), 1, file);
                        auxInt = blockAux->rightSide;
                        fwrite(&auxInt, sizeof(int), 1, file);
                        blockAux = blockAux->pnextBlock;
                        i++;
                    }
                    handAux = handAux->pnextHand;
                }
                // stores the game with the unused blocks
                blockAux = game.pfirstBlock;
                while(blockAux != NULL){
                    auxInt = blockAux->leftSide;
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = blockAux->rightSide;
                    fwrite(&auxInt, sizeof(int), 1, file);
                    blockAux = blockAux->pnextBlock;
                }
            } else {
                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
                createGameFile(type, hands, game);
            }
            fclose(file);
            break;
        default:
            break;
    }
}

/**
 * Saves the generated sequences in a file for logs
 * @param allSequences is the structure that holds all the generated sequences
 */
void saveSequencesInFile(ALLSEQUENCES allSequences){
    FILE *file = NULL;
//    mkdir("data/logs"); // creates the folder if it doesn't yet exists on Windows
    mkdir("data/logs", 0777); // creates the folder if it doesn't yet exists on MAC
    char fileName[40];
//    char path[40] = "data/logs/sequence-";
    char path[100] = "/Users/ruimartins/ClionProjects/Domino-Project/cmake-build-debug/data/logs/sequence-"; // on mac it needs to be an absolute path
    struct timeval tv;
    gettimeofday(&tv,NULL);
    sprintf(fileName, "%ld",  tv.tv_sec);
    strcat(path, fileName);
    strcat(path, ".txt");
    if ((file = fopen(path, "w")) != NULL) {
        fprintf(file, "\t\tNumber of generated sequences: %ld\n\n", allSequences.numberOfSequences);
        STRINGSEQ *strSeqAux = allSequences.pfirstSequence;
        fprintf(file, "  Size of the sequence\t|\t\t\t\tSequence\n");
        fprintf(file, "----------------------------------------------------------------------------------\n");
        while(strSeqAux != NULL){
            fprintf(file, "\t\t%2d\t\t\t\t|\t\t%s\n", strSeqAux->sizeOfSequence, strSeqAux->sequence);
            strSeqAux = strSeqAux->pnextStringSeq;
        }
    }
    fclose(file);
}