/// @file core.c
/// @brief Gathers all the core functions of the project
/// @copyright

#include "core.h"
#include "interface.h"
#include <stdio.h>
#include <time.h>
#include <assert.h>

/***
 * Function that generates player hand randomly
 * -> Runs the number of hands chosen by the user, for each one runs all the blocks of the hand
 * -> Generates a random number confined to the values 0 to 27
 * -> Removes the block from the GAME structure and inserts it into the proper hand
 *
 * @param game is the structure with all the unused blocks
 * @param hands structure that has all the hands created in the game and the respective blocks
 */
void generateRandomHand(GAME *game, HANDS *hands) {
    long ultime;// used to not generate the same random number
    time(&ultime);
    srand((unsigned)ultime);

    int i = 0, j = 0, randValue = 0, linesCount = 0;
    HAND *handAux = NULL;
    BLOCK *delBlock = NULL, *blockAux = NULL;
    hands->pfirstHand = NULL;
    for (i = 0; i < hands->numberOfHands; i++) {
        handAux = (HAND*)malloc(sizeof(HAND));  // current hand that will be filled with the random given blocks
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
 * Function to generate sequences from the hands (one or more)
 * -> Finds wich hand has to play by a selected pattern **
 * -> Runs all the blocks of a hand and checks if each one is available to be played on the sequence, if it is, checks if it's consistent
 * -> After the consistency checked, the block is used on the sequence structure (Insert at the tail). The blocks are doubly linked because, this way,
 * from the first block we can access the last one
 * -> if it's not consistent, the number of blocks inserted in the sequence is decremented and the last block inserted is removed
 * ** Multiple Hands Game [4]: Hand 1 plays, hand 2 plays if it has a consistent block, hand 3 doesn't have a consistent block and passes to the 4th hand
 * hand 4 plays, hand 1 doesn't have a block to play then recursively the block played by the 4th hand is removed, replacing it with another that fits.
 * If it doesn't have, again recursively goes to the hand 3, removes the one played by it, tries again with another, and so on until the 1st hand plays again
 * This way sequences with size 1 will be only possible with the blocks from the 1st hand
 *
 * @param pHands Structure that stores all the games' hands
 * @param pSequence Structure that will save the sequence at each play
 * @param pAllsequences Structure responsible for storing all the sequences generated
 * @param inserted Number of blocks inserted in a sequence
 * @param count Counter for sequences generated
 * @param handId Identifier of the current hand playing
 * @param costOfGenerate used to know the cost for this function
 * @return returns 0 at the end of the function
 */
int generateSequence(HANDS *pHands, SEQUENCE *pSequence, ALLSEQUENCES *pAllsequences, int inserted, unsigned long *count, int handId, unsigned long *costOfGenerate) {
    int i = 0;
    BLOCK *blockAux = NULL;
    HAND *handAux = NULL;
    handId = handId % pHands->numberOfHands; //  To know the current hand that is being played
    handAux = pHands->pfirstHand;
    //    Find hand to be played
    while (i != handId){
        handAux = handAux->pnextHand;
        i++;
    }
    blockAux = handAux->pfirstBlock;    // first block of the hand to be played
    for (i = 0; i < pHands->handSize; i++) {
        (*costOfGenerate)++;
//         if the block is available
        if (blockAux->available == 1) {
//            new block in the sequence
            BLOCK *pnew = (BLOCK *) malloc(sizeof(BLOCK));
            pnew->leftSide = blockAux->leftSide;
            pnew->rightSide = blockAux->rightSide;
            pnew->available = 0;
            pnew->pnextBlock = NULL;
            pnew->prevBlock = NULL;
            if (isConsistent(pSequence, pnew, inserted) == 1) {
                if(inserted == 0) { // If it's the first block in the sequence
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
                // Count only the max sequences
                if(pSequence->sizeOfSequence == pHands->handSize)
                    (*count)++;
                saveSequence(pAllsequences, *pSequence);
//                if it exists more than one hand, adds handId for it to go to the next hand in the next iteration
                if(pHands->numberOfHands > 1)
                    handId = handId+1;
                generateSequence(pHands, pSequence, pAllsequences, inserted, count, handId, costOfGenerate);
                BLOCK *paux = pSequence->pfirstBlock->prevBlock;
                blockAux->available = 1; // block is available if it didn't fit
                // Puts the last block of the sequence equal to the last-but-one block, removing the last block and the first block being linked to the
                // last-but-one block
                pSequence->pfirstBlock->prevBlock = pSequence->pfirstBlock->prevBlock->prevBlock;
                pSequence->pfirstBlock->prevBlock->pnextBlock = pSequence->pfirstBlock;
                free(paux);
                pSequence->sizeOfSequence--;
                inserted--;
            }
        }
        blockAux = blockAux->pnextBlock;    // next block of the hand
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

/**
 * Function responsible for storing all eligible sequences generated in a structure
 * -> Converts the sequence passed to string before storing it
 * -> Stores on the allSequences structure the converted sequences (Insertion at the head)
 *
 * @param allSequences Structure that stores all the generated sequences
 * @param pSequence Sequence to be converted and stored
 */
void saveSequence(ALLSEQUENCES *allSequences, SEQUENCE pSequence) {
    STRINGSEQ *newSequence = (STRINGSEQ*)malloc(sizeof(STRINGSEQ));
    newSequence->sizeOfSequence = pSequence.sizeOfSequence;
    BLOCK *blockAux = pSequence.pfirstBlock;
    int i;
    // creates space for all the values existing in the sequence
    // the size of the sequence is the ammount of blocks, so the size needed is the double, for each value, each block has 2 values
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
    newSequence->idSequence = allSequences->numberOfSequences; // atribuir um id à sequencia usado para as funcoes de search and replace
}


/// KMP Substring Search Algorithm

/**
 * Responsible for the pre-processing of the dfa matrix used to determine for wich state of the algorithm the function goes
 * according to the pattern
 * @param pat is the pattern to be searched
 * @param dfa is the matrix where will be stored the algorithm way of determining the states to give
 */
void preKMP(char *pat, int dfa[][MAX28])
{
    int X,c,j,i, M = strlen(pat);
    // reset DFA matrix to zeros
    for (i = 0; i < R; i++)
    {
        for (j = 0; j < M; j++)
        {
            dfa[i][j]=0;
        }
    }
    // build DFA from a pattern with length M
    dfa[pat[0]-(int)'0'][0] = 1;
    for (X = 0, j = 1; j < M; j++) {
        for (c = 0; c < R; c++){
            dfa[c][j] = dfa[c][X];     // Copy mismatch cases
        }
        dfa[pat[j]-(int)'0'][j] = j+1; // Set match case
        X = dfa[pat[j]-(int)'0'][X];   // Update restart state
    }
}

/**
 * KMP algorithm using the pre-processement explained before
 * runs the DFA matrix according to the position of the pattern where it is, depending on the character and on the text position where it is
 * it will change the state (storing it in the "j" variable) until the pattern is completely scanned or the text is over
 * if the pattern is found in the text, when the cycle ends, j will be equal to the length of the pattern therefore, matching
 * @param text is the text where the pattern will be searched
 * @param pat is the pattern to find
 * @param print is a variable to determine if it's supposed to print the infos about the match found or not
 * @return returns the index of the first character where the pattern was found in the text / sequence, or -1 if not found
 */
int KMP(STRINGSEQ text, char *pat, int print)
{
    int N = strlen(text.sequence);
    int M = strlen(pat);
    int dfa[R][MAX28];
    preKMP(pat, dfa);
    int i, j;
    for (i = 0, j = 0; i < N && j < M; i++){
        j = dfa[text.sequence[i]-(int)'0'][j];
    }
    if (j == M){
        if(print){
            printSequenceMatch(text, (i-M), M, 1); // the number 1 is to ask the function to print the sequence id
            printf(" - Found at position: %d (cost: %d)\n", (i - M), i);
        }
        return (i - M);
    }else {
        return -1;
    }
}

/**
 * Function that uses binary search to find the first sequence of a given size
 * @param allSequences is the structure that stores all the sequences generated
 * @param size is the wished size
 * @param costModel will count the cost of this type of search to find the sequence
 * @return returns the sequence
 */
STRINGSEQ *findSequenceOfSize(ALLSEQUENCES allSequences, int size, unsigned long *costModel){
    STRINGSEQ *sequenceAux = allSequences.pfirstSequence;
    *costModel = 0;
    unsigned long lo = 0, hi = allSequences.numberOfSequences-1;
    if(size <= 0) return NULL;
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

/**
 * Searches in all the sequences the one with the given ID
 * @param allSequences is the structure that stores all the sequences generated
 * @param sequenceId is the id of the sequence wanted
 * @return returns that sequence
 */
STRINGSEQ *getSequenceOfId(ALLSEQUENCES allSequences, ID sequenceId){
    STRINGSEQ *sequenceAux = allSequences.pfirstSequence;
    while(sequenceAux != NULL){
        if(sequenceAux->idSequence == sequenceId.sequenceId){
            return sequenceAux;
        }
        sequenceAux = sequenceAux->pnextStringSeq;
    }
    return NULL;
}

/**
 * Using the help of other functions, this one will store in the GAME structure all the blocks available for the user to choose
 * to create a pattern
 * @param availableBlocks is the structure where will be stored the available blocks
 * @param allSequences is the structure that stores all the sequences generated
 * @param sizeOfPattern is the size of the pattern to choose
 */
void getAvailableBlocks(GAME *availableBlocks, ALLSEQUENCES allSequences, int sizeOfPattern){
    unsigned long test = 0;
    STRINGSEQ *firstSeq = findSequenceOfSize(allSequences, sizeOfPattern, &test); // first sequence of size
    if(!getSequencesOfSize(availableBlocks, *firstSeq, sizeOfPattern)){
        // returning availableBlocks empty will mean that there's only one sequence available (explained in getSequencesOfSize function)
        availableBlocks->availableBlocks = 0;
        availableBlocks->pfirstBlock = NULL;
        printf("\nThere's only one sequence with that size what means that is the only pattern possible\n");
        printf("Sequence: ");
        int blockStringLen = strlen(firstSeq->sequence), i;
        for (i = 0; i < blockStringLen; i++) {
            if(i%2 == 0){
                printf("[");
                printf("%c,", *(firstSeq->sequence + i));
            }
            if((i+1)%2 == 0){
                printf("%c", *(firstSeq->sequence + i));
                printf("]");
            }
        }
        printf("\n\n");
    }
}

/**
 * Starting at the first sequence of a given size already discovered, this function will get all the other sequences of the same size
 * @param availableBlocks is the structure where will be stored the available blocks
 * @param firstSequence is the first sequence of the given size
 * @param size is the size wanted
 * @return returns 0 if there's only one sequence of the given size, there's only one way of making the pattern and doesn't make sense to ask for it
 */
int getSequencesOfSize(GAME *availableBlocks, STRINGSEQ firstSequence, int size){
    STRINGSEQ *sequenceAux = &firstSequence;
    int sequenceLen = 0, i;
    unsigned long count = 0;
    while(sequenceAux != NULL && sequenceAux->sizeOfSequence == size){
        sequenceLen = strlen(sequenceAux->sequence);
        for (i = 1; i < sequenceLen; i += 2) { // iterates 2 by 2 corresponding to a block -> 2 values
            BLOCK *blockAux = (BLOCK*)malloc(sizeof(BLOCK));
            blockAux->leftSide  = *(sequenceAux->sequence + (i-1)) - '0'; // turns the character into the correspondent integer
            blockAux->rightSide = *(sequenceAux->sequence + i) - '0';
            // checking if the block is already present in the linked list
            if(blockIsPresent(*availableBlocks, *blockAux)){ // the block already exists so it's ignored
                free(blockAux);
                continue;
            }
            blockAux->prevBlock = NULL; // no need for a doubly linked list in this case
            if(availableBlocks->pfirstBlock == NULL){
                blockAux->pnextBlock = NULL;
            }else{
                blockAux->pnextBlock = availableBlocks->pfirstBlock;
            }
            availableBlocks->pfirstBlock = blockAux;
            availableBlocks->availableBlocks += 1;
        }
        count += 1;
        sequenceAux = sequenceAux->pnextStringSeq;
    }
    if(count == 1){
        return 0;
    }
    return 1;
}

/**
 * Function that handles the creation of the replacement pattern incluiding all the limitations needed to avoid any errors
 * incluiding repetitions and inconsistencies
 * @param allSequences is the structure that stores all the sequences generated
 * @param sequenceIds is the structure holding the ids of the sequences matching the pattern to be replaced
 * @param pattern is the pattern to be replaced
 * @param replace is the pattern to replace
 */
void replacePattern(ALLSEQUENCES *allSequences, IDS *sequenceIds, char *pattern, char *replace){
    STRINGSEQ *strSequenceAux = NULL;
    ID *idAux = sequenceIds->firstId, *delId = NULL;
    int index, i, sequenceLength, len;
    int patternLength = strlen(pattern);
    int replaceLength = strlen(replace);
    char *newSequence;
    while (idAux != NULL) {
        len = 0; // resets at each sequence
        strSequenceAux = getSequenceOfId(*allSequences, *idAux);
        sequenceLength = strSequenceAux->sizeOfSequence*2;
        newSequence = (char*)malloc(sizeof(char) * (replaceLength+(sequenceLength-patternLength))); // size of the new sequence removing the old pattern and inserting the new one
        index = KMP(*strSequenceAux, pattern, 0);
        printf("\nOld Sequence ");
        printSequenceMatch(*strSequenceAux, index, patternLength, 0); // the number 0 is to ask the function to NOT print the sequence id
        // sequence until the pattern position
        for (i = 1; i < index; i+=2) {
            *(newSequence + len++) = (*(strSequenceAux->sequence + (i-1)));
            *(newSequence + len++) = (*(strSequenceAux->sequence + i));
        }
        // insert the new pattern
        for (i = 0; i < replaceLength; i++) {
            *(newSequence + len++) = (*(replace + i));
        }
        // sequence after the pattern ends
        for (i = (index+patternLength+1); i < sequenceLength; i+=2) {
            *(newSequence + len++) = (*(strSequenceAux->sequence + (i-1)));
            *(newSequence + len++) = (*(strSequenceAux->sequence + i));
        }
        *(newSequence + len) = '\0';
        strSequenceAux->sequence = createDynamicString(newSequence);
        strSequenceAux->sizeOfSequence = len / 2;
        printf("\nNew Sequence ");
        printSequenceMatch(*strSequenceAux, index, replaceLength, 0);
        printf("\n----------------------------");
        free(newSequence); // space allocated before only fits the current sequence
        delId = idAux;
        idAux = idAux->nextId;
        free(delId); // frees each id because they are no longer needed
    }
    free(sequenceIds);
}

/***
 * Function responsible for sorting the allSequences in descending order of the size of each sequences
 * -> merge sort algorithm is used for this sorting
 * @param allSequences is the structure that stores all the sequences to be sorted
 */
void sortAllSequences(ALLSEQUENCES *allSequences) {
    unsigned long cost = 0;
    mergeSort(&allSequences->pfirstSequence, &cost);
    printf("cost: %ld\n", cost);
}

/**
* Function responsible for sorting all the sequences
* Sequences are sorted by its size and it's length, in descending order
* @param headRef structure that has all the sequences to be sorted
* @param costModel variable used to know the cost of this function
*/
/* sorts the linked list by changing pnextSequence pointers (not sizeOfSequence) */
void mergeSort(STRINGSEQ * *headRef, unsigned long *costModel)
{
    *costModel += 1;
    STRINGSEQ *head = *headRef;
    STRINGSEQ *a = NULL;
    STRINGSEQ *b = NULL;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->pnextStringSeq == NULL))
    {
        return;
    }
    /* Split head into 'a' and 'b' sublists */
    frontBackSplit(head, &a, &b);
    /* Recursively sort the sublists */
    mergeSort(&a, costModel);
    mergeSort(&b, costModel);
    /* answer = merge the two sorted lists together */
    *headRef = sortedMerge(a, b, costModel);
}

/***
 * Funcao responsavel por ordenar os indices (tamanho de cada sequencia). As sequencias são ordenadas a partir do seu tamanho.
 * Ordena e faz merge com a proxima menor. Se a proxima tiver o mesmo valor da atual o algoritmo tem um critério de selecao de qual escolher.
 * Escolhe o que tiver a string da sequencia maior, isto é, fica ordenado por tamanho de sequencia e ainda ordenado por sequencias.
 *
 * @param a Valor a ser ordenado, da lista a
 * @param b Valor a ser ordenado, da lista b
 * @param costModel Variavel usada para saber o custo da funcao sortedMerge()
 * @return STRINGSEQ ordenado e com merge (entre a lista a e b)
 */
//STRINGSEQ *sortedMerge(STRINGSEQ *a, STRINGSEQ *b, unsigned long *costModel)
//{
//    *costModel += 1;
//    STRINGSEQ *result = NULL;
//
//    /* Base cases */
//    if (a == NULL)
//        return(b);
//    else if (b==NULL)
//        return(a);
//
//    /* Pick either a or b, and recur */
////    if (a->sizeOfSequence <= b->sizeOfSequence) // ascending order
//    if (a->sizeOfSequence > b->sizeOfSequence)    // descending order
//    {
//        result = a;
//        result->pnextStringSeq = sortedMerge(a->pnextStringSeq, b, costModel);
//    }
////  criterio de selecao para eleger que uma sequencia de tamanho 4 é maior que outra de tamnho igual (se o string SEQUENCE da primeira > string SEQUENCE da segunda)
//    else if(a->sizeOfSequence == b->sizeOfSequence && strcmp(a->sequence, b->sequence) > 0)
//    {
//        result = a;
//        result->pnextStringSeq = sortedMerge(a->pnextStringSeq, b, costModel);
//
//    }
//    else
//    {
//        result = b;
//        result->pnextStringSeq = sortedMerge(a, b->pnextStringSeq, costModel);
//    }
//    return(result);
//}

/***
 * Funcao responsavel por ordenar os indices (tamanho de cada sequencia). As sequencias são ordenadas a partir do seu tamanho.
 * Ordena e faz merge com a proxima menor. Se a proxima tiver o mesmo valor da atual o algoritmo tem um critério de selecao de qual escolher.
 * Escolhe o que tiver a string da sequencia maior, isto é, fica ordenado por tamanho de sequencia e ainda ordenado por sequencias.
 *
 * @param a Valor a ser ordenado, da lista a
 * @param b Valor a ser ordenado, da lista b
 * @param costModel Variavel usada para saber o custo da funcao sortedMerge()
 * @return STRINGSEQ ordenado e com merge (entre a lista a e b)
 */
STRINGSEQ *sortedMerge(STRINGSEQ *a, STRINGSEQ *b, unsigned long *costModel)
{
    *costModel += 1;
    STRINGSEQ *result = NULL;

    /* point to the last result pointer */
    STRINGSEQ* *lastPtrRef = &result;

    while(1)
    {
        if (a == NULL)
        {
            *lastPtrRef = b;
            break;
        }
        else if (b==NULL)
        {
            *lastPtrRef = a;
            break;
        }
        //    if (a->sizeOfSequence <= b->sizeOfSequence) // ascending order
        if (a->sizeOfSequence > b->sizeOfSequence)    // descending order
        {
            moveNode(lastPtrRef, &a);
        }
//      criterio de selecao para eleger que uma sequencia de tamanho 4 é maior que outra de tamnho igual (se o string SEQUENCE da primeira > string SEQUENCE da segunda)
        else if(a->sizeOfSequence == b->sizeOfSequence && strcmp(a->sequence, b->sequence) > 0)
        {
            moveNode(lastPtrRef, &a);
        }
        else
        {
            moveNode(lastPtrRef, &b);
        }

        /* tricky: advance to point to the next ".pnextStringSeq" field */
        lastPtrRef = &((*lastPtrRef)->pnextStringSeq);
    }
    return(result);
}



/***
 * Divide as sequencias da lista de sequencias em duas metades (frente e tras) e retorna duas listas atras de parametros
 * If the length is odd, the extra sequence2 should go in the front list.
 * Uses the fast/slow pointer strategy.
 * @param source lista com todas as sequencias
 * @param frontRef lista a do merge: primeira metade da lista original
 * @param backRef lista b do merge: ultima metade da lista original
 */
void frontBackSplit(STRINGSEQ *source, STRINGSEQ* *frontRef, STRINGSEQ* *backRef)
{
    STRINGSEQ *fast = NULL;
    STRINGSEQ *slow = NULL;
    if (source==NULL || source->pnextStringSeq==NULL)
    {
        /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->pnextStringSeq;


//        fast: avanca o dobro do que avanca o slow, desta forma quando fast chegar a null (fim), slow está na metade
//        ao estar na metade consegue-se dividir entre a lista da frente (lista a) e a lista de tras (lista b)
        while (fast != NULL)
        {
            fast = fast->pnextStringSeq;
            if (fast != NULL)
            {
                slow = slow->pnextStringSeq;
                fast = fast->pnextStringSeq;
            }
        }

        /* 'slow' is before the midpoint in the list, so split it in two at that point. */
        *frontRef = source; // lista da frente(lista a) fica com a primeira metade dos valores da lista source
        *backRef = slow->pnextStringSeq; // lista de tras (lista b) fica com a segunda metade dos valores da lista source
        slow->pnextStringSeq = NULL; // curte para limite da lista a
    }
}



/***
 * Funcao responsavel por mover o endereço da parte frontal da fonte(sourceRef) para a frente do destino(destRef)
 * Before calling MoveNode():
 *  source == {1, 2, 3}
 *  dest == {1, 2, 3}
 *
 *  Affter calling MoveNode():
 *  source == {2, 3}
 *  dest == {1, 1, 2, 3}
 *
 * @param destRef Endereço da sequencia de destino
 * @param sourceRef Endereço da sequencia de origem
 */
void moveNode(STRINGSEQ **destRef, STRINGSEQ **sourceRef)
{
    /* the front source node  */
    STRINGSEQ* newSeq = *sourceRef;

    /* Advance the source pointer */
    *sourceRef = newSeq->pnextStringSeq;

    /* Link the old dest off the newSeq */
    newSeq->pnextStringSeq = *destRef;

    /* Move dest to point to the newSeq */
    *destRef = newSeq;
}



/***
 * Checks if a block is consistent with the last placed block on the sequence
 * @param pSequence Sequencia que contem as peças
 * @param newBlock peça a ser testada com a ultima peça inserida na sequencia
 * @param inserted Numero de paças inseridas
 * @return 0 if block is not consistent or 1 if block is consistent
 */
int isConsistent(SEQUENCE *pSequence, BLOCK *newBlock, int inserted) {
    // first block is always consistent
    if (inserted == 0) {
        return 1;
    }
        // if the left side of the block to insert is equal to the right side of the last block
    else if (newBlock->leftSide == pSequence->pfirstBlock->prevBlock->rightSide) {
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


/***
 * Inverts a block
 * @param pBlock is the block to be inverted
 */
void invertBlock(BLOCK *pBlock) {
    int aux = 0;
    aux = pBlock->leftSide;
    pBlock->leftSide = pBlock->rightSide;
    pBlock->rightSide = aux;
}

/***
 * Inverts a block on sequence
 * -> Only used when its the first block
 * @param pSequence Sequencia que contem o bloco a ser invertido
 */
void invertBlockSequence(SEQUENCE *pSequence) {
    int aux = 0;
    aux = pSequence->pfirstBlock->leftSide;
    pSequence->pfirstBlock->leftSide = pSequence->pfirstBlock->rightSide;
    pSequence->pfirstBlock->rightSide = aux;
}




void printSequence(SEQUENCE sequence){
    BLOCK *blockAux = sequence.pfirstBlock;
    int i;
    for (i = 0; i < sequence.sizeOfSequence && blockAux != NULL; i++) {
        printf("[%d, %d] ", blockAux->leftSide, blockAux->rightSide);
        blockAux = blockAux->pnextBlock;
    }
    printf("\n");
}

