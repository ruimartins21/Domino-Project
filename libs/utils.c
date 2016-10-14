
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

///
///
///



/**
 *
 * @param matrix
 * @param lines
 * @param hand
 */
void gerateRandomHand(int matrix[][MAX2], int lines, int hand[][MAX2]) {
    int l = 0, c = 0, aux = 0;
    aux = 0 + rand() % 14;
    for (l = 0; l < lines; l++) {
        for (c = 0; c < 1; c++) {
            printf("%d ", matrix[l][c]);
        }
        printf("%d \n", matrix[l][c]);
    }
    printf("rand = %d\n", aux);

}


void compressMatriz(int matrix[][MAX2], int lines, int index) {
    int l = 0, c = 0, aux = index + 1;
    for (l = 0; l < lines - aux; l++) {

        matrix[index][0] = matrix[index + 1][0];
        matrix[index][1] = matrix[index + 1][1];

        index++;


        printf("%d  %d\n", matrix[index][0], matrix[index][1]);
    }
    matrix[index][0] = -1;
    matrix[index][1] = -1;

}

void printmat(int matrix[][MAX2], int lines) {
    int l = 0;

    for (l = 0; l < lines; l++) {

        printf("%d %d\n", matrix[l][0], matrix[l][1]);
    }

}