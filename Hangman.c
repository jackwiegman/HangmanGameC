/*
 * @file
 * @brief Play a hangman game with the user.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE sizeof(char)      /** Size of char on the computer running the program */
#define INT_SIZE sizeof(int)        /** Size of an int on the computer running the program */
#define MAX_HANGMAN_STRING_SIZE 100 /** Max string size to be entered by the player */
#define MAX_ERRORS 7                /** Max error before player loses */

/**
 * @brief Array holding pictures of a hangman at various stages to display.
 */
const char *HANGMANPICS[(MAX_ERRORS)] = {"\
  +---+ \n\
  |   | \n\
      | \n\
      | \n\
      | \n\
      | \n\
=========", "\
  +---+ \n\
  |   | \n\
  O   | \n\
      | \n\
      | \n\
      | \n\
=========", "\
  +---+ \n\
  |   | \n\
  O   | \n\
  |   | \n\
      | \n\
      | \n\
=========", "\
  +---+ \n\
  |   | \n\
  O   | \n\
 /|   | \n\
      | \n\
      | \n\
=========", "\
  +---+ \n\
  |   | \n\
  O   | \n\
 /|\\  | \n\
      | \n\
      | \n\
=========", "\
  +---+ \n\
  |   | \n\
  O   | \n\
 /|\\  | \n\
 /    | \n\
      | \n\
=========", "\
  +---+ \n\
  |   | \n\
  O   |   \n\
 /|\\  |   \n\
 / \\  |  \n\
      |  \n\
========= "};

void printCurrentBoard(char *currentBoard, int size) {

    for (int i = 0; i < size; i++) {
    }
}

int main(int argc, char *argv[]) {

    // char wordsList = strtok(char *, const char *);

    // Word bank of animals

    /**
     * @brief List of possible words to choose from, separated by spaces
     */
    char *FullWordList =
        "ant baboon badger bat bear beaver camel cat clam cobra cougar coyote crow deer dog donkey "
        "duck eagle ferret fox frog goat goose hawk lion lizard llama mole monkey moose mouse mule "
        "newt otter owl panda parrot pigeon python rabbit ram rat raven rhino salmon seal shark "
        "sheep skunk sloth snake spider stork swan tiger toad trout turkey turtle weasel whale "
        "wolf wombat zebra ";

    char *wordList, *secretWord, *currentBoard;

    int size = (sizeof(&currentBoard)) / CHAR_SIZE;

    for (int i = 0; i < MAX_ERRORS; i++) {
        printf("%s\n", HANGMANPICS[i]);
    }

    // for (int i = 0; i <)

    // wordList[numWords] = {"dog", "cat", "wolf", "bear", "tiger", "cheetah", "elephant"};

    printCurrentBoard(currentBoard, size);

    printf("Size of char: ");

    return EXIT_SUCCESS;
}
