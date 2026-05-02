//Name: Retuz Ahmed
//Date: 05/01/2026
//Purpose: Project 10; Twordle

#include <stdio.h>
#include <stdbool.h>

#define WORD_LEN 5
#define GUESS_MAX 6
#define STR_MAX 100

bool loadMysteryWord(char mysteryWord[]);
int strLen(char str[]);
bool validGuess(char str[]);
void makeLowercase(char str[]);
bool hasLetter(char ch, char str[]);
void getUserGuess(char guess[], int guessNum);
void buildDisplay(char display[], char guess[], char mysteryWord[]);
void buildArrows(char arrows[], char guess[], char mysteryWord[]);
void displayBoard(char displays[][WORD_LEN + 1], char arrows[][WORD_LEN + 1], int numGuesses);
void winMessage(char mysteryWord[], int numGuesses);

int main() {
    char mysteryWord[WORD_LEN + 1];
    char guess[STR_MAX];
    char displays[GUESS_MAX][WORD_LEN + 1];
    char arrows[GUESS_MAX][WORD_LEN + 1];

    if (!loadMysteryWord(mysteryWord)) {
      printf("Sorry, could not get today's word. Try again tomorrow.\n");
      return 0;
    }
    
    makeLowercase(mysteryWord);  
    int guessNum = 0;
    bool won = false;
    while (guessNum < GUESS_MAX && !won) {
        getUserGuess(guess, guessNum + 1);
        makeLowercase(guess);
        won = true;
        for (int i = 0; i < WORD_LEN; i++) {
            if (guess[i] != mysteryWord[i]) {
                won = false;
                break;
            }
        }
        
        buildDisplay(displays[guessNum],  guess, mysteryWord);
        buildArrows(arrows[guessNum], guess, mysteryWord);
        guessNum++;
        printf("================================\n");
        if (won) {
            winMessage(mysteryWord, guessNum);
        } else {
            displayBoard(displays, arrows, guessNum);
        }
    }

    if (!won) {
        printf("You lost, better luck next time!\n");
    }
    return 0;
}

bool loadMysteryWord(char mysteryWord[]) {
    FILE *fp = fopen("word.txt", "r");
    if (fp == NULL) {
        return false;
    }
    if (fscanf(fp, "%s", mysteryWord) != 1) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    
    return true;
}

int strLen(char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

bool validGuess(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        bool lower = (c >= 'a' && c <= 'z');
        bool upper = (c >= 'A' && c <= 'Z');
        if (!lower && !upper) {
            return false;
        }
    }
    return true;
}

void makeLowercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}

bool hasLetter(char ch, char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            return true;
        }
    }
    return false;
}

void getUserGuess(char guess[], int guessNum) {
    if (guessNum == GUESS_MAX) {
        printf("FINAL GUESS : ");
    } else {
        printf("GUESS %d! Enter your guess: ", guessNum);
    }
    scanf("%s", guess);
    while (strLen(guess) != WORD_LEN || !validGuess(guess)) {
        if (strLen(guess) != WORD_LEN) {
            printf("Your guess must be 5 letters long.\n");
        } else {
            printf("Your guess must contain only letters.\n");
        }
        printf("Please try again: ");
        scanf("%s", guess);
    }
}

void buildDisplay(char display[], char guess[], char mysteryWord[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == mysteryWord[i]) {
            display[i] = guess[i] - 'a' + 'A';
        } else {
            display[i] = guess[i];
        }
    }
    display[WORD_LEN] = '\0';
}

void buildArrows(char arrows[], char guess[], char mysteryWord[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        arrows[i] = ' ';
    }
    arrows[WORD_LEN] = '\0';
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == mysteryWord[i]) {
            continue;
        }

        if (!hasLetter(guess[i], mysteryWord)) {
            continue;
        }

        bool alreadyClaimed = false;
        for (int j = 0; j < WORD_LEN; j++) {
            if (guess[j] == guess[i] && guess[j] == mysteryWord[j]) {
                alreadyClaimed = true;
                break;
            }
        }
        if (alreadyClaimed) {
            continue;
        }

        bool alreadyPointedAt = false;
        for (int k = 0; k < i; k++) {
            if (guess[k] == guess[i] && arrows[k] == '^') {
                alreadyPointedAt = true;
                break;
            }
        }
        if (!alreadyPointedAt) {
            arrows[i] = '^';
        }
    }
}

void displayBoard(char displays[][WORD_LEN + 1], char arrows[][WORD_LEN + 1], int numGuesses) {
    for (int i = 0; i < numGuesses; i++) {
        printf("%s\n", displays[i]);
        printf("%s\n", arrows[i]);
    }
}

void winMessage(char mysteryWord[], int numGuesses) {
    printf("                ");
    for (int i = 0; i < WORD_LEN; i++) {
        char letter = mysteryWord[i];
        if (letter >= 'a' && letter <= 'z') {
            letter = letter - 'a' + 'A';
        }
        printf("%c", letter);
    }
    printf("\n");
    if (numGuesses == 1) {
        printf("        You won in 1 guess!\n");
        printf("                 GOATED!\n");
    } else {
        printf("        You won in %d guesses!\n", numGuesses);
        if (numGuesses <= 3) {
            printf("                Amazing!\n");
        } else if (numGuesses <= 5) {
            printf("                Nice!\n");
        }
    }
}


