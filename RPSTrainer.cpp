#include "RPSTrainer.h"

// default constructor
RPSTrainer::RPSTrainer() : regretSum(NUM_ACTIONS, 0.0), 
                           strat(NUM_ACTIONS, 0.0),
                           stratSum(NUM_ACTIONS, 0.0),
                           distribution(0.0, 1.0) {
    // initialize vectors with correct num of elements
    // and random numbers to be distributed between (0.0, 1.0]

    // seed random number generator
    random_device rd;
    generator.seed(rd());
}

RPSTrainer::~RPSTrainer()
{
}

// function to compute a mixed strategy
vector<double> RPSTrainer::getStrat() {
    // sum of all positive regrets
    double normalizingSum = 0;

    // copy all positive regrets to 'strat' then sum them
    for (int i = 0; i < NUM_ACTIONS; i++){
        
        if (regretSum[i] > 0){
            strat[i] = regretSum[i];
        } else {
            strat[i] = 0;
        }
        
        normalizingSum += strat[i];
    }

    // now we normalize these regrets (so that arrays sum to 1, representing probabilites)
    for (int i = 0; i < NUM_ACTIONS; i++){

        // if at least one action w/ positive regret
        if (normalizingSum > 0){
            // divide by normalizing sum
            strat[i] /= normalizingSum;
        } else {
            // in the case of non-positive sum, give actions equal probability
            strat[i] = 1.0 / NUM_ACTIONS;
        }
        
        stratSum[i] += strat[i];
    }
    
    return strat;
}

// function to retrieve random action from mixed strategy
int RPSTrainer::getAction(vector<double> strat){
    // generate a random floating point number in range (0, 1]
    double r = distribution(generator);

    // initialize cumulative probabiliy to 0
    double cumulativeProb = 0; 

    // loop to iterate over each action
    for (int a = 0; a < NUM_ACTIONS; a++){
        // sums probablity of actions "sequentially"
        cumulativeProb += strat[a];

        // if r falls within range, we have our action
        if (r < cumulativeProb){
            return a;
        }
    }
    
    // if probability or rounding error, return last action
    return NUM_ACTIONS - 1;
}

// training algorithm
void RPSTrainer::train(int iterations){
    // vector containing the expected payoff of each action, given opponent play
    vector<double> actionUtility(NUM_ACTIONS, 0.0);

    // loop through iterations
    for (int i = 0; i < iterations; i++){
        /* ---- get actions ---- */

        // first compute current strategy
        strat = getStrat();
        // use to select actions
        int myAction = getAction(strat);
        int oppAction = getAction(oppStrat);


        /* ---- compute action utilities ----*/
        
        // initialize to 0
        fill(actionUtility.begin(), actionUtility.end(), 0.0);

        // Set the utilities based on opponent's action
        actionUtility[(oppAction + 1) % NUM_ACTIONS] = 1;    // Win
        actionUtility[oppAction] = 0;                         // Tie
        actionUtility[(oppAction + NUM_ACTIONS - 1) % NUM_ACTIONS] = -1; // Lose

        /* ---- accumulate action regrets ----*/

        for (int j = 0; j < NUM_ACTIONS; j++){
            regretSum[j] = max(regretSum[j] + actionUtility[j] - actionUtility[myAction], 0.0);
        }
        
    }
    
}

vector<double> RPSTrainer::getAvgStrategy() {
    vector<double> avgStrategy(NUM_ACTIONS, 0.0);
    double normalizingSum = 0;

    for (int i = 0; i < NUM_ACTIONS; i++){
        normalizingSum += stratSum[i];
    }

    for (int j = 0; j < NUM_ACTIONS; j++){
        if (normalizingSum > 0){
            avgStrategy[j] = stratSum[j] / normalizingSum;
        } else {
            avgStrategy[j] = 1.0 / NUM_ACTIONS;
        }
    }
    
    return avgStrategy;
}
