# Blackjack-Project

# Blackjack Game
This is a simple command-line-based Blackjack game implemented in C++. The game includes basic functionality for player actions such as betting, receiving loans, and playing the core Blackjack game against the dealer.
This is programmed using Object-Oriented Programming utilizing the encapsulation of data and behaviors, as well as procedural programming in utility functions.

# How to Play
Run the Game: Compile and run the game using a C++ compiler.

Create an Account: If it's your first time playing, you'll need to create an account by entering your name. Your account information will be saved in a file called savedata.json.

Place a Bet: Enter the amount you want to bet. If you don't have enough money, you can choose to get a loan.

Play the Game: The game will proceed with your turn to draw cards and make decisions. Follow the on-screen prompts to play your hand.

Winning: The game will determine the winner based on the final hand values of the player and the dealer. If you win, your account balance will be updated.

Continue Playing: You can choose to continue playing additional rounds.

# Features
Player Account: Your account data, including your name, current money balance, and any outstanding loans, is saved in a JSON file (savedata.json).

Betting: You can place bets, and if you win, your account balance will be updated accordingly.

Loans: If you run out of money, you can choose to get a loan. However, keep in mind that loans need to be repaid.

Game Logic: The game follows standard Blackjack rules, with actions such as hitting, standing, and determining the winner based on hand values.

# Files
blackjack.hpp: Header file containing the BlackJack class and related enumerations.

blackjack.cpp: Implementation file for the BlackJack class.

utilities.hpp: Header file containing the UserData class, utility functions, and card-related enumerations.

utilities.cpp: Implementation file for the UserData class and utility functions.

json.hpp: External library for handling JSON data.

main.cpp: Main program file that includes the game loop.
