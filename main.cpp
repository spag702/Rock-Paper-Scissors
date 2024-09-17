#include "RPSTrainer.h"
#include <string>
#include <iostream>

int main() {
    // create an instance of the class
    RPSTrainer trainer;

    int iterations = 1000000; // Number of training iterations

    trainer.train(iterations);

    vector<double> avgStrategy = trainer.getAvgStrategy();

    // Output the probabilities of choices
    cout << "\nAverage strategy after " << iterations << " iterations:" << endl;
    cout << "Rock:     " << avgStrategy[0] << endl;
    cout << "Paper:    " << avgStrategy[1] << endl;
    cout << "Scissors: " << avgStrategy[2] << endl;

    // now we have the computer play against the user

    // create array of action names
    const vector<string> actionNames = {"rock", "paper", "scissors"};

    cout << "\nLet's play Rock-Paper-Scissors!" << endl;
    cout << "Enter your move <Rock|Paper|Scissors>. Type 'exit' to quit the game" << endl;

    // now we take user input
    string userPlay = "";
    bool playing = true;

    // game loop to repeat play
    while (playing){
        cout << "Your move: ";
        getline(cin, userPlay);

        // if user wants to exit game
        if (userPlay == "exit"){
            playing = false;
            cout << "\nExiting game" << endl;
            break;
        }
        
        int userAction = -1; // need to be an int so we can compare to computer choice

        if (userPlay == "rock"){
            userAction = 0;
        } else if (userPlay == "paper"){
            userAction = 1;
        } else if (userPlay == "scissors"){
            userAction = 2;
        } else {
            cout << "\nUh oh! Something went wrong!" << endl;
            cout << "Make sure input is ALL LOWERCASE and spelled correctly" << endl;
        }
        
        // have algorithm select computer play
        int computerAction = trainer.getAction(avgStrategy);

        cout << "\nComputer plays: " << actionNames[computerAction] << endl;

        // determine who wins
        if (userAction == computerAction) {
            cout << "It's a tie!" << endl;
        } else if ((userAction + 1) % 3 == computerAction) {
            cout << "You lose!" << endl;
        } else {
            cout << "You win!" << endl;
        }

        cout << endl;
        
    }

    return 0;
}
