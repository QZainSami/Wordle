#include "Wordle.h"
#include "colors.h"
#include <iostream>
using namespace std;

void howToPlay() {
    cout << "\n" << YELLOW << "📘 HOW TO PLAY WORDLE" << RESET << "\n";
    cout << "1. Guess a 5-letter word within 6 attempts.\n";
    cout << "2. " << GREEN << "Green" << RESET << " = correct letter in correct position.\n";
    cout << "3. " << YELLOW << "Yellow" << RESET << " = correct letter but wrong position.\n";
    cout << "4. " << GRAY << "Gray" << RESET << " = letter not in the word.\n";
    cout << "5. Type 'hint' to reveal one letter (only once per game).\n\n";
}

int main() {
    while (true) {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Play Wordle\n";
        cout << "2. How to Play\n";
        cout << "3. Exit\n";
        cout << "Choose option: ";
        int choice; cin >> choice;

        if (choice == 1) {
            Wordle game;
            game.play();

            cout << "\nDo you want to play again? (y/n): ";
            char again; cin >> again;
            if (again == 'y' || again == 'Y') continue;
            else break;
        }
        else if (choice == 2) howToPlay();
        else if (choice == 3) break;
        else cout << RED << "Invalid option!" << RESET << endl;
    }
    cout << "\nThanks for playing Wordle! Goodbye.\n";
    return 0;
}
