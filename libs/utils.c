
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/time.h>

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
//--------------------------------------------------------------------------------------------------------------------------------------
void generateRandomHand(int matrix[][MAX2], int hand[][MAX3], int linesHand, int qtSet) {
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
            hand[linesCount][2] = 1;


            compressMatrix(matrix, LINES - linesCount, randValue);
            linesCount++;
//
//            printf("\n----------------\n");
//            printf("\nantes----------Matriz geral\n");
//            printMat(matrix, LINES);

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


void printMat(int matrix[][MAX3], int lines) {
    int l = 0;

    for (l = 0; l < lines; l++) {

        printf("[%d %d %d] ", matrix[l][0], matrix[l][1], matrix[l][2]);
//        printf("%d %d\n", matrix[l][0], matrix[l][1]);
    }

}

void printMatDefault(int matrix[][MAX57], int lines, int cols) {
    int l = 0, c = 0;

    for (l = 0; l < lines; l++) {
        for (c = 0; c < cols && matrix[l][c] != -1; c++) {
            printf("%d ", matrix[l][c]);
        }
        printf("\n");
    }

}

void initMat(int m[][MAX57], int lines, int cols) {
    int l = 0, c = 0;

    for (l = 0; l < lines; l++) {
        for (c = 0; c < cols; c++) {
            m[l][c] = -1;
        }
    }

}

void initArray(int array[MAX57]) {
    int i = 0;
    for (i = 0; i < MAX57; i++) {
        array[i] = -1;
    }
}

void printArray(int *a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/***
 * funcao usala pelo quick sort
 * @param a
 * @param b
 * @return
 */
int compareIntValues(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

/**
 *  Sort int arrays using quick sort from the C library
 *
 *  @param v integer array to sort
 *  @param n size of the array
 */
void sortIntArray(int *v, int n) {
    qsort(v, n, sizeof(int), compareIntValues);
}


/**
 * funcao para gerar sequencia a partir de uma mao
 *  -> verifica se peça inserida na matriz sequencia é consistente, se for consistente tenta inserir a proxima peça da mao
 *  ->  caso nao seja consistente tenta ver se as proximas peas da mao sao consistentes com a ultima peça inserida na matriz sequencia. Quando
 *  encontra a peça que é consistente coloca a mesma na matriz sequencia, e ainda modifica a matriz mao trocando a peça encontrada pela peca que não foi
 *  consistente no inicio. Permintindo dessa forma, da proxima vez que no ciclo for verificar as peças que são consistentes com as peças inseridas na matriz
 *  verifique a peça que anteriormente não foi consistente, podendo desta vez ser ou não consistente
 *
 *  o index 2 de cada linha é o estado da peca (1 - disponivel 0 -indisponivel) Inicialmente estão todas disponiveis
 *
 * @param matrix Initial Matrix (with the number of blocks existing at the time)
 * @param handSize size of the hand
 * @param sequence matriz sequencia de pecas consistentes
 * @param inserted number of blocks inserted in matrix sequence
 * @return
 */
int generateSequence(int matrix[][MAX3], int handSize, int sequence[][MAX3], int allSequences[][MAX57], int inserted) {
    int i = 0;

    printf("\nMao:");
    printMat(matrix, handSize);
    printf("\n");
    printf("Sequencia:");
    printMat(sequence, inserted);
    printf("\n");


    for (i = 0; i < handSize; i++) {

//        se peca disponivel
        if (matrix[i][2] == 1) {

            sequence[inserted][0] = matrix[i][0];
            sequence[inserted][1] = matrix[i][1];

            printf("Iteracao (%d): \nPeça em jogo: [%d %d]\n", i, sequence[inserted][0], sequence[inserted][1]);

            if (isConsistent(sequence, inserted) == 1) {
                printf("Valor do I: %d\n", i);

                inserted++;
                matrix[i][2] = 0; // peca fica indisponivel
                saveSequence(sequence, allSequences, inserted * 2);
//                saveSequence(sequence, allSequences, inserted );
                printf("Peças inseridas: %d\n", inserted);

                generateSequence(matrix, handSize, sequence, allSequences, inserted);


                matrix[i][2] = 1; // colocar a peça que não deu na sequencia novamente disponivel
                inserted--;
            }
        }
    }

    return 0;
}


/***
 * funcao responsavel por guardar numa matriz sequencias cada sub-sequencia / sequencia gerada
 * Coloca no index 0 de cada linha o tamanho da sequencia em questão
 * os valores que estoa para alem da sequencia estão inicializados a -1
 * @param sequence Matriz da sequencia a ser guardada
 * @param allSequences Matriz com todas as sequencias guardadas
 * @param sizeOfSequence Tamanho da sequencia a ser guardada
 */
void saveSequence(int sequence[][MAX2], int allSequences[][MAX57], int sizeOfSequence) {
    int i = 0, j = 0, k = 0;

//    procuro ate encontrar o primiero -1, que sera a primeira linha livre para guardar a sequencia em questao
    while (allSequences[i][0] != -1) {
        i++; // incremento primeiro pois a proxima linha pode ser a disponivel para guardar a sequencia
        if (allSequences[i][0] == -1) {
            allSequences[i][0] = sizeOfSequence;
            for (j = 1, k = 0; j < sizeOfSequence; j += 2, k++) {
                allSequences[i][j] = sequence[k][0];
                allSequences[i][j + 1] = sequence[k][1];
            }
            break;
        }

    }
//    se for a primeira insiro na primeira linha ele nem vai entrar no clico while de cima por isso insiro a sequencia
    if (i == 0) {
        allSequences[i][0] = sizeOfSequence;
        for (j = 1, k = 0; j < sizeOfSequence; j += 2, k++) {
            allSequences[i][j] = sequence[k][0];
            allSequences[i][j + 1] = sequence[k][1];
        }
    }
}

/***
 * Funcao responsavel por odernar  de forma decrescente por tamanho a matriz de todas as sequencias
 * Ordena a partir de uma array ordenado (o conteudo desse array corresponde ao index 0 de cada linha que contem o tamanho de cada sequencia)
 * @param allSequences Matriz com todas as sequencias e sub sequencias do jogo
 */
void sortAllSequences(int allSequences[][MAX57]) {
    int numberOfSequences = 0, j = 0, k = 0, l = 0, m = 0, arraySorted[MAX57], auxMatrix[500][MAX57];
//    criar array com index 0 de cada linha
    while (allSequences[numberOfSequences][0] != -1) {
        arraySorted[numberOfSequences] = allSequences[numberOfSequences][0];
        numberOfSequences++;

    }
//    ordenar o array por ordem decrescente -> usado quick sort
    sortIntArray(arraySorted, numberOfSequences);
    printf("\nAux sorted:");
    printArray(arraySorted, numberOfSequences);
    printf("\n");

    printf("allSequences for sort:\n");
    printMatDefault(allSequences, numberOfSequences, 56);
    printf("\n");

//    start auxiliar matrix the -1
    initMat(auxMatrix, 500, 57);

    k = numberOfSequences - 1;
    printf("Number of Sequences generated: %d\n", numberOfSequences);

    for (j = 0; j < numberOfSequences; j++) {
        if (arraySorted[k] == allSequences[j][0]) {
            for (l = 0; l <= allSequences[j][0]; l++) {
                auxMatrix[m][l] = allSequences[j][l];
            }
            allSequences[j][0] = -1;
            m++; // usado para guarda numa nova linha da matrix auxiliar
            k--; // ir para valor seguinte do arraySorted
            j = -1; // when this cycle ends it restarts the outer cycle so it starts searching the next sequence from the beginning (-1 because the cycle will still increment after this)
        }
    }
    // copy back to allSequences matrix
    for (j = 0; j < numberOfSequences; j++) {
        for (l = 0; l <= auxMatrix[j][0]; l++) {
            allSequences[j][l] = auxMatrix[j][l];
        }
        allSequences[j][l] = -1;

    }
    printf("allSequences:\n");
    printMatDefault(allSequences, numberOfSequences, 56);
    printf("\n");

}


/***
 * verifica se uma determinada peça é consistente na sequencia de jogo
 *
 * @param sequence matriz sequencia de pecas consistentes
 * @param index posicao da peça a ser inserida
 * @return 1 se consistente
 */
int isConsistent(int sequence[][MAX2], int index) {
//    primeira peça é sempre consistente
    if (index == 0) {
        return 1;
    }
//    se o lado esquerdo da peça inserida for igual ao lado direito da peça anterior
    else if (sequence[index - 1][1] == sequence[index][0]) {
        return 1;
    }
//    se o lado direito da peça inserida for igual ao lado direito da peça anterior, então roda-se a peça
    else if (sequence[index - 1][1] == sequence[index][1]) {
        invertBlock(sequence, index);
        return 1;
    }
//    se for a segunda peça a inserir e esta não for consistente com a primeira peça, então  testa-se com o lado esquerdo
// da primeira peça com o lado esquerdo da segunda peça
    else if (index == 1 && sequence[index - 1][0] == sequence[index][0]) {
        invertBlock(sequence, index - 1);
        return 1;
    }
//    se o lado esquerdo da primeira peça for igual lado direito da segunda peça
    else if (index == 1 && sequence[index - 1][0] == sequence[index][1]) {
        invertBlock(sequence, index - 1);
        invertBlock(sequence, index);
        return 1;
    }
//    se nao for consistente
    else {
        return 0;
    }
}


/***
 *
 * funcao que inverte a peça, isto é, roda a peça
 *  -> [0 1] fica [1 0]
 *
 * @param block matriz sequencia de pecas consistentes
 * @param index indice da peça a ser invertida
 */
void invertBlock(int block[][MAX2], int index) {
    int aux = 0;
    aux = block[index][1];
    block[index][1] = block[index][0];
    block[index][0] = aux;

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
void openFile(int type, int content[LINES][MAX2], int *numberOfHands, int *handSize) {
    FILE *file;
    int i = 0;
    char fileName[40], fOut[30];
    switch (type) {
        // Text files
        case 1:
            // printf("\nFiles existing:\n");
            // system("dir/b *.txt"); // scans all files with the extension "txt" in the root of the folder where the program executable is and prints them
            printf("\nFile name: ");
            scanf("%s", fileName);
            checkExtension(fileName);
            file = fopen(fileName, "r"); // opens the file with permissions to read only
            if (file == NULL) {
                printf("\nxx Error: Impossible to open the file '%s' xx\n", fileName);
                openFile(type, content, numberOfHands, handSize);
            } else {
                printf("\n** Success: File '%s' opened **\n", fileName);
                while (fgets(fOut, 29, file)) {
//                    printf("%s", fOut); // imprime todos os conteudos do ficheiro
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
                    } else {
                        content[i - 1][0] = fOut[0] - '0';
                        content[i - 1][1] = fOut[1] - '0';
                    }
                    i++;
                }
            }
            break;

            // Binary files
        case 2:

            break;

        default:
            break;
    }
}

void createGameFile(int content[LINES][MAX2], int numberOfHands, int handSize) {
    FILE *file;
    int i = 0;
    char fileName[40];
    // create txt file
    printf("\nFile name: ");
    scanf("%s", fileName);
    checkExtension(fileName);
    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
        createGameFile(content, numberOfHands, handSize);
    } else {
        // guardar numberOfHands e handSize
        for (i = 0; i < (numberOfHands * handSize) + 1; i++) {
            fprintf(file, "%d%d", content[i][0], content[i][1]);
            fprintf(file, "\n");
        }
        fclose(file);
    }
    // verificar nomes repetidos para evitar rewrite
}

/**
 * checks the filename the user inputted for the extension and if it doesn't exist adds it at the end
 * @param fileName name of the file requested by the user
 */
void checkExtension(char *fileName) {
    if (strstr(fileName, ".txt") == NULL) { // searches the substring ".txt" in the filename the user inputted
        strcat(fileName, ".txt");
    }
}