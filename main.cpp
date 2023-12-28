#include <iostream>
#include "blackjack.hpp"
#include "utilities.hpp"

using namespace std;

int main() {
    string name;
    UserData User;
    BlackJack BJ;

    // Welcome message
    cout << "Welcome to Jun's Poker game" << endl;

    // Check if user has existing data, if not, create an account
    if (!checkDataFile()) {
        cout << "Create an account.\nEnter your name: ";
        getline(cin, name);
        createDataFile(name);
        User.getData(); // Load user data from file
    }
    else {
        User.getData(); // Load user data from file
    }

    // Main game loop
    do {
        User.bet(); // Prompt user to place a bet

        // Run the Blackjack game
        if (BJ.runGame()) {
            User.betAward(); // Award the user's bet based on game outcome
        }

        User.savePoint(); // Save user data after the game

        // Ask if the user wants to continue playing
        cout << "\nDo you want to continue? [yes/no]: ";
    } while (checkInput());

    return 0;
}