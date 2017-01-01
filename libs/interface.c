/// @file interface.c
/// @brief Gathers all the functions that interact with the user
/// @copyright

#include "interface.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Prints the multiple menus that are needed
 * @param path tells the function at wich part of the menu it is
 * @return returns the choice of the user
 */
int printMenu(int path) {
    int choiceMade = 0;
    switch (path) {
        case 0:
            printf("\n\t\t\t\t# # # # # # # # # #\n");
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
            printf("\n\t\t\t\t# # # # # # # # # #\n");
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
            printf("\n\t\t\t\t# # # # # # # # # #\n");
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
            printf("\n\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tNumber of blocks on each hand: ");
            scanf("%d", &choiceMade);
            return choiceMade;

        case 4:
            printf("\n\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - Choose the blocks randomly\n");
            printf("\t\t\t\t2 - Choose the blocks manually\n");
            scanf("%d", &choiceMade);
            return choiceMade;

        case 5:
            printf("\n\t\t\t\t# # # # # # # # # #\n");
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
            printf("\n\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\tSave game data in a file? (Y/N): ");
            getchar(); // avoids empty symbols like previous enters
            choiceMade = getchar(); // gets the character needed to answer by its ASCII code
            if (choiceMade != 'Y' && choiceMade != 'y' && choiceMade != 'N' && choiceMade != 'n') {
                printf("!!! Invalid answer !!!\n");
                return printMenu(path);
            } else {
                if (choiceMade == 'Y' || choiceMade == 'y') return 1;
                return 0;
            }

        case 7:
            printf("\n\t\t\t\t# # # # # # # # # #\n");
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
            printf("\n\t\t\t\t# # # # # # # # # #\n");
            printf("\t\t\t\t#     M E N U     #\n");
            printf("\t\t\t\t# # # # # # # # # #\n\n");
            printf("\t\t\t\t1 - See the biggest sequence\n");
            printf("\t\t\t\t2 - See the sequences of a certain size\n");
            printf("\t\t\t\t3 - See all the sequences\n");
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
 * Shows the user all the blocks that are available to choose (this prevents out of bounds selections from the user)
 * @param game is the structure that holds all the blocks not being used by any hands
 * @return returns the counter of blocks available to choose from for further conditioning from the user inputs
 */
int blocksAvailable(GAME game) {
    int i = 0;
    BLOCK *blockAux = game.pfirstBlock;
    printf("\n\t\t\t\t### Available Blocks ###\n");
    while (blockAux != NULL) {
        printf("\t#%2d = [%d|%d]", i + 1, blockAux->leftSide, blockAux->rightSide);
        // putting breaks after a certain number of blocks printed to improve the visualization
        if ((i + 1) % 5 == 0 && i != 0) {
            printf("\n");
        }
        i++;
        blockAux = blockAux->pnextBlock;
    }
    return i;
}

/**
 * The user chooses block by block wich ones he wants in each hand
 * it's showed the available blocks for choosing.
 * After each choice the block chosen is transferred to the hand and removed from the game
 * @param game is where all the available blocks are
 * @param hands are the hands to fill with blocks
 */
void generateManualHand(GAME *game, HANDS *hands) {
    int i, j, blocksLimit, blockId;
    hands->pfirstHand = NULL;
    HAND *handAux = NULL;
    BLOCK *delBlock = NULL, *blockAux = NULL;
    for (i = 0; i < hands->numberOfHands; i++) {
        handAux = (HAND*)malloc(sizeof(HAND));
        printf("\n## %2d hand ##\n", i + 1);
        for (j = 0; j < hands->handSize; j++) {
            blocksLimit = blocksAvailable(*game);
            printf("\n%2d block: ", j + 1);
            scanf("%d", &blockId);
            if (blockId < 1 || blockId > blocksLimit) {
                printf("!!! Choose a valid number !!!");
                j--;
                continue;
            }
            blockId -= 1;
            // gets the block chosen from the game, removing it from there, and inserting it in the respective hand
            delBlock = popBlock(game, blockId);
            blockAux = transferBlock(delBlock);
            if(handAux->pfirstBlock == NULL){ // it's the first block to be inserted in the hand
                blockAux->pnextBlock = NULL; // it will be used the insertion at the head, so the first block to be inserted will be the one at the tail
            }else{
                blockAux->pnextBlock = handAux->pfirstBlock;
            }
            handAux->pfirstBlock = blockAux;
        }
        handAux->pnextHand = hands->pfirstHand;
        hands->pfirstHand = handAux;
    }
}

/**
 * This function will search a given pattern among all the sequences generated
 * At the same time, each sequence that contains the pattern, its id will be stored in a structure of ids to have access of the matched sequences
 * only at the other functions
 * The search functionality used here is based on the KMP substring search algorithm
 * @param allSequences is the structure that stores all the sequences generated
 * @param pattern is the pattern chosen to be searched
 * @param sequenceIds is the structure where it will be stored the ids of the sequences matching the patten
 * @param numberOfMatches will tell the user how many sequences matched with the pattern
 */
void findPatternInSequences(ALLSEQUENCES allSequences, char *pattern, IDS *sequenceIds, unsigned long *numberOfMatches){
    STRINGSEQ *stringSeqAux = allSequences.pfirstSequence;
    int patternLength = strlen(pattern) / 2; // number of blocks not the number of values (size of the string)
    ID *idAux;
    while(stringSeqAux != NULL && stringSeqAux->sizeOfSequence >= patternLength){ // it will only find matches if the sequence is the same size or bigger than the pattern size
        if(KMP(*stringSeqAux, pattern, 1) > -1){ // returns the index where the pattern was found in the sequence if a match was found
            idAux = (ID*)malloc(sizeof(ID));
            if(sequenceIds->firstId == NULL){
                idAux->nextId = NULL;
            }else{
                idAux->nextId = sequenceIds->firstId;
            }
            idAux->sequenceId = stringSeqAux->idSequence;
            sequenceIds->firstId = idAux;
            *numberOfMatches += 1;
        }
        stringSeqAux = stringSeqAux->pnextStringSeq;
    }
    sequenceIds->numberOfIds = *numberOfMatches;
    printf("\nNumber of matches for the pattern \"%s\": %ld\n", pattern , *numberOfMatches);
}

/**
 * Function that handles all the editing the user wishes to do on the generated hands
 * It handles the changes of blocks between the hands structure and the game structure
 * @param hands is the hands structure containing all the hands, and each one all its blocks
 * @param game is where all the unused blocks are
 * @return returns true or false that will tell the program if the user edited anything or not
 */
int editHands(HANDS *hands, GAME *game) {
    int i, j, handId = 0, removeId = 0, addId = 0, blocksLimit, edited = 0, validate = 0, choice = 'y';
    HAND *handAux = NULL;
    while (1) {
        handAux = hands->pfirstHand;
        for (i = 0; i < hands->numberOfHands && handAux != NULL; i++) {
            printf("\n#%2d = Hand %d: ", i + 1, i + 1);
            printSingleHand(*handAux, hands->handSize);
            handAux = handAux->pnextHand;
        }
        while (!validate) {
            printf("\nDo you wish to change anything before proceeding? (Y/N): ");
            getchar();
            choice = getchar();
            if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
                printf("!!! Invalid answer !!!\n");
                validate = 0;
                continue;
            }
            validate = 1;
        }
        validate = 0;
        if (choice == 'n' || choice == 'N') {
            // if the user decided to not edit, since it's inside a loop, we need to check if he edited anything before
            return edited;
        }
        handAux = hands->pfirstHand;
        if (hands->numberOfHands > 1) {
            while(handId < 1 || handId > hands->numberOfHands) {
                printf("\nEnter the id of the hand to edit: ");
                scanf("%d", &handId);
            }
            i = 1;
            while(i < handId && handAux != NULL){
                handAux = handAux->pnextHand;
                i++;
            }
        }
        if(handAux == NULL) {
            printf("!!! Invalid choice !!!\n");
            validate = 0;
            continue;
        }
        BLOCK *blockAux = handAux->pfirstBlock;
        for (i = 0, j = handId; i < hands->handSize; i++, j++) {
            printf(" #%2d = [%d|%d]", i + 1, blockAux->leftSide, blockAux->rightSide);
            blockAux = blockAux->pnextBlock;
        }
        while(removeId < 1 || removeId > hands->handSize){
            printf("\nWhich block do you want to change? ");
            scanf("%d", &removeId);
        }
        blockAux = handAux->pfirstBlock;
        i = 1;
        while(i < removeId && blockAux != NULL){
            blockAux = blockAux->pnextBlock;
            i++;
        }
        blocksLimit = blocksAvailable(*game);
        while (addId < 1 || addId > blocksLimit) {
            printf("\nChoose a block to insert from the available blocks above: ");
            scanf("%d", &addId);
        }
        addId -= 1;
        printf("\nindex: %d", addId);
        swapBlock(game, blockAux, addId);
        edited = 1;
        // reset variables
        addId = 0;
        handId = 0;
        removeId = 0;
    }
}

/**
 * Function that prints the allSequences structure with the proper info for the user to see
 * @param allSequences is the structure that stores all the sequences generated
 * @param size is a parameter to check if the user wants to see all the sequences or only the biggest one
 */
void printSequences(ALLSEQUENCES allSequences, int size){
    STRINGSEQ *pauxSequence = allSequences.pfirstSequence;
    int i, blockStringLen = 0;
    if(size == 1){
        // print only the biggest sequence, since it's an ordered list of sequences, the biggest is the first one
        blockStringLen = strlen(pauxSequence->sequence);
        for (i = 0; i < blockStringLen; i++) {
            if(i%2 == 0){
                printf("[");
                printf("%c,", *(pauxSequence->sequence + i));
            }
            if((i+1)%2 == 0){
                printf("%c", *(pauxSequence->sequence + i));
                printf("]");
            }
        }
        printf(" Using %d blocks\n", pauxSequence->sizeOfSequence);
    }else{
        // print all the sequences generated
        while (pauxSequence != NULL){
            blockStringLen = strlen(pauxSequence->sequence);
            for (i = 0; i < blockStringLen; i++) {
                if(i%2 == 0){
                    printf("[");
                    printf("%c,", *(pauxSequence->sequence + i));
                }
                if((i+1)%2 == 0){
                    printf("%c", *(pauxSequence->sequence + i));
                    printf("]");
                }
            }
            printf("\n");
            pauxSequence = pauxSequence->pnextStringSeq;
        }
    }
}

/**
 * Given a size it prints all the sequences of that size, starting with the one passed through parameter
 * @param sequence is the first sequence of the wished size
 * @param size is the size of the sequences to print
 */
void printSequenceOfSize(STRINGSEQ sequence, int size){
    STRINGSEQ *sequenceAux = &sequence;
    int blockStringLen, i;
    unsigned long count = 0;
    while(sequenceAux->sizeOfSequence == size){
        blockStringLen = strlen(sequenceAux->sequence);
        for (i = 0; i < blockStringLen; i++) {
            if(i%2 == 0){
                printf("[");
                printf("%c,", *(sequenceAux->sequence + i));
            }
            if((i+1)%2 == 0){
                printf("%c", *(sequenceAux->sequence + i));
                printf("]");
            }
        }
        printf("\n");
        count += 1;
        sequenceAux = sequenceAux->pnextStringSeq;
    }
    printf("\n%ld sequences found\n", count);
}

/**
 * Function that handles the creation of the pattern incluiding limitations made by existing blocks, etc
 * @param allSequences structure containing all the sequences
 * @param maxSequenceSize size of the biggest sequence (in an ordered list by descending order it's the 1st sequence)
 * @return returns the final string with the pattern chosen
 */
char *createPattern(ALLSEQUENCES allSequences, int maxSequenceSize){
    int i, sizeOfPattern = 0, blocksLimit, blockId;
    GAME availableBlocks = {0, NULL};
    BLOCK *delBlock = NULL, *blockAux = NULL;
    char *pattern = (char*)malloc( sizeof(char) * (sizeOfPattern*2) + 1 );
    *pattern = '\0'; // initialize the string as empty
    // will store all the blocks chosen in the a sequence structure to check consistency and only after that is ready to be transformed to a string
    SEQUENCE *sequenceAux = (SEQUENCE*)malloc(sizeof(SEQUENCE));
    while(sizeOfPattern < 1 || sizeOfPattern > maxSequenceSize){
        printf("\nHow many blocks will there be in the pattern? ");
        scanf("%d", &sizeOfPattern);
    }
    // with the desired size for the pattern now, to avoid problems like the user choosing some block that isn't consistent with any other
    // block present in the sequences, it's created in a structure of the type GAME a linked list of the blocks present in all the sequences generated
    // of the size of the pattern, this way it's certain that it can always be a pattern made with the given size
    getAvailableBlocks(&availableBlocks, allSequences, sizeOfPattern);
    if(availableBlocks.availableBlocks == 0){
        free(sequenceAux);
        return pattern;
    }
    sequenceAux->sizeOfSequence = sizeOfPattern;
    for (i = 0; i < sizeOfPattern; i++) {
        blocksLimit = blocksAvailable(availableBlocks);
        printf("\n\n(insert \'-1\' to return to the menu)");
        printf("\n%2d block: ", i + 1);
        scanf("%d", &blockId);
        if(blockId == -1){
            free(sequenceAux);
//            freeGame(&availableBlocks);
            return pattern;
        }
        if (blockId < 1 || blockId > blocksLimit) {
            printf("!!! Choose a valid number !!!");
            i--;
            continue;
        }
        blockId -= 1;
        delBlock = peepBlock(availableBlocks, blockId); // returns the block chosen without removing it from the game because it might not be consistent
        if (i == 0) { // if it's the first block will insert it in the sequence, no verification required
            delBlock = popBlock(&availableBlocks, blockId); // gets the block chosen from the game, removing it from the game after its content is copied
            blockAux = transferBlock(delBlock);
            blockAux->prevBlock = blockAux; // doubly linked list
            sequenceAux->pfirstBlock = blockAux;
        }else if(i == 1){ // the second block to be inserted needs a different verification, that will invert the first block if needed
            if (isConsistent(sequenceAux, delBlock, 1)){ // will check the consistency with the block inserted before
                delBlock = popBlock(&availableBlocks, blockId); // gets the block chosen from the game, removing it from the game after its content is copied
                blockAux = transferBlock(delBlock);
                blockAux->prevBlock = sequenceAux->pfirstBlock;
                sequenceAux->pfirstBlock->pnextBlock = blockAux;
                sequenceAux->pfirstBlock->prevBlock = blockAux;
            }else{
                printf("\nThe block can't be used in this place.");
                i--;
                continue;
            }
        }else{
            if (isConsistent(sequenceAux, delBlock, 2)){
                delBlock = popBlock(&availableBlocks, blockId); // gets the block chosen from the game, removing it from the game after its content is copied
                blockAux = transferBlock(delBlock);
                blockAux->prevBlock = sequenceAux->pfirstBlock->prevBlock;
                sequenceAux->pfirstBlock->prevBlock->pnextBlock = blockAux;
                sequenceAux->pfirstBlock->prevBlock = blockAux;
            }else{
                printf("\nThe block can't be used in this place.");
                i--;
                continue;
            }
        }
        printf("\nCurrent pattern: ");
        printSequence(*sequenceAux);
    }
    // creates space for all the values that the pattern will have
    // the size of the pattern is the ammount of blocks, so the size needed is the double (for each value), each block has 2 values
    // the + 1 at the end is for the end of the string: '\0'
    int patternLength = 0;
    blockAux = sequenceAux->pfirstBlock;
    for (i = 0; i < sizeOfPattern && blockAux != NULL; i++) {
        patternLength = strlen(pattern);
        *(pattern + patternLength)     = '0' + blockAux->leftSide; // turns the integer into the correspondent character
        *(pattern + (patternLength+1)) = '0' + blockAux->rightSide;
        *(pattern + (patternLength+2)) = '\0';
        delBlock = blockAux;
        blockAux = blockAux->pnextBlock;
        free(delBlock); // freeing the space used by the sequence generated as it goes through all the blocks
    }
    free(sequenceAux);
//    freeGame(&availableBlocks);
    return pattern;
}

/**
 * Function that handles the creation of the replacement pattern
 * It handles the conditions like the outer limits the pattern must have
 * According to the sequences and the pattern to replace already chosen it shows the user the blocks after a filtering
 * of the blocks that already exists in the sequence, therefore, that can't be repeated
 * Stores each block chosen in a temporary sequence structure and at the end of the function it converts all the blocks to a single string
 * @param allSequences structure containing all the sequences
 * @param sequenceIds are the ids of the sequences that matched the pattern to be replaced
 * @param pattern is the pattern chosen to be replaced
 * @return returns the final string with the replacement pattern chosen
 */

char *createReplacePattern(ALLSEQUENCES allSequences, IDS sequenceIds, char *pattern) {
    GAME availableBlocks = {0,NULL};
    getGame(&availableBlocks);
    BLOCK *blockAux = (BLOCK*)malloc(sizeof(BLOCK)), *delBlock = NULL;
    STRINGSEQ *strSequenceAux = NULL;
    ID *idAux = sequenceIds.firstId;
    int i, patternLength = strlen(pattern), sizeOfPattern = 0, blocksLeft = 0, blocksLimit = 0, blockId, index = -1;
    // runs all the ids of the linked list and for each one gets the respective sequence from where it will be taken
    // the blocks that are not from the pattern to replace to remove them from the available blocks from wich the user will
    // choose the replacement pattern
    while (idAux != NULL) {
        strSequenceAux = getSequenceOfId(allSequences, *idAux);
        index = KMP(*strSequenceAux, pattern, 0);
        for (i = 1; i < index; i+=2) {
            blockAux->leftSide = (*(strSequenceAux->sequence + (i-1))) - '0';
            blockAux->rightSide = (*(strSequenceAux->sequence + i)) - '0';
            // sends the block and the availableBlocks through a function that removes the block from the available ones
            // since it's already present in the sequence
            delBlock = removeBlock(&availableBlocks, *blockAux);
            if(delBlock != NULL){
                blocksLeft += 1;
                free(delBlock);
            }
        }
        for (i = (index+patternLength+1); i < (strSequenceAux->sizeOfSequence*2); i+=2) {
            blockAux->leftSide = (*(strSequenceAux->sequence + (i-1))) - '0';
            blockAux->rightSide = (*(strSequenceAux->sequence + i)) - '0';
            delBlock = removeBlock(&availableBlocks, *blockAux);
            if(delBlock != NULL){
                blocksLeft += 1;
                free(delBlock);
            }
        }
        blocksLimit += 1;
        idAux = idAux->nextId;
    }
    blocksLeft = 28 - blocksLeft;
    // Outer limits where the new pattern must fit
    int leftLimit  = pattern[0] - '0';
    int rightLimit = pattern[patternLength - 1] - '0';
    // condition if it is a replacement in a single sequence or in multiple ones because with one sequence only we can
    // give the user more freedom if a certain pattern is at the beginning or the end of the pattern, the user doesn't
    // need to choose a block with a certain value at the side with no more blocks attached
    if(blocksLimit == 1){ // used a variable that doesn't affect anything else, to spare the creation of a new one
        // it counts the amount of ids existing, therefore, if there's only one it means it's a replacement in a single sequence
        if(index <= 0){ // if the pattern starts at the beginning of the sequence
            leftLimit = -1;
        }
        if(index+patternLength >= (strSequenceAux->sizeOfSequence*2)){ // if the pattern ends at the end of the sequence
            rightLimit = -1;
        }
    }
    while(sizeOfPattern < 1 || sizeOfPattern >  blocksLeft){
        printf("\nHow many blocks will there be in the pattern? ");
        scanf("%d", &sizeOfPattern);
    }
    char *replace = (char*)malloc( sizeof(char) * (sizeOfPattern*2) + 1 );
    *replace = '\0'; // initialize the string as empty
    SEQUENCE *sequenceAux = (SEQUENCE*)malloc(sizeof(SEQUENCE));
    sequenceAux->sizeOfSequence = sizeOfPattern;
    for (i = 0; i < sizeOfPattern; i++) {
        printf("\nLimits: left: %d right %d\n", leftLimit, rightLimit);
        blocksLimit = blocksAvailable(availableBlocks);
        printf("\n\n(insert \'-1\' to return to the menu)");
        printf("\n%2d block: ", i + 1);
        scanf("%d", &blockId);
        if(blockId == -1){
            free(sequenceAux);
//            freeGame(&availableBlocks);
            return replace;
        }
        if (blockId < 1 || blockId > blocksLimit) {
            printf("!!! Choose a valid number !!!");
            i--;
            continue;
        }
        blockId -= 1;
        delBlock = peepBlock(availableBlocks, blockId); // returns the block chosen without removing it from the game because it might not be consistent
        if(sizeOfPattern == 1){ // replace with only one block means the block must have both limit values in case there are values
            if(leftLimit == -1){
                if(rightLimit == -1){
                    delBlock = popBlock(&availableBlocks, blockId); // gets the block chosen from the game, removing it from there after its contents are copied
                    blockAux = transferBlock(delBlock);
                    blockAux->prevBlock = blockAux; // doubly linked list
                    sequenceAux->pfirstBlock = blockAux;
                }else{
                    if(delBlock->rightSide == rightLimit){ // only right side needs to have a certain value
                        delBlock = popBlock(&availableBlocks, blockId);
                        blockAux = transferBlock(delBlock);
                        blockAux->prevBlock = blockAux;
                        sequenceAux->pfirstBlock = blockAux;
                    }else if(delBlock->leftSide == rightLimit){
                        delBlock = popBlock(&availableBlocks, blockId);
                        invertBlock(delBlock);
                        blockAux = transferBlock(delBlock);
                        blockAux->prevBlock = blockAux;
                        sequenceAux->pfirstBlock = blockAux;
                    }else{
                        printf("\nThe block can't be used in this place. The block must have a side with the value %d", rightLimit);
                        i--;
                    }
                }
                continue;
            }else if(rightLimit == -1){
                if(delBlock->leftSide == leftLimit){ // only left side needs to have a certain value
                    delBlock = popBlock(&availableBlocks, blockId);
                    blockAux = transferBlock(delBlock);
                    blockAux->prevBlock = blockAux;
                    sequenceAux->pfirstBlock = blockAux;
                }else if(delBlock->rightSide == leftLimit){
                    delBlock = popBlock(&availableBlocks, blockId);
                    invertBlock(delBlock);
                    blockAux = transferBlock(delBlock);
                    blockAux->prevBlock = blockAux;
                    sequenceAux->pfirstBlock = blockAux;
                }else{
                    printf("\nThe block can't be used in this place. The block must have a side with the value %d", leftLimit);
                    i--;
                }
                continue;
            }
        }
        if (i == 0) { // if it's the first block will verify if any of its 2 values is equal to the right value of the last inserted block on the sequence
            if(leftLimit == -1){ // if it's -1 it means there's no block on the left so there's no condition for fitting
                delBlock = popBlock(&availableBlocks, blockId); // gets the block chosen from the game, removing it from there after its contents are copied
                blockAux = transferBlock(delBlock);
                blockAux->prevBlock = blockAux; // doubly linked list
                sequenceAux->pfirstBlock = blockAux;
            }else{
                if(delBlock->leftSide == leftLimit){
                    delBlock = popBlock(&availableBlocks, blockId);
                    blockAux = transferBlock(delBlock);
                    blockAux->prevBlock = blockAux;
                    sequenceAux->pfirstBlock = blockAux;
                }else if(delBlock->rightSide == leftLimit){ // needed to invert the block
                    delBlock = popBlock(&availableBlocks, blockId);
                    invertBlock(delBlock);
                    blockAux = transferBlock(delBlock);
                    blockAux->prevBlock = blockAux;
                    sequenceAux->pfirstBlock = blockAux;
                }else{
                    printf("\nThe block can't be used in this place. The block must have a side with the value %d", leftLimit);
                    i--;
                    continue;
                }
            }
        }else if(i == (sizeOfPattern-1)){
            if(rightLimit == -1){
                if (isConsistent(sequenceAux, delBlock, 2)){
                    delBlock = popBlock(&availableBlocks, blockId);
                    blockAux = transferBlock(delBlock);
                    blockAux->prevBlock = sequenceAux->pfirstBlock->prevBlock;
                    sequenceAux->pfirstBlock->prevBlock->pnextBlock = blockAux;
                    sequenceAux->pfirstBlock->prevBlock = blockAux;
                }else{
                    printf("\nThe block can't be used in this place.");
                    i--;
                    continue;
                }
            }else {
                if (isConsistent(sequenceAux, delBlock, 2)){
                    if (delBlock->rightSide == rightLimit) { // this block can't move so the right side must fit
                        delBlock = popBlock(&availableBlocks, blockId);
                        blockAux = transferBlock(delBlock);
                        blockAux->prevBlock = sequenceAux->pfirstBlock->prevBlock;
                        sequenceAux->pfirstBlock->prevBlock->pnextBlock = blockAux;
                        sequenceAux->pfirstBlock->prevBlock = blockAux;
                    } else {
                        printf("\nThe block can't be used in this place. The block must have a side with the value %d", rightLimit);
                        i--;
                        continue;
                    }
                }else{
                    printf("\nThe block can't be used in this place.");
                    i--;
                    continue;
                }
            }
        }else{
            if (isConsistent(sequenceAux, delBlock, 2)){
                delBlock = popBlock(&availableBlocks, blockId); // gets the block chosen from the game, removing it from the game after its content is copied
                blockAux = transferBlock(delBlock);
                blockAux->prevBlock = sequenceAux->pfirstBlock->prevBlock;
                sequenceAux->pfirstBlock->prevBlock->pnextBlock = blockAux;
                sequenceAux->pfirstBlock->prevBlock = blockAux;
            }else{
                printf("\nThe block can't be used in this place.");
                i--;
                continue;
            }
        }
        printf("\nCurrent pattern: ");
        printSequence(*sequenceAux);
    }
    // creates space for all the values that the pattern will have
    // the size of the pattern is the ammount of blocks, so the size needed is the double (for each value), each block has 2 values
    // the + 1 at the end is for the end of the string: '\0'
    int replaceLength = 0;
    blockAux = sequenceAux->pfirstBlock;
    for (i = 0; i < sizeOfPattern && blockAux != NULL; i++) {
        replaceLength = strlen(replace);
        *(replace + replaceLength)     = '0' + blockAux->leftSide; // turns the integer into the correspondent character
        *(replace + (replaceLength+1)) = '0' + blockAux->rightSide;
        *(replace + (replaceLength+2)) = '\0';
        delBlock = blockAux;
        blockAux = blockAux->pnextBlock;
        free(delBlock); // freeing the space used by the sequence generated as it goes through all the blocks
    }
    free(sequenceAux);
    freeGame(&availableBlocks);
    return replace;
}

/**
 * Prints a given sequence with brackets around the pattern
 * @param text is the sequence to print
 * @param index is the index where the pattern starts
 * @param length is the length of the pattern
 * @param withId used to print the sequence id or not as needed
 */
void printSequenceMatch(STRINGSEQ text, int index, int length, int withId){
    int i,j;
    if(withId)
        printf("id %4ld: ", text.idSequence);
    for (i = 0; i < strlen(text.sequence); i++) {
        if(i == index){
            printf("[");
            for (j = i; j < (i+length); j++) {
                printf("%c", *(text.sequence + j));
            }
            i = j-1;
            printf("]");
        }else{
            printf("%c", *(text.sequence + i));
        }
    }
}

/**
 * Prints a certain sequence
 * @param sequence is the sequence to be printed
 */
void printSequence(SEQUENCE sequence){
    BLOCK *blockAux = sequence.pfirstBlock;
    int i;
    for (i = 0; i < sequence.sizeOfSequence && blockAux != NULL; i++) {
        printf("[%d, %d] ", blockAux->leftSide, blockAux->rightSide);
        blockAux = blockAux->pnextBlock;
    }
    printf("\n");
}