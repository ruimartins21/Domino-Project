/// @file core.c
/// @brief Gathers all the core functions of the project
/// @copyright

#include "core.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * Function that generates player hand randomly
 * -> Runs the number of hands chosen by the user, for each one runs all the blocks of the hand
 * -> Generates a random number confined to the values 0 to 27
 * -> Returns the block positioned at the index generated and copies its content to another place and frees the space on memory of the previous one
 *
 * @param matrix Initial game matrix (all pieces)
 * @param hand Matrix with the player pieces (hand game)
 * @param linesHand Matrix lines of the player hand
 * @param qtSet Number of hands to generate
 */
void generateRandomHand(GAME *game, HANDS *hands) {

    long ultime;
    time(&ultime);
    srand((unsigned)ultime);

    int i = 0, j = 0, randValue = 0, linesCount = 0;
    HAND *handAux = NULL;
    BLOCK *delBlock = NULL, *blockAux = NULL;
    hands->pfirstHand = NULL;
    for (i = 0; i < hands->numberOfHands; i++) {
        handAux = (HAND*)malloc(sizeof(HAND));
        for (j = 0; j < hands->handSize; j++) {
            if(linesCount < 27){
                randValue = 0 + rand() % ((MAX28-1) - linesCount); // it needs to be sent MAX28 - 1 because the popBlock function works with numbers between 0 and 27
            }else{
                randValue = 0;
            }
            delBlock = popBlock(game, randValue); // retrieves the block to pass it to the hand and remove from the game structure
            blockAux = transferBlock(delBlock);
            if(handAux->pfirstBlock == NULL){ // it's the first block to be inserted in the hand
                blockAux->pnextBlock = NULL; // it will be used the insertion at the head, so the first block to be inserted will be the one at the tail
            }else{
                blockAux->pnextBlock = handAux->pfirstBlock;
            }
            handAux->pfirstBlock = blockAux;
            linesCount++;
        }
        handAux->pnextHand = hands->pfirstHand;
        hands->pfirstHand  = handAux;
    }
}

/**
  * Function to generate sequences from one hand
  * Checks if the block that is inserted in the sequence matrix is consistent, if it is tries to insert the next block
  * if it's not consistent checks the next blocks for consistency with the last inserted block until a block is considered consistent
  * than it inserts it in the sequence and each time a block is inserted in the sequence, the 3rd column of the hands matrix is changed to 0
  * that means the block is currently being used
  * That way when the algorithm runs again to check another block, it ignores the blocks that have that 3rd column at 0
  * @param matrix Initial matrix (with the number of blocks existing at the time)
  * @param handSize size of the hand
  * @param sequence sequence matrix with the blocks that are consistent
  * @param allSequences is the matrix that will store all the eligible sequences
  * @param inserted number of blocks inserted in sequence matrix
  * @return
  */

/*
int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, int *count, int handId) {
    int i = 0;
    BLOCK *blockAux = NULL;
    HAND *handAux = NULL;

    handAux = pHands->pfirstHand; // vai ser usado para varias maos


    handId = handId % pHands->numberOfHands; //  mao atual de jogo
//    printf("Mão[%d]\n", handId);

//    ir buscar a mao correspondente
    while (i != handId){
        handAux = handAux->pnextHand;
        i++;
    }
    blockAux = handAux->pfirstBlock;

    for (i = 0; i < pHands->handSize; i++) {
//         if the block is available
        if (blockAux->available == 1) {

            BLOCK *pnew = (BLOCK *) malloc(sizeof(BLOCK));
//            nova peca a inserir na sequencia
            pnew->leftSide = blockAux->leftSide;
            pnew->rightSide = blockAux->rightSide;
            pnew->available = 0;
            pnew->pnextBlock = NULL;
            pnew->prevBlock = NULL;


            if (isConsistent(pSequence, pnew, inserted) == 1) {
                if(inserted == 0) { // se for a primeira peça na sequencia

                    pSequence->pfirstBlock = pnew;
                    pSequence->pfirstBlock->pnextBlock = pnew;
                    pSequence->pfirstBlock->prevBlock = pnew;
                }else{
                    pSequence->pfirstBlock->prevBlock->pnextBlock = pnew;
                    pnew->prevBlock = pSequence->pfirstBlock->prevBlock;
                    pnew->pnextBlock = pSequence->pfirstBlock;
                    pSequence->pfirstBlock->prevBlock = pnew;
                }


                inserted++;
                pSequence->sizeOfSequence++;
                blockAux->available = 0; // block is now unavailable

                if(pSequence->sizeOfSequence == pHands->handSize)
                    (*count)++;

                printSequence(*pSequence);
//                printf("------------------------------------------------------\n");
//                printHand(*pHands);

                saveSequence(pAllsequences, pSequence);
                if(pHands->numberOfHands > 1)
                    handId = handId+1;
                generateSequence(pHands, pSequence, pAllsequences, inserted, count, handId);

                BLOCK *paux = pSequence->pfirstBlock->prevBlock;
                blockAux->available = 1; // block is available if it didn't fit
                pSequence->pfirstBlock->prevBlock = pSequence->pfirstBlock->prevBlock->prevBlock;
                pSequence->pfirstBlock->prevBlock->pnextBlock = pSequence->pfirstBlock;
                free(paux);
                pSequence->sizeOfSequence --;
                inserted--;
            }
        }
        if(blockAux->pnextBlock != NULL)
            blockAux = blockAux->pnextBlock;
    }
    return 0;
}
*/

int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, int *count) {
    int i = 0;
    BLOCK *blockAux = NULL;
    HAND *handAux = NULL;

    handAux = pHands->pfirstHand; // vai ser usado para varias maos
    blockAux = handAux->pfirstBlock;

    for (i = 0; i < pHands->handSize; i++) {
//         if the block is available
        if (blockAux->available == 1) {

            BLOCK *pnew = (BLOCK *) malloc(sizeof(BLOCK));
//            nova peca a inserir na sequencia
            pnew->leftSide = blockAux->leftSide;
            pnew->rightSide = blockAux->rightSide;
            pnew->available = 0;
            pnew->pnextBlock = NULL;
            pnew->prevBlock = NULL;

            if (isConsistent(pSequence, pnew, inserted) == 1) {
                if(inserted == 0) { // se for a primeira peça na sequencia
                    pSequence->pfirstBlock = pnew;
                    pSequence->pfirstBlock->pnextBlock = pnew;
                    pSequence->pfirstBlock->prevBlock = pnew;
                }else{
                    pSequence->pfirstBlock->prevBlock->pnextBlock = pnew;
                    pnew->prevBlock = pSequence->pfirstBlock->prevBlock;
                    pnew->pnextBlock = pSequence->pfirstBlock;
                    pSequence->pfirstBlock->prevBlock = pnew;
                }

                inserted++;
                pSequence->sizeOfSequence++;
                blockAux->available = 0; // block is now unavailable

                if(pSequence->sizeOfSequence == pHands->handSize)
                    (*count)++;

//                printf("antes de gravar\n");
//                printSequence(*pSequence);

                saveSequence(pAllsequences, *pSequence);
//                printf("depois de gravar\n");
//                printSequence(*pSequence);
//                printf("--------------------------\n\n");
                generateSequence(pHands, pSequence, pAllsequences, inserted, count);

                BLOCK *paux = pSequence->pfirstBlock->prevBlock;
                blockAux->available = 1; // block is available if it didn't fit
                pSequence->pfirstBlock->prevBlock = pSequence->pfirstBlock->prevBlock->prevBlock;
                pSequence->pfirstBlock->prevBlock->pnextBlock = pSequence->pfirstBlock;
                free(paux);
                pSequence->sizeOfSequence --;
                inserted--;
            }
        }
        if(blockAux->pnextBlock != NULL){
            blockAux = blockAux->pnextBlock;
        }
    }
    return 0;
}


/**
 * Function responsible for storing all eligible sub-sequences / sequences in the sequences matrix
 * Inserts in the first column of all sequences the size of it
 * All the columns not used for a certain sequence (since the matrix that is storing them has to have a maximum size)
 * are going to be "-1" to be considered "empty" spaces
 * @param sequence is the sequence that is going to be stored
 * @param allSequences is the matrix that stores all the sequences
 * @param sizeOfSequence the size of the sequence to store
 * @param handSize is the size of the hands, required for some conditions
 */
void saveSequence(ALLSEQUENCES *allSequences, SEQUENCE pSequence) {
    // Soluçao Ricardo - INTS

//    SEQUENCE *newSequence = (SEQUENCE*)malloc(sizeof(SEQUENCE));
//    *newSequence = pSequence;
//    newSequence->pfirstBlock = NULL;
//    BLOCK *newBlock = NULL, *blockAux = pSequence.pfirstBlock, *lastBlock = NULL;
//    int i;
//    // creates new memory spaces for the sequence blocks
//    // because the ones generated and passed through pSequence will be modified in generateSequence function
//    for (i = 0; i < newSequence->sizeOfSequence && blockAux != NULL; i++) {
//        newBlock = (BLOCK*)malloc(sizeof(BLOCK));
//        *newBlock = *blockAux;
//        newBlock->pnextBlock = NULL; // it will always be the last block
//        if(newSequence->pfirstBlock == NULL){
//            newBlock->prevBlock  = newBlock;
//            newSequence->pfirstBlock = newBlock;
//        }else{
//            // insertion at the tail in a doubly linked list
//            lastBlock = newSequence->pfirstBlock;
//            while(lastBlock->pnextBlock != NULL){
//                lastBlock = lastBlock->pnextBlock;
//            }
//            newSequence->pfirstBlock->prevBlock = newBlock; // first block pointing to the last one
//            lastBlock->pnextBlock = newBlock; // previous last block pointing to the new last block
//            newBlock->prevBlock = lastBlock; // last block pointing to the previous block
//        }
//        blockAux = blockAux->pnextBlock;
//    }
//    // insert new sequences at the head
//    if(allSequences->pfirstSequence == NULL){
//        newSequence->pnextSequence = NULL;
//        allSequences->pfirstSequence = newSequence;
//    }else{
//        newSequence->pnextSequence = allSequences->pfirstSequence;
//        allSequences->pfirstSequence = newSequence;
//    }
//    allSequences->numberOfSequences++;

    // Solucao Ricardo - STRINGS
    STRINGSEQ *newSequence = (STRINGSEQ*)malloc(sizeof(STRINGSEQ));
    newSequence->sizeOfSequence = pSequence.sizeOfSequence;
    BLOCK *blockAux = pSequence.pfirstBlock;
    int i;
    // creates space for all the values existing in the sequence
    // the size of the sequence is the ammount of blocks, so the size needed is the double, for each value, and each block as 2 values
    // the + 1 at the end is for the end of the string '\0' when there's a sequence that uses all the blocks
    char *blockString = (char*)malloc( sizeof(char) * (newSequence->sizeOfSequence*2) + 1 );
    *blockString = '\0'; // initialize the string as empty
    int blockStringLen = 0;
    for (i = 0; i < newSequence->sizeOfSequence && blockAux != NULL; i++) {
        blockStringLen = strlen(blockString);
        *(blockString + blockStringLen)     = '0' + blockAux->leftSide;
        *(blockString + (blockStringLen+1)) = '0' + blockAux->rightSide;
        *(blockString + (blockStringLen+2)) = '\0';
        blockAux = blockAux->pnextBlock;
    }
    // at this point there's a string created with all the values of each block existing in the sequence
    newSequence->sequence = createDynamicString(blockString);
    free(blockString);
    //insert new sequences at the head
    if(allSequences->pfirstSequence == NULL){
        newSequence->pnextStringSeq = NULL;
        allSequences->pfirstSequence = newSequence;
    }else{
        newSequence->pnextStringSeq = allSequences->pfirstSequence;
        allSequences->pfirstSequence = newSequence;
    }
    allSequences->numberOfSequences++;


    // Soluçao Rui
//    int i =0;
//    SEQUENCE *pnew = (SEQUENCE*)malloc(sizeof(SEQUENCE));
//    pnew->sizeOfSequence = pSequence->sizeOfSequence;
//    BLOCK *pnewB = (BLOCK*)malloc(sizeof(BLOCK));
//    pnewB = pSequence->pfirstBlock;
//    pnewB->pnextBlock = NULL;
//    pnewB->prevBlock = NULL;
//    pnew->pfirstBlock = pnewB;
//
//
//
//    for(i=1;i<pSequence->sizeOfSequence;i++){
//        BLOCK *pnewBaux = (BLOCK*)malloc(sizeof(BLOCK));
//        *pnewBaux = *pSequence->pfirstBlock->pnextBlock;
//        pnewB->pnextBlock = pnewBaux;
//        pnewB->prevBlock = pnewBaux;
//        pnewBaux->prevBlock = pnewB;
//        pnewBaux->pnextBlock = pnew->pfirstBlock;
//        pnewB = pnewB->pnextBlock;
//        pSequence->pfirstBlock = pSequence->pfirstBlock->pnextBlock;
//
//    }
//
//    pnew->pnextSequence = NULL;
//
//
//    if(allSequences->pfirstSequence == NULL){
//        allSequences->pfirstSequence = pnew;
//        allSequences->numberOfSequences++;
//        return;
//    }
//    pnew->pnextSequence = allSequences->pfirstSequence;
//    allSequences->pfirstSequence = pnew;
//    allSequences->numberOfSequences++;



//    o que estava 1 fase
//    SEQUENCE *pnew = (SEQUENCE*)malloc(sizeof(SEQUENCE));
//    *pnew = *pSequence;
//    if(allSequences->pfirstSequence == NULL){
//        allSequences->pfirstSequence = pnew;
//        allSequences->numberOfSequences++;
//        return;
//    }
//    pnew->pnextSequence = allSequences->pfirstSequence;
//    allSequences->pfirstSequence = pnew;
//    allSequences->numberOfSequences++;

//    sortAllSequences(allSequences);

//    } else if(allSequences->numberOfSequences == MAX5000){
//        printf("chegou aos 5000\n");

//    printSequences(*allSequences,0);

}

/**
  * Function responsible for sorting the allSequences matrix in descending order of the size of each sequences
  * Orders by an ordered array that has the size of each hand, and searches in the first column of the allSequences matrix that size
  * @param allSequences matrix that has all the sequences and sub-sequences
  */
//

void sortAllSequences(ALLSEQUENCES *allSequences) {

    printSequences(*allSequences, 0);
    /* Sort the above created Linked List */
    mergeSort(&(allSequences->pfirstSequence));
    printSequences(*allSequences, 0);


}

STRINGSEQ *findSequenceOfSize(ALLSEQUENCES allSequences, int size, unsigned long *costModel){
    STRINGSEQ *sequenceAux = allSequences.pfirstSequence;
    *costModel = 0;
    unsigned long lo = 0, hi = allSequences.numberOfSequences-1;
    while (lo <= hi || sequenceAux != NULL) {
        *costModel += 1;
        unsigned long mid = (lo + hi) / 2;
        if      (size < sequenceAux->sizeOfSequence) hi = mid - 1;
        else if (size > sequenceAux->sizeOfSequence) lo = mid + 1;
        else return sequenceAux;
        sequenceAux = sequenceAux->pnextStringSeq;
    }
    return NULL;
}

/* sorts the linked list by changing pnextSequence pointers (not sizeOfSequence) */
void mergeSort(struct sequence* *headRef)
{
    SEQUENCE *head = *headRef;
    SEQUENCE *a = NULL;
    SEQUENCE *b = NULL;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->pnextSequence == NULL))
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    frontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    mergeSort(&a);
    mergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = sortedMerge(a, b);
}

SEQUENCE *sortedMerge(SEQUENCE *a, SEQUENCE *b)
{
    SEQUENCE *result = NULL;

    /* Base cases */
    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    /* Pick either a or b, and recur */
    if (a->sizeOfSequence <= b->sizeOfSequence)
    {
        result = a;
        result->pnextSequence = sortedMerge(a->pnextSequence, b);
    }
    else
    {
        result = b;
        result->pnextSequence = sortedMerge(a, b->pnextSequence);
    }
    return(result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra sequence2 should go in the front list.
     Uses the fast/slow pointer strategy.  */
void frontBackSplit(SEQUENCE *source, struct sequence* *frontRef, struct sequence* *backRef)
{
    SEQUENCE *fast = NULL;
    SEQUENCE *slow = NULL;
    if (source==NULL || source->pnextSequence==NULL)
    {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->pnextSequence;

        /* Advance 'fast' two nodes, and advance 'slow' one sequence2 */
        while (fast != NULL)
        {
            fast = fast->pnextSequence;
            if (fast != NULL)
            {
                slow = slow->pnextSequence;
                fast = fast->pnextSequence;
            }
        }

        /* 'slow' is before the midpoint in the list, so split it in two
          at that point. */
        *frontRef = source;
        *backRef = slow->pnextSequence;
        slow->pnextSequence = NULL;
    }
}

//
//void merge(ALLSEQUENCES *allsequences, ALLSEQUENCES *paux, int lo, int mid, int hi) {
//    SEQUENCE *seqAuxK = allsequences->pfirstSequence, *pantK = NULL;
//    int i = lo, j = mid + 1, k, iter = 0;
//    for (k = lo; k <= hi; k++){// copy
//        paux = allsequences;
//    }
//
//    SEQUENCE *seqAuxJ = paux->pfirstSequence, *pantJ = NULL;
//    SEQUENCE *seqAuxI = paux->pfirstSequence, *pantI = NULL;
//
//
//    for (k = lo; k <= hi; k++) { // merge
//        while(iter != k){
//            pantK = seqAuxK;
//            seqAuxK = seqAuxK->pnextSequence;
//            iter++;
//        }
//        iter = 0;
//        while(iter != j){
//            pantJ = seqAuxJ;
//            seqAuxJ = seqAuxJ->pnextSequence;
//            iter++;
//        }
//        iter = 0;
//        while(iter != i){
//            pantI = seqAuxI;
//            seqAuxI = seqAuxI->pnextSequence;
//            iter++;
//        }
//        if (i > mid){
//            if(seqAuxK == allsequences->pfirstSequence){
//                pantJ->pnextSequence = seqAuxJ->pnextSequence;
//                seqAuxJ->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxJ;
//            }else{
//                pantK->pnextSequence = seqAuxJ;
//                seqAuxJ->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxJ;
//            }
//
//        }else if (j > hi){
//            if(pantK == NULL){
//                seqAuxI->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxI;
//            }else{
//                pantK->pnextSequence = seqAuxJ;
//                seqAuxJ->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxJ;
//            }
//        }else if ( seqAuxJ->sizeOfSequence < seqAuxI->sizeOfSequence){
//            if(pantK == NULL){
//                seqAuxJ->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxJ;
//            }else{
//                pantK->pnextSequence = seqAuxJ;
//                seqAuxJ->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxJ;
//            }
//        }else{
//            if(pantK == NULL){
//                seqAuxI->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxI;
//            }else{
//                pantK->pnextSequence = seqAuxJ;
//                seqAuxJ->pnextSequence = seqAuxK->pnextSequence;
//                seqAuxK = seqAuxJ;
//            }
//        }
//
//    }

//    for (k = lo; k <= hi; k++) { // merge
//        if (i > mid) a[k] = aux[j++];
//        else if (j > hi) a[k] = aux[i++];
//        else if (aux[j] < aux[i]) a[k] = aux[j++];
//        else a[k] = aux[i++];
//    }
//}


/**
 * Checks if a block is consistent with the last placed block on the sequence matrix
 * @param sequence is the matrix of the current sequence
 * @param index is the index of the block to insert
 * @return returns 1 if it is consistent, and 0 if not
// */
int isConsistent(SEQUENCE *pSequence, BLOCK *newBlock, int inserted) {
    // first block is always consistent
    if (inserted == 0) {
        return 1;
    }

        // if the left side of the block to insert is equal to the right side of the last block
    if (newBlock->leftSide == pSequence->pfirstBlock->prevBlock->rightSide) {
        return 1;
    }
        // if the right side of the block to insert is equal to the right side of the last block then invert the block and inserts it
    else if (newBlock->rightSide == pSequence->pfirstBlock->prevBlock->rightSide) {
        invertBlock(newBlock);
        return 1;
    }
        // if it's the second block to be inserted and if it's not consistent, it's tested inverting the first block inserted
    else if (inserted == 1 && newBlock->leftSide == pSequence->pfirstBlock->leftSide ) {
        invertBlockSequence(pSequence);
        return 1;
    }
        // if the right side of the block is equal to the left side of the last block
    else if (inserted == 1 && newBlock->rightSide == pSequence->pfirstBlock->leftSide ) {
        invertBlockSequence(pSequence);
        invertBlock(newBlock);
        return 1;
    }
        // if it's not consistent
    else {
        return 0;
    }
}

/**
 * Inverts a block
 * @param block is the block to be inverted
 * @param index is the blocks' index on the matrix passed
 */

void invertBlock(BLOCK *pBlock) {
    int aux = 0;
    aux = pBlock->leftSide;
    pBlock->leftSide = pBlock->rightSide;
    pBlock->rightSide = aux;
}

void invertBlockSequence(SEQUENCE *pSequence) {
    int aux = 0;
    aux = pSequence->pfirstBlock->leftSide;
    pSequence->pfirstBlock->leftSide = pSequence->pfirstBlock->rightSide;
    pSequence->pfirstBlock->rightSide = aux;
}