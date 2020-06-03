#ifndef BOARD_TILE_H
#define BOARD_TILE_H

#include <iostream>
#include <vector>

using namespace std;

/**
Special data structure to hold the x and y
position of the elements in the configuration
string
*/
struct Point {
	int x;
	int y;
};

class Board_Tile
{
public:
    Board_Tile();
    Board_Tile(const string&);
    virtual ~Board_Tile();

    /**
    Generate all the possible next Configurations
    */
    vector<Board_Tile> nextConfigs();

    /**
    Return the number of moves since the start Configuration
    */
    int numMoves();

    /**
    Calculate Manhattan Distance to the Goal Configuration
    */
    int Manhattan_Distance(const Board_Tile& goalConfig);

    /**
    Print the Board Tile in a nice format
    */
    void printConfiguration();

    /**
    Return the configuration of the Board Tile
    */
    string getConfiguration() const;

    /**
    Keep Record of the moves since the start configuration
    It is public for easy access reasons.
    */
    string movesFromStart;

    /**
    Hold the number D. As D(C) = A(C) + E(C).
    It is the most important value of the Board Tile.
    A* Algorithm would work without it.
    */
    int numMove = 0;

private:

    /**
    Find and return
    */
    int find0(string grid);

    /**
    Configuration of Board Tile
    */
    string config;

};

#endif // BOARD_TILE_H
