#include <iostream>
#include <stdio.h>
#include "Node.h"
#include "Board_Tile.h"
#include "Sliding_Solver.h"

using namespace std;

int main(){

    cout << "Welcome to Sliding Tile Solver" << endl << endl;

    cout << "Enter Start Board: ";
    string startConfig;
    cin >> startConfig;

    cout << "Enter Goal Board: ";
    string goalConfig;
    cin >> goalConfig;

    Board_Tile test(startConfig);
    Board_Tile endTest(goalConfig);

    cout << endl << "Start Configuration: " << endl;
    test.printConfiguration();

    cout << endl << "Goal Configuration: " << endl;
    endTest.printConfiguration();


    cout << endl << "Innitial Manhattan: " << test.Manhattan_Distance(endTest) << endl;

    Sliding_Solver solver(startConfig);
    solver.setGoal(goalConfig);

    Board_Tile finalBoard = solver.Solve_Puzzle();

    cout << endl << "Number of Moves: " << finalBoard.numMoves() << endl;
    cout << endl << "Solution: " << finalBoard.movesFromStart << endl;


    return 0;
}
