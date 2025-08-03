/*
 * @file
 * @brief Play a hangman game with the user.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define EXIT_SUCCESS 1
#define EXIT_FAIL 
#define CHAR_SIZE sizeof(char)
#define INT_SIZE sizeof(int)
#define MAX_HANGMAN_STRING_SIZE 100
#define MAX_ERRORS 7

void printCurrentBoard(char *currentBoard, int size) {

  for (int i = 0; i < size; i++) {
  }
}

int main(int argc, char *argv[]) {

const char * HANGMANPICS[(MAX_ERRORS)] = {
"\
  +---+ \
  |   | \
      | \
      | \
      | \
      | \
=========", 

 "\
  +---+ \
  |   | \
  O   | \
      | \
      | \
      | \
=========",
   "\
  +---+ \
  |   | \
  O   | \
  |   | \
      | \
      | \
=========",
 "\
  +---+ \
  |   | \
  O   | \
 /|   | \
      | \
      | \
=========", 
 "\
  +---+ \
  |   | \
  O   | \
 /|\  | \
      | \
      | \
=========", 
 "\
  +---+ \
  |   | \
  O   | \
 /|\  | \
 /    | \
      | \
=========",

 "\
  +---+ \
  |   | \
  O   |   \
 /|\\  |   \
 / \\  |  \
      |  \
========= "
  wordsList = strtok(char *, const char *);


  // Word bank of animals
  char * FullWordList = "ant baboon badger bat bear beaver camel cat clam cobra cougar \
         coyote crow deer dog donkey duck eagle ferret fox frog goat \
         goose hawk lion lizard llama mole monkey moose mouse mule newt \
         otter owl panda parrot pigeon python rabbit ram rat raven \
         rhino salmon seal shark sheep skunk sloth snake spider \
         stork swan tiger toad trout turkey turtle weasel whale wolf \
         wombat zebra ";

  char *wordList, *secretWord, *currentBoard;

  int size = (sizeof(&currentBoard)) / CHAR_SIZE;

  for (int i = 0; i < )

  wordList = {"dog", "cat", "wolf", "bear", "tiger", "cheetah", "elephant"};

  printCurrentBoard(char *currentBoard, size);

  printf("Size of char: ");
  

  return EXIT_SUCCESS;
}

/*
 * HANGMANPICS = ["
 *  +---+
 *  |   |
 *      |
 *      |
 *      |
 *      |
 *=========", "
 *  +---+
 *  |   |
 *  O   |
 *      |
 *      |
 *      |
 *=========", "
 *  +---+
 *  |   |
 *  O   |
 *  |   |
 *      |
 *      |
 *=========", "
 *  +---+
 *  |   |
 *  O   |
 * /|   |
 *      |
 *      |
 *=========", "
 *  +---+
 *  |   |
 *  O   |
 * /|\  |
 *      |
 *      |
 *=========", "
 *  +---+
 *  |   |
 *  O   |
 * /|\  |
 * /    |
 *      |
 *=========", "
 *  +---+
 *  |   |
 *  O   |
 * /|\  |
 * / \  |
 *      |
 *========="]
 *
 *#Word bank of animals
 *words = ('ant baboon badger bat bear beaver camel cat clam cobra cougar '
 *         'coyote crow deer dog donkey duck eagle ferret fox frog goat '
 *         'goose hawk lion lizard llama mole monkey moose mouse mule newt '
 *         'otter owl panda parrot pigeon python rabbit ram rat raven '
 *         'rhino salmon seal shark sheep skunk sloth snake spider '
 *         'stork swan tiger toad trout turkey turtle weasel whale wolf '
 *         'wombat zebra ').split()
 */
