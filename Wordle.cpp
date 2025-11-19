#include "Wordle.h"
#include <iostream>
#include <cstring>
using namespace std;

// 100 Easy words
char easyWords[100][WORD_LEN + 1] = {
"apple","grape","mango","pearl","stone","chair","plane","crane","bread","sugar",
"light","water","earth","zebra","tiger","eagle","snake","lemon","melon","peach",
"berry","flame","smile","dream","cloud","music","dance","river","storm","green",
"ghost","witch","magic","flute","ocean","table","piano","candy","crown","queen",
"kingy","sword","armor","giant","noble","faith","honor","night","sunny","rainy",
"frost","chess","books","movie","anime","novel","codes","array","stack","queue",
"happy","quick","smart","house","plant","bread","socks","laugh","child","sweet",
"brush","shirt","couch","round","tasty","drink","clock","towel","beach","clean",
"pride","train","horse","camel","goose","sheep","candy","apple","table","spoon",
"bread","flour","chair","pasta","mouse","lemon","pearl","candy","light","green"
};

// 100 Medium words
char mediumWords[100][WORD_LEN + 1] = {
"adore","brave","chase","climb","dream","fancy","grasp","haste","judge","kneel",
"logic","march","noble","ocean","proud","quiet","rebel","sense","thief","union",
"vivid","weary","youth","zesty","amber","blush","cider","daisy","ember","feast",
"glory","honey","ivory","jolly","karma","lunar","mirth","naive","opera","pulse",
"quirk","realm","scent","toxic","utter","vocal","witty","yield","zebra","arcus",
"badge","creed","delta","exile","fable","grind","haste","inlet","jewel","knock",
"latte","medal","niche","oasis","plume","quill","rider","shade","troop","unity",
"vigor","wheat","xenon","yacht","zonal","altar","brace","civic","dread","elite",
"flair","gloom","hymns","irony","jumpy","karma","latch","mourn","nerve","orbit"
};

// 100 Hard words
char hardWords[100][WORD_LEN + 1] = {
"abhor","banjo","crypt","deign","epoch","fjord","glyph","haiku","ivory","jazzy",
"kayak","lyric","mnemo","nymph","oxide","proxy","quasi","rhyme","sphix","throb",
"umbra","vexed","wharf","xylem","yoked","zilch","azure","blitz","cynic","dirge",
"ennui","feign","gnash","heist","ionic","joule","knoll","llama","macaw","nymph",
"occam","psalm","quark","regal","stoic","tryst","ulcer","vigil","waltz","xerox",
"yuppy","zesty","aloof","bleak","crisp","droll","eerie","fluke","grimy","hound",
"inert","jaded","khaki","lurid","moron","niece","obese","pique","quash","revue",
"scorn","tacit","uncut","vapid","wreak","xenon","yokel","zonal","angst","brunt",
"clasp","dowry","ennui","fraud","guise","humid","inane","jaunt","knave","leech"
};

// Constructor
Wordle::Wordle() {
    srand(static_cast<unsigned int>(time(0)));
    hintUsed = false;
}

// Reset game with difficulty
void Wordle::resetGame(Difficulty diff) {
    // Load dictionary based on difficulty
    if (diff == EASY) {
        wordCount = 100;
        memcpy(dictionary, easyWords, sizeof(easyWords));
    }
    else if (diff == MEDIUM) {
        wordCount = 100;
        memcpy(dictionary, mediumWords, sizeof(mediumWords));
    }
    else {
        wordCount = 100;
        memcpy(dictionary, hardWords, sizeof(hardWords));
    }

    // Pick random secret word
    strcpy_s(secretWord, WORD_LEN + 1, dictionary[rand() % wordCount]);
    guesses.clear();
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
        cout << "\n<3 Lives left: " << (MAX_ATTEMPTS - attempt + 1) << endl;
        cout << "Attempt " << attempt << ": ";
        
        string input;
        if (!(cin >> input)) {
            // handle EOF / input error gracefully
            cout << RED << "Input error." << RESET << endl;
            return;
        }

        if (input == "hint") {
            giveHint();
            attempt--; continue;
        }

        if (input.length() != WORD_LEN) {
            cout << RED << "Word must be " << WORD_LEN << " letters long!" << RESET << endl;
            attempt--; continue;
        }

        // copy safely into fixed-size buffer (length already validated)
        strcpy_s(guess, WORD_LEN + 1, input.c_str());

        guesses.addGuess(guess);
        checkGuess(guess);

        if (strcmp(guess, secretWord) == 0) {
            cout << GREEN << "\n[*] Congratulations! You guessed the word: " << secretWord << RESET << endl;
            guesses.displayGuesses();

            int score = attempt;
            int best = getBestScore();
            if (score < best) {
                cout << YELLOW << "[BEST] New Best Score: " << score << RESET << endl;
                saveBestScore(score);
            }
            else {
                cout << "Best Score so far: " << best << endl;
            }
            return;
        }
    }
    cout << RED << "\n[X] Game Over! The word was: " << secretWord << RESET << endl;
    guesses.displayGuesses();
}
