///
///
///

#include "libs/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 *
 * NOME FUNÇÕES
 * @params xpto
 *
 */

int main(int argc, char *argv[]){

    srand((unsigned) time(NULL));

    int matriz[28][MAX2] = {
            {6, 0},
            {6, 1},
            {6, 2},
            {6, 3},
            {6, 4},
            {6, 5},
            {6, 6},
            {5, 0},
            {5, 1},
            {5, 2},
            {5, 3},
            {5, 4},
            {5, 5},
            {4, 0},
            {4, 1},
            {4, 2},
            {4, 3},
            {4, 4},
            {3, 0},
            {3, 1},
            {3, 2},
            {3, 3},
            {2, 0},
            {2, 1},
            {2, 2},
            {1, 0},
            {1, 1},
            {0, 0}
    };

    int matriz1[6][MAX2] = {
            {6, 0},
            {2, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {6, 5}
    };

//    printmat(matriz1, 6);
//    printf("\n\n");


//    gerateRandomHand(matriz, 14, game);

    compressMatriz(matriz1, 6, 2);
    printmat(matriz1, 6);



    return 0;
}