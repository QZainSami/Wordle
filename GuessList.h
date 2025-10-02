#pragma once
#ifndef GUESSLIST_H
#define GUESSLIST_H

#include "config.h"
#include <iostream>
#include <cstring>
using namespace std;

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
	void clear();
    ~GuessList();
};

#endif
