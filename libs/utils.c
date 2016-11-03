
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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
            printf("\t\t\t\tNumber of Hands: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 28) {
                printf("!!! Please choose a number between 1 & 28. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 1:
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

        case 2:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tNumber of pieces on each hand: ");
            scanf("%d", &choiceMade);
            return choiceMade;
        default:
            break;
    }

    return 0;

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
    int i = 0, j = 0, block = 3;
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
void printHand_uglify(int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        printf("[ 1 , 1 ] ");
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
    int i, result;
    if (inserted == handSize) {
        return 1;
    }

    for (i = 0; i < handSize; i++) {
        sequence[i][0] = matrix[i][0];
        sequence[i][1] = matrix[i][1];
        if (isConsistent(sequence, i) == 1) {
            inserted++;
            result = generateSequence(matrix, handSize, sequence, inserted);
            if (result == 1) {
                return 1;
            }
        } else {
//            mandar handSize - inserted
//            compressMatrix(); aperfeicoar de forma a trocar a peca atual para o fim, movendo as restantes pecas para cima
            i--;
        }
    }
    return 0;
}

int isConsistent(int sequence[][MAX2], int index) {
    if(index == 0){
        return  1;
    }
    if (sequence[index - 1][1] == sequence[index][0]) {
        return 1;
    } else if (sequence[index - 1][1] == sequence[index][1]) {
        invertBlock(sequence, index);
        return 1;
    } else {
        return 0;
    }
}

void invertBlock(int block[][MAX2], int index) {
    int aux;
    aux = block[index][1];
    block[index][1] = block[index][0];
    block[index][0] = aux;
}