/*
 * @file
 * @brief Play a hangman game with the user.
 */

#include <endian.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHAR_SIZE sizeof(char)      /** Size of char on the computer running the program */
#define INT_SIZE sizeof(int)        /** Size of an int on the computer running the program */
#define MAX_HANGMAN_STRING_SIZE 100 /** Max string size to be entered by the player */
#define MAX_ERRORS 6                /** Max error before player loses */
#define MAX_GUESSED_LETTERS 26      /** Max size of array to hold the guessed letters */

const char *MASKED_CHAR_VALUE = "_";
/**
 * @var const char * HANGMANPICS
 * Array holding pictures of a hangman at various stages to display.
 */
const char *HANGMANPICS[(MAX_ERRORS + 1)] = {"\
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

/**
 * @var const char * FullWordList
 * List of possible words to choose from, separated by spaces.
 */
const char *FullWordList =
    "ant baboon badger bat bear beaver camel cat clam cobra cougar coyote crow deer dog donkey \
    duck eagle ferret fox frog goat goose hawk lion lizard llama mole monkey moose mouse mule \
    newt otter owl panda parrot pigeon python rabbit ram rat raven rhino salmon seal shark \
    sheep skunk sloth snake spider stork swan tiger toad trout turkey turtle weasel whale \
    wolf wombat zebra ";

/**
 * @var const char * usedLetters
 * Array to hold the letters that have been guessed previously.
 */

/**
 * @brief Prompt user for a guess and then scan in the letter of the guess while validating input.
 *
 * @param[out] guessedLetter The pointer to place the guessed letter.
 */
void getLetterGuess(char *guessedLetter) {

    printf("Please enter a letter to guess: "); // Prompt for guess
    scanf("%s", guessedLetter);
    printf("\n%s\n", guessedLetter);

    /* Scan and reprompt untill valid input */
    // while (scanErr != 1) {
    //     puts("Error, please enter a singular letter as a guess.");
    //     printf("Guess: ");
    //     scanf("%c", guessedLetter);
    // }
}

void runGame() {}

void printCurrentBoard(char *currentBoard) {
    int size = strlen(currentBoard) / sizeof(char *);
    for (int i = 0; i < size; i++) {
        printf("%s", &currentBoard[i]);
    }
    printf("\n");
}

// char *getSecretWord(const char *wordList) {
//     // Must be freed later
//     char *modifiedList = strdup(wordList);
//
//     char *delimiter = " "; //
//
//     int wordCount = 0;
//     unsigned long size = 0;
//
//     /* ----- Tokenizing and getting word count, then going thru and adding to array ---- */
//     char *token = strtok(modifiedList, delimiter); // First token
//     while (token != NULL) {
//         wordCount++;                     // Keep track of number of words in list
//         size += sizeof(strlen(token));   // Track size in bytes of list (with null byte)
//         token = strtok(NULL, delimiter); // Move to next word in list
//     }
//
//     printf("Size: %ld\n", size);
//     printf("Word Count: %d\n", wordCount);
//
//     char *tokenizedWordsArray[wordCount]; // Array to store individual words
//
//     // for (int i = 0; i < wordCount; i++) {
//     //     printf("%s, ", tokenizedWordsArray[i]);
//     // }
//     //
//     token = strtok(modifiedList, " "); // Move to first
//
//     for (int i = 0; i < wordCount; i++) {
//         puts("out 1");
//         printf("%s\n", token);
//         puts("out 2");
//         if (token == NULL) {
//             printf("%d\n", i);
//             perror("Error when parsing word list.");
//             break;
//         }
//         tokenizedWordsArray[i] = malloc(strlen(token));
//         puts("out 3");
//         strcpy(tokenizedWordsArray[i], token);
//     }
//
//     int randomIndex = rand() % wordCount;
//
//     return tokenizedWordsArray[randomIndex];
// }

void printHangmanPictures() {
    for (int i = 0; i < MAX_ERRORS; i++) {
        printf("%s\n", HANGMANPICS[i]);
    }
}

/**
 * @brief Check the users guess, updating the board and tracking if the game was won.
 *
 * @param[in] guessedLetter The letter guessed by the user
 * @param[in] secretWord The secret word being guessed
 * @param[in/out] currentBoard Current state of the board
 * @param[in] size Number of letters in the secret word & current board
 * @return Value representing weather the game was won during this guess.
 */
bool checkGuess(char *guessedLetter, char *secretWord, char *currentBoard, int size,
                bool *gameWon) {
    *gameWon = true;
    int discoveredLetters = 0;
    for (int i = 0; i < size; i++) {
        if (secretWord[i] == *guessedLetter) {
            // if ((strcmp(secretWord[i], guessedLetter)) == 0) {

            currentBoard[i] = *guessedLetter;
            discoveredLetters++;
        }
        if (currentBoard[i] == *"_") {
            puts("Letter not discovered.");
            *gameWon = false;
        }
    }

    bool guessIsCorrect;
    if (discoveredLetters > 0) {
        guessIsCorrect = true;
        printf("You discovered %d letters!\n", discoveredLetters);
    } else {
        guessIsCorrect = false;
        printf("The letter '%c' is not in the secret word.\n", *guessedLetter);
    }
    return guessIsCorrect;
}

void printWord(char *word) {
    int size = strlen(word) * sizeof(char *);
    for (int i = 0; i < size; i++) {
        printf("%s", &word[i]);
    }
    printf("\n");
}

/**
 * @brief Run the main program.
 *
 * @param argc [TODO:parameter]
 * @param argv [TODO:parameter]
 * @return [TODO:return]
 */
int main(int argc, char *argv[]) {

    // srand(time(NULL)); // Initialize for rand()
    // //
    // puts(getSecretWord(FullWordList));
    //

    // printHangmanPictures();

    char *secretWord = "apple";

    puts("out 1");
    int secretWordSize = strlen(secretWord);
    printf("sec word size: %d\n", secretWordSize);

    char *currentBoard = malloc((sizeof(char *)) * (secretWordSize + 1));
    puts("out 2");

    char playerGuess;

    puts("out 3");
    for (int i = 0; i < secretWordSize; i++) {
        currentBoard[i] = *"_";
        // strcpy(&currentBoard[i], "_");
        // currentBoard[i] = strdup(MASKED_CHAR_VALUE);
    }

    int errorCount = 0;
    bool gameWon = false;
    bool maxErrorsReached = false;
    bool guessIsCorrect = false;
    char *usedLetters = malloc(sizeof(char *) * MAX_GUESSED_LETTERS);

    while (!gameWon && !maxErrorsReached) {
        getLetterGuess(&playerGuess);

        guessIsCorrect =
            checkGuess(&playerGuess, secretWord, currentBoard, secretWordSize, &gameWon);
        if (!guessIsCorrect) {
            puts("Wrong guess.");

            usedLetters[errorCount++] = playerGuess;
            errorCount++;
        }

        printf("%s\n", HANGMANPICS[errorCount]);
        puts("\n=== CURRENT BOARD ===");
        puts("=====================");
        printf("%s\n", currentBoard);

        if (errorCount >= MAX_ERRORS) {
            maxErrorsReached = true;
        }
    }

    if (errorCount >= MAX_ERRORS) {
        puts("You lost.");
        printf("The secret word was: %s\n", secretWord);
        puts("Better luck next time!");
    } else if (gameWon) {
        printf("Congratulations! You guessed the secret word: %s\n", secretWord);
    } else {
        perror("Something went wrong.");
    }

    return 0;
}
