#ifndef RPSTRAINER_H
#define RPSTRAINER_H

#include <iostream>
#include <vector>
#include <random>

using namespace std;

class RPSTrainer
{
private:
    // some private variable definitions
    static const int NUM_ACTIONS = 3;

    // variables for random number generea
    default_random_engine generator;
    uniform_real_distribution<double> distribution;

public:

    vector<double> regretSum, strat, stratSum;
    vector<double> oppStrat = {0.333333, 0.333333, 0.333333};

    RPSTrainer();
    ~RPSTrainer();

    // get random action based on mixed strategy
    int getAction(vector<double> strat);

    // training algorithm
    void train(int iterations);

    // get average mixed strategy across all training iterations
    vector<double> getAvgStrategy();

    // function to get strategy while playing with user
    vector<double> getStrat();

    // function to get initial strategy before playing with user
    vector<double> getTrainingStrat();

    // function that updates regrets after every round of play with user
    void updateRegret(int myAction, int oppAction);
};

#endif 
