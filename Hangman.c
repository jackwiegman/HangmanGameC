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

const char *MASKED_CHAR_VALUE = "_"; /** Value of the hidden spaces for the current board */
/**
 * @var const char * HANGMANPICS
 * Array holding pictures of a hangman at various stages to display.
 *
 * Got the pictures and word bank from this git project:
 * https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c
 *
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

/***************************
 * This was trying to get the bonus with choosing a random word from the word list but I started it
 * before a lot of other functionality and was going to come back to it but ran out of time.
 * I think I was pretty close to getting it, I was trying to tokenize the string in one loop and
 * then use the null byte characters ending the strings as a basis to loop through those, adding
 * each string to an array so that I could just choose a random int as the index of the array to
 * get the random word.
 * For the difficulty I was planning to sort that array by string length, then choose from the
 * first, second, or third thirds of the list representing easy, medium, and hard respectively.
 ***************************/
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

/**
 * @brief Prompt user for a guess and then scan in the letter of the guess while validating input.
 *
 * @param[out] guessedLetter The pointer to place the guessed letter.
 */
void getLetterGuess(char *guessedLetter) {

    printf("Please enter a letter to guess: "); // Prompt for guess
    scanf("%s", guessedLetter); // assign the char pointer to the guessed letter pointer
    printf("\n");
}

/**
 * @brief Print the current board with a banner.
 *
 * @param currentBoard Pointer to the current board to be displayed.
 */
void printCurrentBoard(char *currentBoard) {
    puts("\n=== CURRENT BOARD ===");
    puts("=====================");
    printf("%s\n", currentBoard);
}

/**
 * @brief Determine if the current guess has been guessed before.
 *
 * @param playerGuess The letter the player guessed
 * @param pastGuesses The string of all previous guesses
 * @return true if the guess is a duplicate, else false
 */
bool isDuplicateGuess(char *playerGuess, char *pastGuesses) {
    // Loop thru each past guess and check if it matches the current guess
    for (int i = 0; i < strlen(pastGuesses); i++) {
        if (pastGuesses[i] == *playerGuess) {
            // Return true if an entry in the past guesses matches the gurrent guess
            return true;
        }
    }
    return false;
}

/**
 * @brief Check the users guess, updating the board and tracking if the game was won.
 *
 * @param[in] guessedLetter The letter guessed by the user
 * @param[in] secretWord The secret word being guessed
 * @param[in/out] currentBoard Current state of the board
 * @param[in] pastGuesses The list of
 * @param[in] size Number of letters in the secret word & current board
 * @return Value representing weather the game was won during this guess.
 */
bool checkGuess(char *guessedLetter, char *secretWord, char *currentBoard, char *pastGuesses,
                int size, bool *gameWon) {
    *gameWon = true; // Set gamewon to true, as we will make it false if a blank character is found
    int discoveredLetters = 0; // Number of letters uncovered in this round

    /* Loop through the secret word to check for matches. */
    for (int i = 0; i < size; i++) {
        // If a match, increment the number of discovered letters to use later
        if (secretWord[i] == *guessedLetter) {
            currentBoard[i] = *guessedLetter; // Replace blank char with the discovered char
            discoveredLetters++;
        }
        // Checking for blank characters in the board, indicating the game hasn't been won, then
        // set the checker to false
        if (currentBoard[i] == *"_") {
            *gameWon = false;
        }
    }

    bool guessIsCorrect; // Tracks if the guess matched a letter in the secret word

    /* If letters have been discovered, it was a successful guess. Print a message and set variable
     * accordingly */
    if (discoveredLetters > 0) {
        guessIsCorrect = true;
        printf("You discovered %d letters!\n", discoveredLetters);
    } else {
        guessIsCorrect = false;
        printf("The letter '%c' is not in the secret word.\n", *guessedLetter);
    }

    return guessIsCorrect; // True if any number of letters were uncovered by the guess.
}

/**
 * @brief Print a string with spaces between the letters, for the guessed letters mainly.
 *
 * @param word Word to print
 * @param size Size of the string without spaces
 */
void printStringWithSpaces(char *word, int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", word[i]);
    }
    printf("\n");
}

/**
 * @brief Run the main program.
 *
 */
int main() {

    char *secretWord = "apricot";            /** Hard coded secret word. */
    int secretWordSize = strlen(secretWord); /** Number of letters in the secret word */

    char *currentBoard =
        malloc((sizeof(char *)) *
               (secretWordSize + 1)); /** A string the size of the secret word to store the hidden
                                         and revealed characters throughout the game */

    int errorCount = 0;            /** Counter for the number of errors the player has made. */
    bool gameWon = false;          /** Keep track of if the game has been won */
    bool maxErrorsReached = false; /** True if the amount of errors is enough to lose the game */
    bool guessIsCorrect = false;   /** Whether the players guess is a letter in the secret word */

    int usedLetterIndex = 0; /** Track the index to insert the next guessed letter */
    char *usedLetters =
        malloc(sizeof(char *) *
               MAX_GUESSED_LETTERS); /** String to hold at most each letter in the alphabet and
                                        track which letters have been guessed */

    char playerGuess; /** The letter guessed by the player */

    /* Assign the mask character to each letter in the word to display */
    for (int i = 0; i < secretWordSize; i++) {
        currentBoard[i] = *MASKED_CHAR_VALUE;
    }

    /* Startup messages and first board display */
    puts("Welcome to Hangman!");
    printf("There are %d letters in the secret word.\n", secretWordSize);
    printCurrentBoard(currentBoard);

    /* Main while loop that runs until the max number of errors has been reached or the game has
     * been won */
    while (!gameWon && !maxErrorsReached) {
        getLetterGuess(
            &playerGuess); /* Call function to get the guess and assign it to the pointer */

        /* Run the function checking duplicates until a new letter is guessed. */
        while (isDuplicateGuess(&playerGuess, usedLetters)) {
            printf("The letter '%s' has already been guessed. Try again.\n", &playerGuess);
            getLetterGuess(&playerGuess);
        }

        /* Check if the guess matches any letters in the secret word, and assign it to the var.
         * Also updates gamewon pointer checked by the loop. */
        guessIsCorrect = checkGuess(&playerGuess, secretWord, currentBoard, usedLetters,
                                    secretWordSize, &gameWon);

        /* Increment the error count if the guess wasn't correct */
        if (!guessIsCorrect) {
            errorCount++;
        }

        /* Add the guess to the previous guesses and increment the index for the next time */
        usedLetters[usedLetterIndex++] = playerGuess;

        /* Print the dialougues and information for the round */
        printf("%s\n", HANGMANPICS[errorCount]);
        printCurrentBoard(currentBoard);
        puts("Letters guessed:");
        printStringWithSpaces(usedLetters, MAX_GUESSED_LETTERS);

        /* Set the maxError var if the count has reached the max value. */
        if (errorCount >= MAX_ERRORS) {
            maxErrorsReached = true;
        }
    }

    /* Check for the cause after exiting the loop and print dialogue accordingly. */
    if (errorCount >= MAX_ERRORS) { // Check if exit due to error count, i.e., Losing
        puts("You lost.");
        printf("The secret word was: %s\n", secretWord);
        puts("Better luck next time!");
    } else if (gameWon) { // Otherwise check if game was won.
        printf("Congratulations! You guessed the secret word: %s\n", secretWord);
    } else { // Should be caught by one of the two above options, otherwise...
        puts("Something went wrong.");
    }

    return 0;
}
