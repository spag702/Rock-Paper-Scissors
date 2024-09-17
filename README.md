Hello! This is my first personal project and therefore my first project
ever published to GitHub.

In this program, I use counterfactual regret minimization to calculate
a strategy for optimal Rock-Paper-Scissors play. It should be obvious that
I did not come up with this algorithm, and I give all credit to Todd W. 
Neller and Marc Lanctot for their amazing research paper, "An Introduction to Counterfactual Regret Minimization". In this program, I essentially follow the steps provided by Lanctot and Neller in Chapter 2. 

Commit - Sep 17, 2024 00:45 
    Folder first uploaded.
    Contains the RPSTrainer class which implements the CFR algorithm.
    Odd "problem" occurs where theoretical strategy output should be close to 
    0.3 for each action, yet actual output randomly favors a single actoin. The skewed output is likely due to the accumulation of negative regrets, causing the strategy to converge to a single action. 
    Introduced ability to play against the computer.


Commit - Sep 17, 2024 01:20
    Changed the training function, preventing negative regrets and ensuring regretSum[j] is always non-negative. This fixed the skewed action profiles.
    Added README file.
    
