#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
#include <memory>

using namespace std;

// globals
int n, timePenalty;
vector<vector<char>> mainBoard;
vector<vector<bool>> visitedCoords;


// holds the vector of the state + weight calculated by distance to finish line
struct Board {
    double distance;
    int time;
    int x = 0;
    int y = 0;

    Board(double d, int t, int ix, int iy) { 
        distance = d;
        time = t;
        x = ix;
        y = iy;
    }
};

// used for making sure the set orders the boards by weight where weight = moves + distance
struct BoardComparison {
    bool operator()(const shared_ptr<Board>& a, const shared_ptr<Board>& b) const { return (a->time + a->distance <= b->time + b->distance); }
};

double calculateDistance(int xa, int ya, int xb, int yb) {
    return sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
}

void printBoard(Board &b) {
    cout << "distance: " << b.distance << ", time: " << b.time << endl;
    for (auto i : mainBoard) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Implementation of A* Search
int searchBoard(shared_ptr<Board> initBoard, int fx, int fy) {
    // Queue used for A*, will automatically have the most promising board at the front
    set<shared_ptr<Board>, BoardComparison> boardQueue;

    boardQueue.insert(initBoard);

    int foundSolution = -1;
    while(foundSolution == -1) {
        shared_ptr<Board> board = *boardQueue.begin(); // highest priority
        boardQueue.erase(boardQueue.begin()); // remove the board from the queue
        int x = board->x;
        int y = board->y;

        vector<pair<int, int>> choices = {
            {-1, 0}, // up
            {1, 0}, // down
            {0, -1}, // left
            {0, 1} // right
        };

        // go through each choice
        for (auto i : choices) {
            int c1 = x + i.first;
            int c2 = y + i.second;

            // check choices
            if (c1 < 0 || c1 >= n) continue;
            if (c2 < 0 || c2 >= n) continue;
            if (visitedCoords[c1][c2] == true) continue;
            
            // check if we're done :)
            if (mainBoard[c1][c2] == 'f') {
                foundSolution = board->time + 1;
                break;
            }

            // make new boards
            int newTime = 1;
            if (mainBoard[c1][c2] == 'b') newTime = timePenalty + 1;

            shared_ptr<Board> newBoard = make_shared<Board>(calculateDistance(c1, c2, n-1, n-1), board->time+newTime, c1, c2);
            boardQueue.insert(newBoard);
            visitedCoords[c1][c2] = true;
        }

        // check if were done :(
        if (boardQueue.size() == 0) {
            return -1;
        }
    }

    return foundSolution;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    cin >> n >> timePenalty;

    // setup
    visitedCoords = vector<vector<bool>>(n, vector<bool>(n, false));
    mainBoard = vector<vector<char>>(n, vector<char>(n, '-'));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mainBoard[i][j];
        }
    }
    mainBoard[0][0] = 's';
    mainBoard[n-1][n-1] = 'f';
    shared_ptr<Board> initBoard = make_shared<Board>(calculateDistance(0, 0, n-1, n-1), 0, 0, 0);

    int totalTime = searchBoard(initBoard, n-1, n-1);
    cout << totalTime;
    
    return 0;
}