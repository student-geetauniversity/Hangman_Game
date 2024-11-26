#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void showWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool wordGuessed(const vector<bool>& guessed) {
    for (bool g : guessed) {
        if (!g) return false;
    }
    return true;
}

int main() {
    vector<string> words = { "hangman", "program", "cpp", "dev", "computer" };
    srand(static_cast<unsigned int>(time(0)));
    string word = words[rand() % words.size()];

    vector<bool> guessed(word.length(), false);
    vector<char> wrongGuesses;
    int attempts = 6;

    cout << "Welcome to Hangman!" << endl;

    while (attempts > 0) {
        cout << "Current word: ";
        showWord(word, guessed);
        cout << "Wrong guesses: ";
        for (char ch : wrongGuesses) {
            cout << ch << " ";
        }
        cout << endl;
        cout << "Attempts remaining: " << attempts << endl;

        char guess;
        cout << "Enter your guess (a single letter): ";
        cin >> guess;
        guess = tolower(guess);

        if (find(wrongGuesses.begin(), wrongGuesses.end(), guess) != wrongGuesses.end() ||
            find(guessed.begin(), guessed.end(), true) != guessed.end() && 
            word[find(guessed.begin(), guessed.end(), true) - guessed.begin()] == guess) {
            cout << "You've already guessed that letter. Try again." << endl;
            continue;
        }

        bool correct = false;

        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess) {
                guessed[i] = true;
                correct = true;
            }
        }

        if (!correct) {
            wrongGuesses.push_back(guess);
            attempts--;
            cout << "Wrong guess!" << endl;
        }

        if (wordGuessed(guessed)) {
            cout << "Congratulations! You've guessed the word: " << word << endl;
            break;
        }
    }

    if (attempts == 0) {
        cout << "Sorry, you've run out of attempts. The word was: " << word << endl;
    }

    return 0;
}
