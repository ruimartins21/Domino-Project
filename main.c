/// @file main.c
/// @brief Main file of the project that contains the flux of all the functions implemented
/// @copyright

#include "libs/utils.h"
#include "libs/interface.h"
#include "libs/core.h"
#include "libs/files.h"
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <sys/stat.h> // library for the mkdir for Mac
#include <io.h> // library for the mkdir for Windows

/**
 * Project main function
 * where all the flow of the program will be managed
 * @param argc counter of the arguments passed when calling the program executable
 * @param argv array of the arguments passed
 * @return returns 0 when the program is finished successfully
 */
int main(int argc, char *argv[])
{
    int choice, path = 0, typeOfFile = 0, edited = 0, size = 0;
    unsigned long cost = 0, costOfGenerate = 0, count = 0;
    int validated = 0, maxSize = 0; // variables needed for more than one hand conditions commented below because it's not yet working
    srand((unsigned) time(NULL));
    char fileName[40], filePath[40] = "data/", *pattern, *replace;

    GAME game = {0, NULL};
    HANDS hands = {0, 0, NULL};
    SEQUENCE sequence = {0, NULL};
    ALLSEQUENCES allSequences = {0, NULL};

    // First iteration of the menu is for the user to choose between starting a new game or loading a saved game from a file
    choice = printMenu(0);
    if(choice == 1) {
        path += 1; // iterates in the menu
        // Second iteration of the menu asks for the number of hands the users wants the program to use
        hands.numberOfHands = printMenu(path);
        path += 1;
        // The third iteration is to choose a game made randomly or manually (where the user chooses the number of blocks on each hand)
        choice = printMenu(path);
        path += 1;
        // Generate the game structure
        getGame(&game);
        if (choice == 1) {
            // Generate the hands by calculating the maximum amount of blocks possible on each hand
            hands.handSize = MAX28 / hands.numberOfHands;
            // Defining a max number of blocks per hand (7 is default, and depending on the number of hands it can be less)
            if (hands.handSize > 7) {
                hands.handSize = 7;
            }
            generateRandomHand(&game, &hands);
        } else if (choice == 2) {
            // asks the user for the number of blocks each hand will have
            while (!validated) {
                hands.handSize = printMenu(path);
                // distribute the number of blocks chosen by the number of hands and it can't exceed 28 (total blocks existing)
                // all hands have the same number of blocks
                if (hands.numberOfHands * hands.handSize > 28) {
                    // tells the user what is the max size each hand can have depending on how many hands he chose before
                    maxSize = 28 / hands.numberOfHands;
                    printf("!!! Size too large! To use %d hands each one can have %d blocks maximum. !!!\n",
                           hands.numberOfHands, maxSize);
                } else {
                    validated = 1;
                }
            }
            path += 1;
            // asks the user if he wants to choose the blocks for each hand randomly or manually
            choice = printMenu(path);
            if (choice == 1) {
                // choose the blocks randomly
                generateRandomHand(&game, &hands);
            } else {
                // choose the blocks manually
                generateManualHand(&game, &hands);
            }
        }
    }else if(choice == 2){
        // load a game from file
        path = 5;
//        mkdir("data/"); // creates the folder if it doesn't yet exists on Windows
//        mkdir("data/",0777); // creates the folder if it doesn't yet exists on MAC
        printf("\nFiles existing (.txt):\n");
        system("dir/b data\\*.txt"); // scans all files with the extension "txt" in the root of the folder where the program executable is and prints them
        printf("\nFiles existing (.bin):\n");
        system("dir/b data\\*.bin"); // scans all files with the extension "bin" in the root of the folder where the program executable is and prints them
        typeOfFile = printMenu(path); // choose between text file or binary file
        while(fileExists(filePath) != 1){
            strcpy(filePath, "data/"); // restores the string to its original string after some concatenation that might have occurred inside the loop
            printf("\nFile name: ");
            scanf("%s", fileName);
            if(typeOfFile == 1){
                checkExtension(fileName, ".txt");
            }else{
                checkExtension(fileName, ".bin");
            }
            strcat(filePath, fileName);
        }
        if(fileExists(filePath)) {
            openFile(fileName, typeOfFile, &hands, &game);
        }
    }
    // if the game has no blocks, it's not possible to edit
    if(game.availableBlocks > 0){
        // Editing part: shows the user all the hands made before and asks if he wants to change anything
        edited = editHands(&hands, &game);
    }
    if(!edited && path == 5) {
        // if the user loaded the game from a file and didn't edit that data, it will skip this next step that is to save the data in a file
    }else {
        if(path == 5){ // loaded the game from file and edited? then edit the existing file
            editFile(fileName, typeOfFile, hands, game);
        }else{ // if it enter here, the game wasn't loaded from a file so asks the user if he wants to save the game
            path = 6;
            choice = printMenu(path);
            // if the user chose to save the game in a file
            if (choice) {
                path += 1;
                typeOfFile = printMenu(path);
                createGameFile(typeOfFile, hands, game);
            }
        }
    }
    // at this point the game is ready to be played so we move on to generating the sequences and sorting them
    long long time_usec_init;
    long long time_usec_end;
    long elapsed_time;
    gettimeuseconds(&time_usec_init); // init time
    generateSequence(&hands, &sequence, &allSequences, 0, &count, 0, &costOfGenerate);
    sortAllSequences(&allSequences);
    gettimeuseconds(&time_usec_end); // end time
    elapsed_time = (long) (time_usec_end - time_usec_init);
    printf("\t\t\t\t#  SEQUENCES GENERATED SUCCESSFULLY  #\n\n");
    printf("Some statistics about the game generated:\n");
    printf("Elapsed time (usec) = %ld\n",elapsed_time);
    printf("Elapsed time (sec) = %lf \n",(elapsed_time * pow(10, -6)));
    printf("Number of completed sequences (using all the blocks): %ld\n", count);
    printf("Number of saved sequences: %ld\n", allSequences.numberOfSequences);
    saveSequencesInFile(allSequences);
    path = 8;
    choice = -1;
    while(choice != 0){ // runs the menu until the user wants to exit
        choice = printMenu(path);
        STRINGSEQ *sequenceAux;
        if(choice == 1) {
            printf("\n# The biggest sequence generated was:\n");
            printSequences(allSequences, 1);
        }else if(choice == 2){
            printf("\nSize of the sequences to see: ");
            scanf("%d", &size);
            sequenceAux = findSequenceOfSize(allSequences, size, &cost);
            if(sequenceAux != NULL){
                printf("\nSequences of size %d: ", size);
                printf("(Cost of finding the first sequence: %ld)\n", cost);
                printSequenceOfSize(*sequenceAux, size);
            }else{
                printf("No sequences found with that size\n");
            }
        }else if(choice == 3){
            printf("\n# All sequences generated:\n");
            printSequences(allSequences, 0);
            printf("Number of completed sequences (using all the blocks): %ld\n", count);
            printf("Number of saved sequences: %ld\n", allSequences.numberOfSequences);
        }else if(choice == 4 || choice == 5){ // search a pattern
            int maxSequenceSize = allSequences.pfirstSequence->sizeOfSequence; // size of the biggest sequence (in an ordered list by descending order it's the 1st sequence)
            printf("\nSelect the pattern to replace:");
            pattern = createPattern(allSequences, maxSequenceSize);
            if(strlen(pattern) > 0) {
                IDS sequenceIds = {NULL};
                unsigned long numberOfMatches = 0;
                findPatternInSequences(allSequences, pattern, &sequenceIds, &numberOfMatches);
                if(numberOfMatches != 0) {
                    if (choice == 5) { // Replace the chosen pattern in the sequences where it's consistent with the rest of the sequence
                        while (choice < 1 || choice > 2) {
                            printf("\n1 - Replace the pattern in a single sequence");
                            printf("\n2 - Replace the pattern in all the listed sequences\nChoice: ");
                            scanf("%d", &choice);
                        }
                        unsigned long sequenceId = 0;
                        if (choice == 1) {
                            printf("\nID of the sequence: ");
                            scanf("%ld", &sequenceId);
                            while (!checkId(&sequenceIds, sequenceId)) {
                                printf("\nID of the sequence: ");
                                scanf("%ld", &sequenceId);
                            }
                        }
                        printf("\nSelect the replacement pattern:");
                        // choose the pattern to replace the previous pattern chosen
                        replace = createReplacePattern(allSequences, sequenceIds, pattern);
                        if(strlen(replace) > 0){
                            replacePattern(&allSequences, &sequenceIds, pattern, replace);
                        }
                    }
                }
            }
        }
    }
    return 0;
}