
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

///
///
///

/**
 * generate initial game matrix
 * @param pieces => matrix to store the generated numbers
 * @return => default (0): filled matrix is stored via its addresses so it isn't needed to return anything
 */
int getGame(int pieces[][MAX2]) {
    int l = 0, c = 0, lin = 0;
    for (l = 0; l <= 6; l++) {
        for (c = l; c <= 6; c++) {
            pieces[lin][0] = l;
            pieces[lin][1] = c;
            lin += 1;
        }
    }
    return 0;
}

/**
* Print the various menus that are needed
* @param path => tells the function at wich part of the menu it is
* @param choice => choice the user made, that together with the path given gives the function the proper infos to display
*/
int printMenu(int path) {
    int choiceMade = 0;
    switch (path) {
        case 0:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - New Game\n");
            printf("\t\t\t\t2 - Load Game from file\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 1:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tNumber of Hands: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 28) {
                printf("!!! Please choose a number between 1 & 28. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 2:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Create Hand(s) randomly\n");
            printf("\t\t\t\t2 - Create Hand(s) manually\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 3:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tNumber of pieces on each hand: ");
            scanf("%d", &choiceMade);
            return choiceMade;

        case 4:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Load game from text file\n");
            printf("\t\t\t\t2 - Load game from binary file\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        default:
            return -1;
    }
}

/**
 * Print a hand of the game vertically
 * @param size => size of the hand
 */
void printHandVertically(int size) {
    int i = 0, j = 0, block = 5;
    for (i = 0; i < block; i++) {
        if (i % 2 == 0) {
            for (j = 0; j < size; j++) {
                printf("+---+  ");
            }
        } else {
            for (j = 0; j < size; j++) {
                printf("| 1 |  ");
            }
        }

        printf("\n");
    }
}

/**
 * Print a hand of the game horizontally
 * @param hand => matrix where the hands are saved
 * @param size => size of the hand
 * @param index => position of the hand to print
 */
void printHandHorizontally(int hand[][MAX2], int size, int index) {
    int i, j, block = 3;
    // move the first position to print according to the index
    index = (index == 0 ? index : index * size);
//    printf("index = %d\n", index);
    for (i = 0; i < block; i++) {
        if (i % 2 == 0) {
            for (j = index; j < index + size; j++) {
                printf("+---+---+ ");
            }
        } else {
            for (j = index; j < index + size; j++) {
                printf("| %d | %d | ", hand[j][0], hand[j][1]);
            }
        }

        printf("\n");
    }
}

/**
 * Print a hand of the game but not the pieces, only a vector with its numbers
 * @param size => size of the hand
 */
void printHand_uglify(int hand[][MAX2], int size, int index) {
    int i;
    // move the first position to print according to the index
    index = (index == 0 ? index : index * size);
    for (i = index; i < index + size; i++) {
        printf("[ %d , %d ] ", hand[i][0], hand[i][1]);
    }
}

/**
 * Function that generates player hand randomly
 * -> Runs the number of hands chosen by the user, for each one runs all the blocks of the hand
 * -> Generates a random number confined to the values 0 to 27
 * -> Drops index of generated number from the deck and puts it on the player hand
 * -> Compresses Matrix and inserts "-1" in the last position according to the number of lines withdrawned
 *
 * @param matrix Initial game matrix (all pieces)
 * @param hand Matrix with the player pieces (hand game)
 * @param linesHand Matrix lines of the player hand
 * @param qtSet Number of hands to generate
 */
void generateRandomHand(int matrix[][MAX2], int hand[][MAX2], int linesHand, int qtSet) {
    int l = 0, j = 0, randValue = 0, linesCount = 0, limit = 0;
    limit = LINES / linesHand;
    if (qtSet < limit)
        limit = qtSet;

//    printf("limit %d\n", limit);
    for (j = 0; j < limit; j++) {
        for (l = 0; l < linesHand; l++) {
            randValue = 0 + rand() % (LINES - linesCount);
//            printf("rand = %d\n", randValue);

//            printf("lineCount: %d\n", linesCount);
            hand[linesCount][0] = matrix[randValue][0];
            hand[linesCount][1] = matrix[randValue][1];


            compressMatrix(matrix, LINES - linesCount, randValue);
            linesCount++;

//            printf("\n----------------\n");
//            printf("\nantes----------Matriz geral\n");
//            printmat(matrix, LINES);

//        printf("%d \n", hand[l][0]);
//        printf("%d \n", hand[l][1]);
        }
//        printmat(hand, LINES);
//        printf("\n--------------\n");
//        printf("countLines: %d\n", linesCount);
    }
}


/**
 * Function that compresses the game matrix
 * Used to generated random hands
 * -> Drops index of generated number from deck and put it on player hand
 * -> Compress Matrix and puts "-1" in the last position
 *
 * @param matrix Initial Matrix (with the number of blocks existing at the time)
 * @param lines Number of lines existing at the previous matrix
 * @param index Position of the block to be withdrawn to the player hand
 */
void compressMatrix(int matrix[][MAX2], int lines, int index) {
    int l = 0, c = 0, aux = index + 1;
    for (; index < lines; index++) {

        matrix[index][0] = matrix[index + 1][0];
        matrix[index][1] = matrix[index + 1][1];

//        printf("%d  %d\n", matrix[index][0], matrix[index][1]);
    }
    matrix[index - 1][0] = -1;
    matrix[index - 1][1] = -1;
}


//funcao de dividir o array pela quantidade de maos

//funcao de consistencia para verificar se as peças batem certo para a sequencia
/**
 * pega na matriz com as varias maos criadas e identificar as maos (array ao auxiliar, que diz mao 1, com as pecas de 0 ate 10, exemplo)
 */


void printMat(int matrix[][MAX2], int lines) {
    int l = 0;

    for (l = 0; l < lines; l++) {

        printf("%d %d\n", matrix[l][0], matrix[l][1]);
    }

}

void inittMat(int m[][MAX2], int lines) {
    int l = 0;

    for (l = 0; l < lines; l++) {

        m[l][0] = 0;
        m[l][1] = 0;
    }

}

//void shiftMatrix(int matrix[][MAX2], int handSize, int index) {
//    int i = 0, j = 0, aux[2];
//
//    aux[0] = matrix[0][0];
//    aux[1] = matrix[0][1];
//
//    for (i = 0; i < handSize; i++) {
//        for (j = 0; j < MAX2; j++) {
//            matrix[i][j] = matrix[i + 1][j];
//        }
//    }
//    matrix[i - 1][0] = aux[0];
//    matrix[i - 1][1] = aux[1];
//}


int generateSequence(int matrix[][MAX2], int handSize, int sequence[][MAX2], int inserted) {
    int i, result, j;
    int aux[2] = {0,0};

//    printf("Matriz sequence main:\n");
//    printMat(sequence, handSize);
//    printf("\n");
    if (inserted == handSize) {
        return 1;
    }

//    printf("\nantes do for:\n");
//    printMat(matrix, handSize);
    for (i = inserted; i < handSize; i++) {
        sequence[i][0] = matrix[i][0];
        sequence[i][1] = matrix[i][1];
        inserted++;

        printf("\nIteracao (%d): \nPeça em jogo: [%d][%d]\nPeças inseridas: %d\n", i, sequence[i][0],
               sequence[i][1], inserted);
//        printf("Matriz no if:\n");
        printMat(sequence, inserted);
        printf("\n");

//        printf("Matriz sequence main:\n");
//        printMat(sequence, inserted);
//        printf("\n");

        if (isConsistent(sequence, i) == 1) {
//            inserted++;
//            printf("Sequencias: \n");
//            printMat(sequence,inserted);
//            printf("\n antes de enviar como recursivo\n");
//            printMat(matrix, handSize);
            printf("Matriz no if:\n");
            printMat(matrix, handSize);
            printf("\n");
            result = generateSequence(matrix, handSize, sequence, inserted);
            if (result == 1) {
                return 1;
            }
        } else {
            printf("Matriz no else:\n");
            printMat(matrix, handSize);
            printf("\n");

            aux[0] = matrix[i][0];
            aux[1] = matrix[i][1];
//            printMat(matrix, handSize);

            printf("\naux[0]= %d, aux[1]= %d\n", aux[0], aux[1]);
            for (j = i; j < handSize; j++) {
                matrix[j][0] = matrix[j + 1][0];
                matrix[j][1] = matrix[j + 1][1];
            }
            matrix[j-1][0] = aux[0];
            matrix[j-1][1] = aux[1];

            printf("\nMatriz depois de deslocada:\n");
            printMat(matrix, handSize);
            i--;
        }
    }
    return 0;
}

int isConsistent(int sequence[][MAX2], int index) {
//    printf("\n (isConsistent)\n");
//    printMat(sequence, 4);
    if (index == 0) {
        return 1;
    }
    if (sequence[index - 1][1] == sequence[index][0]) {
        return 1;
    } else if (sequence[index - 1][1] == sequence[index][1]) {
//        printf("index: %d", index);
//        printf("\nmatriz sequencia (isConsistent)\n");
//        printMat(sequence, 4);
        invertBlock(sequence, index);
        return 1;
    } else {
        return 0;
    }
}

void invertBlock(int block[][MAX2], int index) {
    int aux = 0;
//    printf("\n-----\n");
//    printMat(block,4);
    aux = block[index][1];
//    printMat(block, index);
//    printf("aux: %d\n", aux);
    block[index][1] = block[index][0];
    block[index][0] = aux;

//    printf(" ---->Invertido: [%d] [%d]\n", block[index][0], block[index][1]);
//    printMat(block, index);

}

/**
 * Function to check the existence of a file (currently not needed)
 */
//int fileExists(const char *filename)
//{
//    FILE *fp = fopen(filename, "r");
//    if (fp != NULL){
//        fclose(fp);
//    }
//    return (fp != NULL);
//}

/**
 * Opens the file with the name the user inputs if it exists, if not, keeps asking for a valid name
 * @param type => type = 1 means it's a text file, type = 2 means it's a binary file
 * @param aux => array where will be stored the contents of the file opened
 * @param lines => size of the final array after it's extracted
 * @return
 */
    void openFile(int type, int aux[LINES][MAX2], int *numberOfHands, int *handSize) {
        FILE *file;
        int i = 0;
        char fileName[50], fOut[200];
        switch (type){
            // Text files
            case 1:
                // printf("\nFiles existing:\n");
                // system("dir/b *.txt"); // scans all files with the extension "txt" in the root of the folder where the program executable is and prints them
                printf("\nFile name: ");
                scanf("%s", fileName);
                // if the user didn't add ".txt" at the end of the file name it will be needed to add it
                if(strstr(fileName, ".txt") == NULL){ // searches the substring ".txt" in the filename the user inputted
                    strcat(fileName, ".txt");
                }
                file = fopen(fileName, "r"); // opens the file with permissions to read only
                if(file == NULL)
                {
                    printf("\nxx Error: Impossible to open the file '%s' xx\n", fileName);
                    openFile(type, aux, numberOfHands, handSize);
                }else{
                    printf("\n** Success: File '%s' opened **\n", fileName);
                    while(fgets(fOut, 29, file))
                    {
//                    printf("%s", fOut); // imprime todos os conteudos do ficheiro
                        // first line of the file, to extract the size of each hand and how many hands there are
                        if(i == 0){
                            *numberOfHands = fOut[0] - '0';
                            *handSize      = fOut[1] - '0';
                        }else{
                            aux[i-1][0] = fOut[0] - '0';
                            aux[i-1][1] = fOut[1] - '0';
                        }
                        i++;
                    }
                }
                break;

                // Binary files
            case 2:

                break;

            default: break;
        }
}