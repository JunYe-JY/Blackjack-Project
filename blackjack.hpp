#ifndef BLACKJACK_HPP
#define BLACKJACK_HPP

#include <vector>
#include "utilities.hpp"

using namespace std;

// Enumeration representing the game states
enum class GameState {
    PLAYER_TURN, DEALER_TURN, GAME_OVER
};

// Enumeration representing the winner of the game
enum class Winner {
    PLAYER, DEALER, NONE
};

// Class representing the Blackjack game
class BlackJack {
    private:
        vector<Card> Deck;        // Deck of cards
        vector<Card> Player_Hand; // Player's hand
        vector<Card> Dealer_Hand; // Dealer's hand
        GameState state;          // Current game state
        Winner winner;            // Winner of the game

    public:
        // Constructor initializes the game state and winner
        BlackJack() : state(GameState::PLAYER_TURN), winner(Winner::NONE) {};
        // Function to reset the game
        void reset();
        // Function to run the Blackjack game
        bool runGame();
        // Function to initialize the deck of cards
        void initializeDeck();
        // Function to get the numerical value of a card
        int getCardValue(const Card& card);
        // Function to get the total value of a hand
        int getHandValue(const vector<Card>& hand);
        // Function to deal initial hands to the player and dealer
        void dealHands();
        // Function to display the current hand
        void displayHand();
        // Function representing the player's turn
        void playerTurn();
        // Function representing the dealer's turn
        void dealerTurn();
};

// Function to display a card
void show_card(const Card& card);

#endif