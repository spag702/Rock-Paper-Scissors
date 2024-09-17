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
    vector<double> regretSum, strat, stratSum;
    vector<double> oppStrat = {0.333333, 0.333333, 0.333333};

    // variables for random number generea
    default_random_engine generator;
    uniform_real_distribution<double> distribution;

public:

    RPSTrainer();
    ~RPSTrainer();

    // get random action based on mixed strategy
    int getAction(vector<double> strat);

    // training algorithm
    void train(int iterations);

    // get average mixed strategy across all training iterations
    vector<double> getAvgStrategy();

    // function to get mixed strat from "regret matching"
    vector<double> getStrat();
};

#endif 
