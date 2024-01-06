#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "json.hpp"
#include "utilities.hpp"

using namespace std;
using json = nlohmann::json;

void UserData::getData() {
    // Open the savedata.json file for reading
    ifstream infile("savedata.json");
    json jsonData;
    // Check if the file is successfully opened
    if (infile.is_open()) {
        // Read the JSON data from the file
        infile >> jsonData;
        // Close the file after reading
        infile.close();
    }
    else {
        // If the file cannot be opened, display an error message and exit the program
        cerr << "Error opening file.\nExiting...";
        exit(1);
    }
    // Extract user data from the JSON object
    json userData = jsonData["Account Data"][0];
    // Set the user's name, money, and loan using the extracted data
    setName(userData["Name"]);
    setMoney(userData["Money"]);
    setLoan(userData["Loan"]);
    cin.clear();
}

void UserData::bet() {
    double amount;
    // Check if the user has no money to bet
    if (money == 0) {
        cout << "You don't have any money to bet with!\n";
        cout << "Would you like to get a loan? [Yes/No]: ";
        // If the user wants to get a loan, call the loan() function
        if (checkInput()) {
            loan();
        }
        else {
            // If the user declines to get a loan, exit the program
            exit(1);
        }
    }
    // Retrieve data and renew previous data;
    getData();
    // Check if the user has an outstanding loan
    if (loanAmount > 0) {
        cout << "You currently have: $" << money << "\n";
        cout << "You currently owe: $" << loanAmount << "\n";
        cout << "Would you like to pay your loan? [Yes/No]: ";
        // If the user wants to pay the loan, call the payLoan() function
        if (checkInput()) {
            payLoan();
        }
    }
    // Display the current amount of money
    cout << "\nCurrent amount: $" << money << "\n";
    // Prompt the user to enter the bet amount
    cout << "How much do you want to bet?: ";
    cin >> amount;
    // Clear the input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Validate the entered amount
    while (!cin || amount <= 0 || amount > money) {
        cout << "Invalid input! Please enter a number greater than zero and less than your current balance: " << endl;
        // Prompt the user to enter a valid bet amount
        cin >> amount;
        // Clear the input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Display the bet amount
    cout << "Bet amount: $" << amount << "\n";
    // Deduct the bet amount from the user's money
    money -= amount;
    // Set the betAmount member variable
    betAmount = amount;
}

bool checkInput() {
    string input;
    do {
        // Get input from the user
        cin >> input;
        // Check if the input is 'yes' or 'y' or 'Yes'
        if (input == "yes" || input == "y" || input == "Yes") {
            cout << endl;
            return true;
        }
        // Check if the input is 'no' or 'n' or 'No'
        else if (input == "no" || input == "n" || input == "No") {
            return false;
        }
        // If the input is not valid, prompt the user to enter [Yes/No] again
        else {
            cout << "[checkInput]Invalid input... Please enter [Yes/No]: ";
        }
    } while (input != "yes" && input != "y" && input != "Yes" && input != "no" && input != "n" && input != "No");
    // The loop continues until valid input is provided, and the function returns true or false accordingly
    return false;
}

bool checkDataFile() {
    // Attempt to open the file in input mode
    ifstream infile("savedata.json");

    // Check if the file is in a good (readable) state
    if (!infile.good()) {
        // If the file is not in a good state, print an error message
        cerr << "Data does not exist... Creating new account..." << endl;
        // Close the file stream
        infile.close();
        // Return false indicating that the data file does not exist
        return false;
    }
    // If the file is in a good state, close the file and return true
    infile.close();
    return true;
}

void createDataFile(string name) {
    // Create a JSON object to store the account data
    json data;
    // Initialize the "Account Data" field as a JSON array
    data["Account Data"] = json::array();
    // Attempt to open the file in output mode
    ofstream outfile("savedata.json");
    // Check if the file is open (successfully created)
    if (!outfile.is_open()) {
        // If the file cannot be opened, print an error message
        cerr << "Error creating \"savedata.json\"...";
        // Exit the program with an error code
        exit(1);
    }
    // Create a new JSON object for the user's data
    json newData;
    // Set the user's name
    newData["Name"] = name;
    // Set the initial money amount
    newData["Money"] = 2500.00;
    // Set the initial loan amount to zero
    newData["Loan"] = 0;
    // Add the user's data to the "Account Data" array
    data["Account Data"].push_back(newData);
    // Write the JSON data to the file with indentation for readability
    outfile << setw(4) << data << endl;
    // Close the file stream
    outfile.close();
}

void UserData::savePoint() {
    // Read existing data from the file
    ifstream infile("savedata.json");
    json jsonData;
    if (infile.is_open()) {
        infile >> jsonData;
        infile.close();
    }
    else {
        cerr << "\nError opening file while saving." << endl;
        exit(1);
    }
    // Update the user's money and loan data in the JSON structure
    jsonData["Account Data"][0]["Money"] = money;
    jsonData["Account Data"][0]["Loan"] = loanAmount;
    // Write the updated JSON data back to the file
    ofstream outfile("savedata.json");
    if (outfile.is_open()) {
        outfile << setw(4) << jsonData << endl;
        outfile.close();
    }
    // Error handling for unable to open the file for writing
    else {
        cerr << "\nError opening file for writing while saving." << endl;
        exit(1);
    }
}

void UserData::loan() {
    double loan;
    // Prompt the user to enter the loan amount
    cout << "How much of would you like to receive?: ";
    cin >> loan;
    // Validate the entered loan amount
    while (cin.fail() || loan < 0 || loan > 3000) {
        //cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a loan greater than $0 and less than $3000: ";
        cin >> loan;
    }
    // Update user's data with the new loan amount
    loanAmount += loan;
    // Update JSON data with the new loan information
    json jsonData;
    jsonData["Account Data"][0]["Money"] = loan;
    jsonData["Account Data"][0]["Loan"] = loanAmount;
    jsonData["Account Data"][0]["Name"] = name;
    // Write the updated JSON data back to the file
    ofstream outfile("savedata.json");
    if (outfile.is_open()) {
        outfile << setw(4) << jsonData << endl;
        outfile.close();
    }
    // Error handling for unable to open the file for writing
    else {
        cerr << "\nError opening file for writing while processing loan." << endl;
        exit(1);
    }
    cout << "Loan of $" << loan << " has been received." << endl;
            cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void UserData::payLoan() {
    double amountPaid;
    // Prompt the user to enter the amount they wish to pay
    cout << "Enter the amount you wish to pay: ";
    cin >> amountPaid;
    // Update loan and money amounts based on the payment
    loanAmount -= amountPaid;
    money -= amountPaid;
}
