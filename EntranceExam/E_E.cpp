#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>

using std::pow, std::ifstream, std::pair, std::string, std::cout, std::endl, std::vector, std::set;

// holds the vector of the state + weight calculated by distance to finish line
struct Board {
    vector<vector<char>> board;
    double distance;
    int moves;
    pair<int, int> position;
    Board(vector<vector<char>> b, double d, int m, pair<int, int> p) { board = b; distance = d; moves = m; position = p; }
};

// used for making sure the set orders the boards by weight where weight = moves + distance
struct BoardComparison {
    bool operator()(const Board& a, const Board& b) const { return (a.moves + a.distance <= b.moves + b.distance); }
};

double calculateDistance(pair<int, int> pos, pair<int, int> finish) {
    return sqrt(pow(pos.first - finish.first, 2) + pow(pos.second - finish.second, 2));
}

// use to calculate which moves are possible out of 8 and return as a vector
vector<pair<int, int>> calculateMoves(Board board) {
    int c1 = board.position.first;
    int c2 = board.position.second;
    vector<pair<int, int>> possibleMoves = 
    { { c1+2, c2+1 }, { c1+2, c2-1 }, { c1-2, c2+1 }, { c1-2, c2-1 }, 
      { c1+1, c2+2 }, { c1+1, c2-2 }, { c1-1, c2+2 }, { c1-1, c2-2 } };

    // weed out
    vector<pair<int, int>> finalMoves;
    for (unsigned int i = 0; i < possibleMoves.size(); i++) {
        c1 = possibleMoves.at(i).first;
        c2 = possibleMoves.at(i).second;

        // check bounds
        if (c1 < 0 || c2 < 0 || c1 >= 8 || c2 >= 8) {
            continue;
        }

        // check availability
        if (board.board.at(c1).at(c2) == 'x' || board.board.at(c1).at(c2) == 's' || board.board.at(c1).at(c2) == 'o') {
            continue;
        }

        // we good
        finalMoves.push_back(possibleMoves.at(i));
    }
    return finalMoves;
}

// Implementation of A* Search
int searchBoard(Board initBoard, pair<int, int> finish) {
    // Queue used for A*, will automatically have the most promising board at the front
    set<Board, BoardComparison> boardQueue;

    boardQueue.insert(initBoard);

    int foundSolution = -1;
    while(foundSolution == -1) {
        Board board = *boardQueue.begin(); // highest priority
        boardQueue.erase(boardQueue.begin()); // remove the board from the queue
        int c1 = board.position.first;
        int c2 = board.position.second;

        vector<pair<int, int>> possibleMoves = calculateMoves(board);

        // check if were done :(
        if (possibleMoves.size() == 0 && boardQueue.size() == 0) {
            return -1;
        }

        // iterate over possible moves
        for (unsigned int i = 0; i < possibleMoves.size(); i++) {
            c1 = possibleMoves.at(i).first;
            c2 = possibleMoves.at(i).second;

            // check if we're done
            if (board.board.at(c1).at(c2) == 'f') {
                foundSolution = board.moves+1;
                break;
            }
            
            // make a new board and add it to the queue
            pair<int, int> newCoords(possibleMoves.at(i).first, possibleMoves.at(i).second);
            Board newBoard = Board(board.board, calculateDistance(newCoords, finish), board.moves+1, newCoords);
            newBoard.board.at(newCoords.first).at(newCoords.second) = 'o';
            boardQueue.insert(newBoard);
        }
    }

    return foundSolution;
}

int main(int argc, char* argv[]) {
    // ifstream file("input.txt");

    // setup
    vector<vector<char>> baseVector(8, vector<char>(8, '_'));
    vector<string> inputs;
    string str = "";
    bool shouldContinue = true;
    int boardCnt = 1;

    // get inputs
    while(getline(std::cin, str) && str != "-1") {
        inputs.push_back(str);
    }

    // mostly this loop parses, continues until it reads a '-1'
    for (unsigned int i = 0; i < inputs.size(); i+=3) {
        string str1 = inputs.at(i);
        string str2 = inputs.at(i+1);
        string str3 = inputs.at(i+2);

        // Check for a -1
        int takenSquares = stoi(str1);
        if (takenSquares == -1) { 
            shouldContinue = false;
            break;
        }

        if (boardCnt != 1) cout << endl; // used for whitespace stuff

        // board vector
        vector<vector<char>> initVector = baseVector;

        // get coords for taken squares
        for (unsigned int i = 0, k = 0; i < takenSquares; i++) {
            int coord1 = str2.at(k) - '0' - 49;
            int coord2 = str2.at(k+1) - '0' - 1;
            initVector.at(coord1).at(coord2) = 'x';
            k += 3; // update counter for string parser
        }

        // get start and finish
        pair<int, int> start(str3.at(0) - '0' - 49, str3.at(1) - '0' - 1);
        pair<int, int> finish(str3.at(3) - '0' - 49, str3.at(4) - '0' - 1);
        initVector.at(start.first).at(start.second) = 's';
        initVector.at(finish.first).at(finish.second) = 'f';

        // setup board and calculate
        Board initBoard = Board(initVector, calculateDistance(start, finish), 0, start);
        int totalMoves = searchBoard(initBoard, finish);

        if (totalMoves == -1) cout << "Board " << boardCnt << ": not reachable";
        else cout << "Board " << boardCnt << ": " << totalMoves << " moves";
        boardCnt++;
    }
    
    return 0;
}