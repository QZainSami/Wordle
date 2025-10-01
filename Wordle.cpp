#include "Wordle.h"
#include <iostream>
#include <cstring>
using namespace std;

Wordle::Wordle() {
    char temp[MAX_WORDS][WORD_LEN + 1] = {
    "apple","grape","mango","pearl","stone","chair",
    "plane","crane","bread","sugar","light","water",
    "earth","zebra","tiger","eagle","snake","lemon",
    "melon","peach","berry","flame","smile","dream",
    "cloud","music","dance","river","storm","green",
    "ghost","witch","magic","flute","ocean","table",
    "piano","candy","crown","queen","kingy","sword",
    "armor","giant","noble","faith","honor","night",
    "sunny","rainy","frost","chess","books","movie",
    "anime","novel","codes","array","stack","queue"
    };

    for (int i = 0; i < MAX_WORDS; i++) strcpy_s(dictionary[i], temp[i]);
    srand(time(0));
    resetGame();
}

void Wordle::resetGame() {
    int index = rand() % MAX_WORDS;
    strcpy_s(secretWord, dictionary[index]);
    hintUsed = false;
}

int Wordle::getBestScore() {
    ifstream in("bestscore.txt");
    int score; if (in >> score) return score;
    return 999;
}

void Wordle::saveBestScore(int score) {
    ofstream out("bestscore.txt");
    out << score;
}

void Wordle::giveHint() {
    if (hintUsed) {
        cout << RED << "You already used your hint!" << RESET << endl;
        return;
    }
    int pos = rand() % WORD_LEN;
    cout << YELLOW << "Hint: Letter at position " << pos + 1 << " is '" << secretWord[pos] << "'" << RESET << endl;
    hintUsed = true;
}

void Wordle::checkGuess(char guess[WORD_LEN + 1]) {
    bool usedSecret[WORD_LEN] = { false };
    bool usedGuess[WORD_LEN] = { false };

    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == secretWord[i]) {
            cout << GREEN << guess[i] << RESET;
            usedSecret[i] = true;
            usedGuess[i] = true;
        }
        else cout << "_";
    }
    cout << endl;

    for (int i = 0; i < WORD_LEN; i++) {
        if (!usedGuess[i]) {
            bool found = false;
            for (int j = 0; j < WORD_LEN; j++) {
                if (!usedSecret[j] && guess[i] == secretWord[j]) {
                    found = true; usedSecret[j] = true; break;
                }
            }
            if (found) cout << YELLOW << guess[i] << RESET << " is in the word but wrong position\n";
            else cout << GRAY << guess[i] << RESET << " is not in the word\n";
        }
    }
}

void Wordle::play() {
    cout << "\nWelcome to " << GREEN << "Wordle (C++ CLI Edition)" << RESET << "!\n";
    cout << "Guess the " << WORD_LEN << "-letter word. You have " << MAX_ATTEMPTS << " attempts.\n";

    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        char guess[WORD_LEN + 1];
        cout << "\n❤️ Lives left: " << (MAX_ATTEMPTS - attempt + 1) << endl;
        cout << "Attempt " << attempt << ": ";
        cin >> guess;

        if (strcmp(guess, "hint") == 0) {
            giveHint();
            attempt--; continue;
        }

        if (strlen(guess) != WORD_LEN) {
            cout << RED << "Word must be " << WORD_LEN << " letters long!" << RESET << endl;
            attempt--; continue;
        }

        guesses.addGuess(guess);
        checkGuess(guess);

        if (strcmp(guess, secretWord) == 0) {
            cout << GREEN << "\n🎉 Congratulations! You guessed the word: " << secretWord << RESET << endl;
            guesses.displayGuesses();

            int score = attempt;
            int best = getBestScore();
            if (score < best) {
                cout << YELLOW << "🏆 New Best Score: " << score << RESET << endl;
                saveBestScore(score);
            }
            else {
                cout << "Best Score so far: " << best << endl;
            }
            return;
        }
    }
    cout << RED << "\n💀 Game Over! The word was: " << secretWord << RESET << endl;
    guesses.displayGuesses();
}
