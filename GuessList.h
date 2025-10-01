#pragma once
#ifndef GUESSLIST_H
#define GUESSLIST_H

#include <iostream>
#include <cstring>
using namespace std;

const int WORD_LEN = 5;

struct Node {
    char guess[WORD_LEN + 1];
    Node* next;
    Node(const char g[]);
};

class GuessList {
private:
    Node* head;
    Node* tail;
public:
    GuessList();
    void addGuess(const char g[]);
    void displayGuesses();
    ~GuessList();
};

#endif
