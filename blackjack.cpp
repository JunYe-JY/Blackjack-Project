#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "blackjack.hpp"

using namespace std;

void BlackJack::reset() {
        // Clear hands
        Player_Hand.clear();
        Dealer_Hand.clear();
        // Clear deck
        Deck.clear();
        // Reset game state
        state = GameState::PLAYER_TURN;
        winner = Winner::NONE;
    }

bool BlackJack::runGame() {
    // Reset any existing game data
    reset();
    // Initialize deck and shuffle
    initializeDeck();
    // Deal initial cards to the dealer and player
    dealHands();
    // Run the game loop until the game state is GAME_OVER
    while (state != GameState::GAME_OVER) {
        // Check the current state of the game and perform the corresponding actions
        if (state == GameState::PLAYER_TURN) {
            // Player's turn: Allow the player to hit or stand
            playerTurn();
        }
        else if (state == GameState::DEALER_TURN) {
            // Dealer's turn: Let the dealer play its turn
            dealerTurn();
        }
    }
    if (winner == Winner::PLAYER) {
        return true;
    }
    // End of the game
    return false;
}

void BlackJack::initializeDeck() {
    // Create the deck of 52 cards (excluding Jokers)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            // Add a card to the deck with the current Rank and Suit
            Deck.push_back({static_cast<Rank>(j), static_cast<Suit>(i)});
        }
    }
    // Randomize the deck of 52 cards
    // Using random_device to generate a seed and mt19937 as the random number generator
    random_device rd;
    mt19937 gen(rd());
    // Shuffle the deck using the generated seed
    shuffle(Deck.begin(), Deck.end(), gen);
}

int BlackJack::getCardValue(const Card &card) {
    // Variable to store the value of the card
    int value = 0;
    // Switch statement to determine the value based on the card's rank
    switch (card.rank) {
        // For number cards (2 through 9), set value to the position of the rank + 2
        case Rank::TWO:
        case Rank::THREE:
        case Rank::FOUR:
        case Rank::FIVE:
        case Rank::SIX:
        case Rank::SEVEN:
        case Rank::EIGHT:
        case Rank::NINE:
            value = static_cast<int>(card.rank) + 2;
            break;
        // For face cards (10, Jack, Queen, King), set value to 10
        case Rank::TEN:
        case Rank::JACK:
        case Rank::QUEEN:
        case Rank::KING:
            value = 10;
            break;
        // For Ace, set value to 11
        case Rank::ACE:
            value = 11;
            break;
    }
    // Return the calculated value for the card
    return value;
}

int BlackJack::getHandValue(const vector<Card> &hand) {
    // Variable to store the total value of the hand
    int value = 0;
    // Variable to count the number of Aces in the hand
    int numAces = 0;
    // Loop through each card in the hand to calculate its value
    for (const Card &card : hand){
        // Add the value of the current card to the total hand value
        value += getCardValue(card);
        // Count Aces for calculations for value of 11 or 1
        if (card.rank == Rank::ACE) {
            numAces++;
        }
    }
    // If the hand value is greater than 21 with an Ace, set the Ace value to 1
    // This is done to handle the flexible value of Aces (11 or 1)
    if (value > 21 && numAces > 0) {
        value -= 10; // Subtract 10 to change the value of one Ace from 11 to 1
        numAces--;   // Reduce the count of Aces
    }
    // Return the total value of the hand
    return value;
}

void BlackJack::dealHands() {
    //Add cards to Dealer and Player hand
    Player_Hand.push_back(Deck.back());
    Deck.pop_back();
    Dealer_Hand.push_back(Deck.back());
    Deck.pop_back();
    Player_Hand.push_back(Deck.back());
    Deck.pop_back();
    Dealer_Hand.push_back(Deck.back());
    Deck.pop_back();
}

void BlackJack::displayHand() {
    // Display the player's hand
    cout << "Player Hand: ";
    // Show cards of Player hand
    for (const Card &card : Player_Hand) {
        show_card(card);
        cout << " ";
    }
    // Display the total value of the player's hand
    cout << "(Value: " << getHandValue(Player_Hand) << ")\n";
    // Display the dealer's hand with only the first card visible
    cout << "Dealer Hand: ";
    // Show only the first card of Dealer hand
    show_card(Dealer_Hand[0]);
}

void BlackJack::playerTurn() {
    // Variable to store user input
    string input;
    // Variable to store the current hand value of the player
    int playerHandValue;
    // Loop until the player stands or busts
    while (true) {
        // Display the player's hand
        displayHand();
        // Prompt the player to choose between hitting or standing
        cout << "\nYOUR TURN. Do you want to hit or stand?: ";
        getline(cin, input);
        cout << "\n";
        // Check the player's input and perform the corresponding action
        if (input == "hit" || input == "Hit" || input == "H" || input == "h") {
            // If the player chooses to hit, draw a card from the deck and add it to their hand
            Player_Hand.push_back(Deck.back());
            Deck.pop_back();
            // Calculate the player's hand value and check if it exceeds 21 (bust)
            playerHandValue = getHandValue(Player_Hand);
            if (playerHandValue > 21) {
                // If the player busts, display the hand and end the game
                displayHand();
                cout << "\nBusted! Your hand is valued: " << playerHandValue << endl;
                state = GameState::GAME_OVER;
                winner = Winner::DEALER;
                return;
            }
        }
        else if (input == "stand" || input == "Stand" || input == "S" || input == "s") {
            // If the player chooses to stand, proceed to the dealer's turn
            state = GameState::DEALER_TURN;
            return;
        }
        else {
            // If the input is invalid, prompt the player to enter a valid option
            cout << "Invalid input. Please enter `Hit/hit` or `Stand/stand`\n";
        }
    }
}

void BlackJack::dealerTurn() {
    // Variables to track the number of Aces in the dealer's hand and the final hand value
    int numAces = 0, dealerHandValue;
    // Display the dealer's hand
    displayHand();
    // Count the number of Aces in the dealer's hand
    for (const Card &card : Dealer_Hand){
        if (card.rank == Rank::ACE) {
            numAces++;
        }
    }
    // If the dealer has an Ace in their hand, they must draw until they have a hand value less than 16
    // or exactly 17 if they have one Ace
    while (getHandValue(Dealer_Hand) < 17 || (numAces == 1 && getHandValue(Dealer_Hand) == 17)) {
        // Draw a card from the deck and add it to the dealer's hand
        Dealer_Hand.push_back(Deck.back());
        Deck.pop_back();
    }
    // Get the final hand value of the dealer
    dealerHandValue = getHandValue(Dealer_Hand);
    // Display the dealer's final hand
    cout << "\n\nDealer's final hand: ";
    for (const Card &card : Dealer_Hand) {
        show_card(card);
        cout << " ";
    }
    // Display the final hand value of the dealer
    cout << "\nDealer's final hand value: " << dealerHandValue << endl;
    // Determine the winner based on the final hand values
    if (dealerHandValue > 21 || dealerHandValue < getHandValue(Player_Hand)) {
        cout << "You Win!\n";
        winner = Winner::PLAYER;
    }
    else if (dealerHandValue > getHandValue(Player_Hand)) {
        cout << "Dealer wins!\n";
        winner = Winner::DEALER;
    }
    else {
        cout << "Tie!\n";
        winner = Winner::NONE;
    }
    // Set the game state to GAME_OVER
    state = GameState::GAME_OVER;
}

// Function to display a card based on its rank and suit
void show_card(const Card& card) { 
    switch (card.rank) {
        case Rank::TWO:
        case Rank::THREE:
        case Rank::FOUR:
        case Rank::FIVE:
        case Rank::SIX:
        case Rank::SEVEN:
        case Rank::EIGHT:
        case Rank::NINE:
        case Rank::TEN:
            cout << static_cast<int>(card.rank) + 2;
            break;
        case Rank::JACK:
            cout << "J";
            break;
        case Rank::QUEEN:
            cout << "Q";
            break;
        case Rank::KING:
            cout << "K";
            break;
        case Rank::ACE:
            cout << "A";
            break;
    }
    switch (card.suit) {
        case Suit::HEART:
            cout << "H";
            break;
        case Suit::DIAMOND:
            cout << "D";
            break;
        case Suit::CLUB:
            cout << "C";
            break;
        case Suit::SPADE:
            cout << "S";
            break;
    }
}