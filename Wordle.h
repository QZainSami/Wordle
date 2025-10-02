#pragma once
#ifndef WORDLE_H
#define WORDLE_H

#include "config.h"
#include "GuessList.h"
#include "colors.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

// Difficulty levels
enum Difficulty { EASY = 1, MEDIUM = 2, HARD = 3 };

class Wordle {
private:
    char dictionary[MAX_WORDS][WORD_LEN + 1];  // Holds chosen difficulty's words
    int wordCount;                             // Number of words in current dictionary
    char secretWord[WORD_LEN + 1];
    GuessList guesses;
    bool hintUsed;

public:
    Wordle();
    void resetGame(Difficulty diff);           // Reset with difficulty choice
    int getBestScore();
    void saveBestScore(int score);
    void giveHint();
    void checkGuess(char guess[WORD_LEN + 1]);
    void play();
};

#endif
