#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

using namespace std;

// Enumeration representing card ranks
enum class Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
};

// Enumeration representing card suits
enum class Suit {
    SPADE, HEART, CLUB, DIAMOND
};

// Class representing a playing card
class Card {
public:
    Rank rank;
    Suit suit;
};

// Class representing user data for the Blackjack game
class UserData {
    private:
        string name;
        double money;
        double betAmount;
        double loanAmount;
    public:
        // Function to set the user's name
        void setName(string name) {
            this->name = name;
        }
        // Function to set the user's money
        void setMoney(double money) {
            this->money = money;
        }
        // Function to set the user's loan amount
        void setLoan(double loan) {
            this->loanAmount = loan;
        }
        // Function to get the user's money
        double getMoney() {
            return money;
        }
        // Function to get user data from a file
        void getData();
        // Function for the user to place a bet
        void bet();
        // Function to award the user's bet
        void betAward() {
            money += (betAmount * 2);
        }
        // Function to save user data
        void savePoint();
        // Function for the user to take a loan
        void loan();
        // Function for the user to repay the loan
        void payLoan();
};

// Function to check user input (yes/no)
bool checkInput();
// Function to check if data file exists
bool checkDataFile();
// Function to create a new data file with user's name
void createDataFile(string name);

#endif