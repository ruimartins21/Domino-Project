
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>

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
            printf("\t\t\t\tNumber of blocks on each hand: ");
            scanf("%d", &choiceMade);
            return choiceMade;

        case 4:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Choose the blocks randomly\n");
            printf("\t\t\t\t2 - Choose the blocks manually\n");
            scanf("%d", &choiceMade);
            return choiceMade;

        case 5:
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

        case 6:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tSave game data in a file? (Y/N): ");
            getchar(); // avoids empty symbols like previous enters
            choiceMade = getchar(); // gets the character needed to answer by its ASCII code
            if(choiceMade != 'Y' && choiceMade != 'y' && choiceMade != 'N' && choiceMade != 'n'){
                printf("!!! Invalid answer !!!\n");
                return printMenu(path);
            }else{
                if(choiceMade == 'Y' || choiceMade == 'y') return 1;
                return 0;
            }
//            if(strcmp(choiceChar, "y") != 0 && strcmp(choiceChar, "Y") != 0 && strcmp(choiceChar, "n") != 0 && strcmp(choiceChar, "N") != 0){
//                printf("!!! Invalid answer !!!\n");
//                return printMenu(path);
//            } else {
//                if(strcmp(choiceChar, "y") == 0 || strcmp(choiceChar, "Y") == 0) return 1;
//                return 0;
//            }

        case 7:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Save game data in a text file\n");
            printf("\t\t\t\t2 - Save game data in a binary file\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 2) {
                printf("!!! Please choose a number between 1 & 2. !!!\n");
                return printMenu(path);
            } else {
                return choiceMade;
            }

        case 8:
            printf("\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - See the biggest sequence\n");
            printf("\t\t\t\t2 - See all the sequences\n");
            printf("\t\t\t\t3 - Search a sequence\n");
            printf("\t\t\t\t4 - Search a pattern in the sequences\n");
            printf("\t\t\t\t5 - Replace a pattern in the sequences\n");
            printf("\t\t\t\tChoice: ");
            scanf("%d", &choiceMade);
            if (choiceMade < 1 || choiceMade > 5) {
                printf("!!! Please choose a number between 1 & 5. !!!\n");
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
 * @param index Position of the block to be withdrawn to the player hand || if it's NULL it will get the lines given and "compress" the matrix to be that size only
 */
void compressMatrix(int matrix[][COLS], int lines, int index) {
    int i;
    if(index == -1){
        // it will compress the matrix to the size given from the lines parameter
        // after the size given fills with -1 until the limit size (28)
        for (i = lines; i < (lines+(28-lines)); i++) {
            matrix[i][0] = -1;
            matrix[i][1] = -1;
        }
    }else{
        for (; index < lines; index++) {
            matrix[index][0] = matrix[index + 1][0];
            matrix[index][1] = matrix[index + 1][1];
        }
        matrix[index - 1][0] = -1;
        matrix[index - 1][1] = -1;
    }
}


void printMat(int matrix[][MAX3], int lines) {
    int l = 0;
//    for (l = 0; l < lines; l++) {
//
//        printf("[%d %d] ", matrix[l][0], matrix[l][1]);
////        printf("%d %d\n", matrix[l][0], matrix[l][1]);
//    }
    while(l < lines && (matrix[l][0] != -1 || matrix[l][1] != -1)){
        printf("[%d %d] ", matrix[l][0], matrix[l][1]);
        l++;
    }
}

/**
 * shows the user all the blocks that are available to choose (this prevents out of bounds selections from the user)
 * @param matrix game matrix that has the unused blocks
 * @return returns the counter of blocks available to choose from for further conditioning from the user inputs
 */
int blocksAvailable(int matrix[][COLS]) {
    int i = 0;
    printf("\n\t\t\t\t### Available Blocks ###\n");
    while (i < LINES && (matrix[i][0] != -1 || matrix[i][1] != -1)) {
        printf("\t#%2d = [%d|%d]", i + 1, matrix[i][0], matrix[i][1]);
        if ((i + 1) % 5 == 0 && i != 0) {
            printf("\n");
        }
        i++;
    }
    return i;
}

/**
 * The user chooses block by block wich ones he wants in each hand
 * it's showed the game matrix so he can see the available blocks
 * after each choice the game matrix goes through the compressMatrix because a block was "removed" from it and passed to the hands matrix
 * @param matrix game matrix with the unused blocks
 * @param hand matrix with all the hands generated
 * @param handSize size of each hand
 * @param numberOfHands number of hands existing
 */
void generateManualHand(int matrix[][COLS], int hand[][COLS], int handSize, int numberOfHands){
    int i, j, k = 0, blocksLimit, blockId;
    for (i = 0; i < numberOfHands; i++) {
        printf("\n## %2d hand ##\n", i+1);
        for (j = 0; j < handSize; j++) {
            blocksLimit = blocksAvailable(matrix);
            printf("\n%2d block: ", j+1);
            scanf("%d", &blockId);
            if(blockId < 1 || blockId > blocksLimit){
                printf("!!! Choose a valid number !!!");
                j--;
                continue;
            }
            blockId -= 1;
            // gets the block chosen in the game matrix and stores it in the hands matrix
            hand[k][0] = matrix[blockId][0];
            hand[k][1] = matrix[blockId][1];
            // sends to compressMatrix to remove the block chosen from the game matrix
            compressMatrix(matrix, blocksLimit, blockId);
            k++;
        }
    }
}

/**
 * Function that handles all the editing the user wishes to do on the generated hands
 * It handles the changes of blocks between the hands matrix and the game matrix
 * @param matrix game matrix with the unused blocks
 * @param hand matrix with all the hands generated
 * @param handSize size of each hand
 * @param numberOfHands number of hands existing
 * @return returns 0 if the user doesn't want to edit anything and 1 if the user edited something
 */
int editHands(int matrix[][COLS], int hand[][COLS], int handSize, int numberOfHands){
    int i, j, handId = 0, removeId, addId = 0, blocksLimit, edited = 0, validate = 0, choice = 'y';
    while(1){
        for(i = 0; i < numberOfHands; i++){
            printf("\n#%2d = Hand %d: ", i+1, i+1);
            printHand_uglify(hand, handSize, i);
        }
        while(!validate){
            printf("\nDo you wish to change anything before proceeding? (Y/N): ");
            getchar();
            choice = getchar();
            if(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n'){
                printf("!!! Invalid answer !!!\n");
                validate = 0;
                continue;
            }
            validate = 1;
        }
        validate = 0;
        if(choice == 'n'){
            // if the user decided to not edit, since it's inside a loop, we need to check if he edited anything before
            return edited;
        }
        if(numberOfHands > 1){
            printf("\nEnter the id of the hand to edit: ");
            scanf("%d", &handId);
            handId -= 1;
            handId = (handId == 0 ? handId : handId * handSize); // arithmetic to reach the desired hand on the matrix of hands
        }
        for(i = 0, j = handId; i < handSize; i++, j++){
            printf(" #%2d = [%d|%d]", i+1, hand[j][0], hand[j][1]);
        }
        printf("\nWhich block do you want to change? ");
        scanf("%d", &removeId);
        removeId -= 1;
        // to this removeId it's needed to add the previous handId index so we can reach the correct hand inside the hands matrix and then move the desired index
        removeId += handId;
        blocksLimit = blocksAvailable(matrix);
        while(addId < 1 || addId > blocksLimit){
            printf("\nChoose a block to insert from the available blocks above: ");
            scanf("%d", &addId);
        }
        addId -= 1;
        // swaps the block chosen from the game matrix with the block chosen on the hand
        i = matrix[addId][0];
        j = matrix[addId][1];
        matrix[addId][0] = hand[removeId][0];
        matrix[addId][1] = hand[removeId][1];
        hand[removeId][0] = i;
        hand[removeId][1] = j;
        edited = 1;
        // reset variables
        addId = 0;
        removeId = 0;
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
 * Opens the file with the name the user inputs if it exists, if not, keeps asking for a valid name
 * @param type type = 1 means it's a text file, type = 2 means it's a binary file
 * @param handsMat matrix where will be stored the hands stored in the file
 * @param gameMat matrix where will be stored the game stored in the file (the game that doesn't have the blocks used in the hands)
 * @param numberOfHands number of hands in the hands matrix
 * @param handSize size of each hand
 */
void openFile(char fileName[], int type, int handsMat[LINES][COLS], int gameMat[LINES][COLS], int *numberOfHands, int *handSize) {
    FILE *file = NULL;
    int i = 0, auxInt, j = 0;
    char fOut[30];
    switch (type) {
        // Text files
        case 1:
//            printf("\nFiles existing:\n");
//            system("dir/b *.txt"); // scans all files with the extension "txt" in the root of the folder where the program executable is and prints them
            checkExtension(fileName, ".txt");
            if ((file = fopen(fileName, "r")) != NULL) {
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
                    } else if(i < ((*numberOfHands)*(*handSize))+1){
                        handsMat[i - 1][0] = fOut[0] - '0';
                        handsMat[i - 1][1] = fOut[1] - '0';
                    // after the matrix of the hands comes the game matrix
                    }else{
                        gameMat[j][0] = fOut[0] - '0';
                        gameMat[j][1] = fOut[1] - '0';
                        j++;
                    }
                    i++;
                }
                // compresses the game matrix to the size extracted from the file
                compressMatrix(gameMat, j, -1);
            } else {
                printf("\nxx Error: Impossible to open the file '%s' xx\n", fileName);
                openFile(fileName, type, handsMat, gameMat, numberOfHands, handSize);
            }
            fclose(file);
            break;

        // Binary files
        case 2:
            // printf("\nFiles existing:\n");
            // system("dir/b *.bin"); // scans all files with the extension "bin" in the root of the folder where the program executable is and prints them
            checkExtension(fileName, ".bin");
            if((file = fopen(fileName, "rb")) != NULL)
            {
                while(!feof(file))
                {
                    if(i == 0){
                        fread(numberOfHands, sizeof(int), 1, file);
                        fread(handSize, sizeof(int), 1, file);
                    }else if(i < ((*numberOfHands)*(*handSize))+1){
                        fread(&auxInt, sizeof(int), 1, file);
                        handsMat[i-1][0] = auxInt;
                        fread(&auxInt, sizeof(int), 1, file);
                        handsMat[i-1][1] = auxInt;
                    }else{
                        fread(&auxInt, sizeof(int), 1, file);
                        gameMat[j][0] = auxInt;
                        fread(&auxInt, sizeof(int), 1, file);
                        gameMat[j][1] = auxInt;
                        j++;
                    }
                    i++;
                }
                // compresses the game matrix to the size extracted from the file
                // needed to decrese by 1 the size because of the cycles the reading does
                compressMatrix(gameMat, j-1, -1);
            } else {
                printf("\nxx Error: Impossible to open the file '%s' xx\n", fileName);
                openFile(fileName, type, handsMat, gameMat, numberOfHands, handSize);
            }
            fclose(file);
            break;

        default: break;
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
void editFile(char fileName[], int type, int handsMat[LINES][COLS], int gameMat[LINES][COLS], int numberOfHands, int handSize){
    FILE *file = NULL;
    int i = 0, auxInt;
    switch (type) {
        // Text files
        case 1:
            if (!fileExists(fileName)) {
                printf("\nxx Error: The file '%s' doesnt exist xx\n", fileName);
                return;
            }
            if ((file = fopen(fileName, "w")) != NULL) {
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
                    fprintf(file, "\n%d%d", handsMat[i][0], handsMat[i][1]);
                }
                // stores the game matrix with the unused blocks
                for (i = 0 ; i < (28 - (numberOfHands * handSize)); i++) {
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
            if (!fileExists(fileName)) {
                printf("\nxx Error: The file '%s' doesnt exist xx\n", fileName);
                return;
            }
            if((file = fopen(fileName, "wb")) != NULL)
            {
                // stores the numberOfHands and the handSize
                fwrite(&numberOfHands, sizeof(int), 1, file);
                fwrite(&handSize, sizeof(int), 1, file);
                // stores the matrix of the hands generated
                for (i = 0; i < (numberOfHands * handSize); i++) {
                    auxInt = handsMat[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = handsMat[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
                // stores the game matrix with the unused blocks
                for (i = 0 ; i < (28 - (numberOfHands * handSize)); i++) {
                    auxInt = gameMat[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = gameMat[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
            }else{
                printf("\nxx Error: Impossible to write to the file '%s' xx\n", fileName);
                return;
            }
            fclose(file);
            break;

        default: break;
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
void createGameFile(int type, int handsMat[LINES][COLS], int gameMat[LINES][COLS], int numberOfHands, int handSize){
    FILE *file = NULL;
    int i = 0, auxInt;
    char fileName[40];
    switch (type) {
        // create txt file
        case 1:
            printf("\nSave the game as: ");
            scanf("%s", fileName);
            checkExtension(fileName, ".txt");
            if (fileExists(fileName)) {
                printf("\nxx Error: The file '%s' already exists xx\n", fileName);
                createGameFile(type, handsMat, gameMat, numberOfHands, handSize);
                return;
            }
            if ((file = fopen(fileName, "w")) != NULL) {
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
                    fprintf(file, "\n%d%d", handsMat[i][0], handsMat[i][1]);
                }
                // stores the game matrix with the unused blocks
                for (i = 0 ; i < (28 - (numberOfHands * handSize)); i++) {
                    fprintf(file, "\n%d%d", gameMat[i][0], gameMat[i][1]);
                }
            } else {
                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
                createGameFile(type, handsMat, gameMat, numberOfHands, handSize);
            }
            fclose(file);
            break;

        // create bin file
        case 2:
            printf("\nSave the game as: ");
            scanf("%s", fileName);
            checkExtension(fileName, ".bin");
            if (fileExists(fileName)) {
                printf("\nxx Error: The file '%s' already exists xx\n", fileName);
                createGameFile(type, handsMat, gameMat, numberOfHands, handSize);
                return;
            }
            if((file = fopen(fileName, "wb")) != NULL)
            {
                // stores the numberOfHands and the handSize
                fwrite(&numberOfHands, sizeof(int), 1, file);
                fwrite(&handSize, sizeof(int), 1, file);
                // stores the matrix of the hands generated
                for (i = 0; i < (numberOfHands * handSize); i++) {
                    auxInt = handsMat[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = handsMat[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
                // stores the game matrix with the unused blocks
                for (i = 0 ; i < (28 - (numberOfHands * handSize)); i++) {
                    auxInt = gameMat[i][0];
                    fwrite(&auxInt, sizeof(int), 1, file);
                    auxInt = gameMat[i][1];
                    fwrite(&auxInt, sizeof(int), 1, file);
                }
            }else{
                printf("\nxx Error: Impossible to create the file '%s' xx\n", fileName);
                createGameFile(type, handsMat, gameMat, numberOfHands, handSize);
            }
            fclose(file);
            break;

        default: break;
    }
}

/**
 * checks the filename the user inputted for the extension and if it doesn't exist adds it at the end
 * @param fileName name of the file requested by the user
 */
void checkExtension(char fileName[], char extension[]){
    if (strstr(fileName, extension) == NULL) { // searches for the extension in the filename the user inputted
        strcat(fileName, extension);
    }
}

/**
 * tries to open a file with the name inputted to check if it exists before writing on it
 * prevents rewriting on an existing file with the name the user wrote
 * @param fileName
 * @return returns 0 if there's no file with that name and 1 if there is
 */
int fileExists(char fileName[]){
    FILE *file = fopen(fileName, "r");
    if (file == NULL) return 0;
    return 1;
}