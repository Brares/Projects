#include "Sliding_Solver.h"

/**
Overloaded constructor that takes a string representing
the initial configuration ofa Board Tile
*/
Sliding_Solver::Sliding_Solver(const string& start) {
    startConfig = Board_Tile(start);
}

Sliding_Solver::~Sliding_Solver() {
}

/**
Set a Board Tile with the final configuration
*/
void Sliding_Solver::setGoal(string s) {
    goal = Board_Tile(s);
}

/**
A* Algorithm.
*/
Board_Tile Sliding_Solver::Solve_Puzzle() {
    int originalDistance = startConfig.Manhattan_Distance(goal);
    int goalNum = goal.Manhattan_Distance(goal);
    int d;

    vector<string> aux;

    startConfig.numMove = originalDistance;
    tileQueue.push(startConfig);
    aux.push_back(startConfig.getConfiguration());


    while (!tileQueue.empty()) {
        Board_Tile tmp = tileQueue.top();
        if (tmp.getConfiguration() == goal.getConfiguration())
            return tmp;

        string s = tmp.getConfiguration();
        tileQueue.pop();

        vector<Board_Tile> tmpBoards = tmp.nextConfigs();
        for (int i = 0; i < tmpBoards.size(); i++) {

            int newDistance = tmpBoards[i].Manhattan_Distance(goal);
            d = tmp.numMove + newDistance;
            s = tmpBoards[i].getConfiguration();

            if (std::find(aux.begin(), aux.end(), s) == aux.end()) {
                if (newDistance <= originalDistance) { // Useless If Statement. I does not do anything important
                    Board_Tile tmp2 = tmpBoards[i];
                    tmp2.numMove = d;
                    tileQueue.push(tmp2);
                    aux.push_back(s);
                }
            }
        }
    }
    return goal; // Return the Goal Configuration in case something bad happen.
}

