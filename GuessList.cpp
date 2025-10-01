#include "GuessList.h"
#include <string>

// Node constructor
Node::Node(const char g[]) {
    strcpy_s(guess, g);
    next = nullptr;
}

// GuessList constructor
GuessList::GuessList() {
    head = nullptr;
    tail = nullptr;
}

// Add a guess
void GuessList::addGuess(const char g[]) {
    Node* newNode = new Node(g);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Display all guesses
void GuessList::displayGuesses() {
    cout << "\nYour guesses history:\n";
    Node* current = head;
    int attempt = 1;
    while (current) {
        cout << attempt++ << ": " << current->guess << endl;
        current = current->next;
    }
}

// Destructor
GuessList::~GuessList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}
