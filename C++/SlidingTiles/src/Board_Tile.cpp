#include "Board_Tile.h"

/**
Default Constructor
*/
Board_Tile::Board_Tile() {
}
/**
Overload constructor. Takes a string with the start
Configuration.
*/
Board_Tile::Board_Tile(const string& configuration) {
    config = configuration;
}

Board_Tile::~Board_Tile() {
}

/**
Return the number of moves since the start configuration
*/
int Board_Tile::numMoves() {
    int num;
    num = movesFromStart.length();
    return num;
}
/**
Print the Board Tile in a nice way
*/
void Board_Tile::printConfiguration() {
    int counter = 0;
    for (int i = 0; i < config.length(); i++) {
        if (counter > 2)
        {
         counter = 0;
         cout << endl;
        }
        counter++;
        std::cout << config[i] << " ";
    }
    cout << endl;
}
/**
Find and return the index for 0.
Use in nextConfiguration
*/
int Board_Tile::find0(string grid) {
    int index = 0;
    for (int i = 0; i < grid.length(); i++){
        if (grid[i] == '0')
            index = i;
    }
    return index;
}
/**
Return the configuration for the Board Tile
*/
string Board_Tile::getConfiguration() const {
    return config;
}

/**
Calculates Manhattan Distance from the configuration to the Goal
Configuration
*/
int Board_Tile::Manhattan_Distance(const Board_Tile& goalConfig) {
    int sum = 0;
    Point points1[9];
    Point points2[9];

    string goal = goalConfig.config;

    vector<int> xPoint1;
    vector<int> xPoint2;
    vector<int> yPoint1;
    vector<int> yPoint2;

    int xCounter = 0, yCounter = 0;

    for (int i = 0; i < config.length(); i++) {
        int tmp;
        tmp = (int)config[i] - 48;

        if( xCounter > 2)
            xCounter = 0;
        if (yCounter > 2) {
            xCounter++;
            yCounter = 0;
        }
        points1[tmp].x = xCounter;
        points1[tmp].y = yCounter;
        yCounter++;
    }
    xCounter = 0; yCounter = 0;
    for (int i = 0; i < goal.length(); i++) {
        int tmp;
        tmp = (int)goal[i] - 48;

        if( xCounter > 2)
            xCounter = 0;
        if (yCounter > 2) {
            xCounter++;
            yCounter = 0;
        }
        points2[tmp].x = xCounter;
        points2[tmp].y = yCounter;
        yCounter++;
    }


    for (int i = 1; i < 9; i++) {
        sum += (abs(points1[i].x - points2[i].x) + abs(points1[i].y - points2[i].y));
        /**
        cout << "X1: " << points1[i].x << ", Y1: " << points1[i].y << endl;
        cout << "X2: " << points2[i].x << ", Y2: " << points2[i].y << endl;
        cout << "The sum at: " << i << " is " << sum << endl;
        */
    }
    //numMove = numMove + sum;

    return sum;
}

/**
Generates the all the possible next configurations.
Check the position of 0 in order to decide which new
configurations generate.
*/
vector<Board_Tile> Board_Tile::nextConfigs() {
    vector<Board_Tile> nextMoves;
    string tmpgrid = config;
    string tmp1 = tmpgrid;
    string tmp2 = tmpgrid;
    string tmp3 = tmpgrid;
    string tmp4 = tmpgrid;
    int x = find0(tmpgrid);
    char tmp;
    Board_Tile temp;

    switch (x) {

    case 0 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp = tmp1[0];
        tmp1[0] = tmp1[3];
        tmp1[3] = tmp;

        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'D';
        nextMoves.push_back(temp);

        tmp = tmp2[0];
        tmp2[0] = tmp2[1];
        tmp2[1] = tmp;

        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'R';
        nextMoves.push_back(temp);

        break;

    case 1 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp3 = tmpgrid;
        tmp = tmp1[1];
        tmp1[1] = tmp1[0];
        tmp1[0] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'L';
        nextMoves.push_back(temp);

        tmp = tmp2[1];
        tmp2[1] = tmp2[4];
        tmp2[4] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'D';
        nextMoves.push_back(temp);

        tmp = tmp3[1];
        tmp3[1] = tmp3[2];
        tmp3[2] = tmp;
        temp = Board_Tile(tmp3);
        temp.movesFromStart = movesFromStart + 'R';
        nextMoves.push_back(temp);

        break;

    case 2 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp = tmp1[2];
        tmp1[2] = tmp1[1];
        tmp1[1] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'L';
        nextMoves.push_back(temp);

        tmp = tmp2[2];
        tmp2[2] = tmp2[5];
        tmp2[5] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'D';
        nextMoves.push_back(temp);

        break;

    case 3 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp3 = tmpgrid;
        tmp = tmp1[3];
        tmp1[3] = tmp1[0];
        tmp1[0] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'U';
        nextMoves.push_back(temp);

        tmp = tmp2[3];
        tmp2[3] = tmp2[4];
        tmp2[4] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'R';
        nextMoves.push_back(temp);

        tmp = tmp3[3];
        tmp3[3] = tmp3[6];
        tmp3[6] = tmp;
        temp = Board_Tile(tmp3);
        temp.movesFromStart = movesFromStart + 'D';
        nextMoves.push_back(temp);

        break;

    case 4 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp3 = tmpgrid;
        tmp4 = tmpgrid;

        tmp = tmp1[4];
        tmp1[4] = tmp1[1];
        tmp1[1] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'U';
        nextMoves.push_back(temp);

        tmp = tmp2[4];
        tmp2[4] = tmp2[3];
        tmp2[3] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'L';
        nextMoves.push_back(temp);

        tmp = tmp3[4];
        tmp3[4] = tmp3[5];
        tmp3[5] = tmp;
        temp = Board_Tile(tmp3);
        temp.movesFromStart = movesFromStart + 'R';
        nextMoves.push_back(temp);

        tmp = tmp4[4];
        tmp4[4] = tmp4[7];
        tmp4[7] = tmp;
        temp = Board_Tile(tmp4);
        temp.movesFromStart = movesFromStart + 'D';
        nextMoves.push_back(temp);

        break;

    case 5 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp3 = tmpgrid;
        tmp = tmp1[5];
        tmp1[5] = tmp1[2];
        tmp1[2] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'U';
        nextMoves.push_back(temp);

        tmp = tmp2[5];
        tmp2[5] = tmp2[4];
        tmp2[4] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'L';
        nextMoves.push_back(temp);

        tmp = tmp3[5];
        tmp3[5] = tmp3[8];
        tmp3[8] = tmp;
        temp = Board_Tile(tmp3);
        temp.movesFromStart = movesFromStart + 'D';
        nextMoves.push_back(temp);

        break;

    case 6 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp = tmp1[6];
        tmp1[6] = tmp1[3];
        tmp1[3] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'U';
        nextMoves.push_back(temp);

        tmp = tmp2[6];
        tmp2[6] = tmp2[7];
        tmp2[7] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'R';
        nextMoves.push_back(temp);

        break;

    case 7 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp3 = tmpgrid;
        tmp = tmp1[7];
        tmp1[7] = tmp1[6];
        tmp1[6] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'L';
        nextMoves.push_back(temp);

        tmp = tmp2[7];
        tmp2[7] = tmp2[4];
        tmp2[4] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'U';
        nextMoves.push_back(temp);

        tmp = tmp3[7];
        tmp3[7] = tmp3[8];
        tmp3[8] = tmp;
        temp = Board_Tile(tmp3);
        temp.movesFromStart = movesFromStart + 'R';
        nextMoves.push_back(temp);

        break;

    case 8 :
        tmp1 = tmpgrid;
        tmp2 = tmpgrid;
        tmp = tmp1[8];
        tmp1[8] = tmp1[7];
        tmp1[7] = tmp;
        temp = Board_Tile(tmp1);
        temp.movesFromStart = movesFromStart + 'L';
        nextMoves.push_back(temp);

        tmp = tmp2[8];
        tmp2[8] = tmp2[5];
        tmp2[5] = tmp;
        temp = Board_Tile(tmp2);
        temp.movesFromStart = movesFromStart + 'U';
        nextMoves.push_back(temp);

        break;

    }

    return nextMoves;
}
