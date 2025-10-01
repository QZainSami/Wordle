#pragma once
#ifndef WORDLE_H
#define WORDLE_H

#include "GuessList.h"
#include "colors.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

const int MAX_WORDS = 500;
const int MAX_ATTEMPTS = 6;

class Wordle {
private:
    char dictionary[MAX_WORDS][WORD_LEN + 1];
    char secretWord[WORD_LEN + 1];
    GuessList guesses;
    bool hintUsed;

public:
    Wordle();
    void resetGame();
    int getBestScore();
    void saveBestScore(int score);
    void giveHint();
    void checkGuess(char guess[WORD_LEN + 1]);
    void play();
};

#endif
