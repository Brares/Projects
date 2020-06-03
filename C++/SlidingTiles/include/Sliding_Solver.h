#ifndef SLIDING_SOLVER_H
#define SLIDING_SOLVER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <Board_Tile.h>

using namespace std;

/**
This is a structure that implements the
operator overlading for the Priority Queue
to work
*/
struct CompareMoves {
    bool operator()(Board_Tile const& b1, Board_Tile const& b2)
    {
        return b1.numMove > b2.numMove;
    }
};

class Sliding_Solver
{
    public:

        /**
        Overloaded Constructor
        */
        Sliding_Solver(const string& startConfig);

        virtual ~Sliding_Solver();

        /**
        A* Algorithm
        */
        Board_Tile Solve_Puzzle();

        /**
        Set a Board Tile with the Goal Configuration
        */
        void setGoal(string s);

    private:
        /**
        MinHeap for Board Tiles
        */
        priority_queue<Board_Tile, vector<Board_Tile>, CompareMoves> tileQueue;

        Board_Tile startConfig;
        Board_Tile goal;
};

#endif // SLIDING_SOLVER_H
