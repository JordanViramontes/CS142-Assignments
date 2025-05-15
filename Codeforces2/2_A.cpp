#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int search(int i, int j, int &row, int &col, vector<vector<int>> &board, vector<vector<int>> &knownPaths) {
    // memoization base case
    if (knownPaths[i][j] != -1) {
        return knownPaths[i][j];
    }

    int x = board[i][j];
    int u = -1, d = -1, l = -1, r = -1;

    if (i - 1 >= 0) { // up
        u = board[i-1][j];
        if (u >= x) u = -1;
    }
    if (i + 1 <= row - 1) { // down
        d = board[i+1][j];
        if (d >= x) d = -1;
    }
    if (j - 1 >= 0) { // left
        l = board[i][j-1];
        if (l >= x) l = -1;
    }
    if (j + 1 <= col - 1) { // right
        r = board[i][j+1];
        if (r >= x) r = -1;
    }

    // base case! all 4 directions are not workable so we return 1
    if (u == -1 && d == -1 && l == -1 && r == -1) {
        knownPaths[i][j] = 1;
        return 1;
    }

    // get the choices for each possible side
    int highest = -1;
    if (u != -1) { 
        int choice = search(i-1, j, row, col, board, knownPaths) + 1; 
        if (choice > highest) highest = choice;
    }
    if (d != -1) { 
        int choice = search(i+1, j, row, col, board, knownPaths) + 1; 
        if (choice > highest) highest = choice;
    }
    if (l != -1) { 
        int choice = search(i, j-1, row, col, board, knownPaths) + 1; 
        if (choice > highest) highest = choice;
    }
    if (r != -1) { 
        int choice = search(i, j+1, row, col, board, knownPaths) + 1; 
        if (choice > highest) highest = choice;
    }

    // set memoization and return
    knownPaths[i][j] = highest;
    return highest;
}

void printBoard(vector<vector<int>> &board) {
    for (auto i : board) {
        for (auto j : i) {
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    int row, col, i, j;
    cin >> row >> col;
    vector<vector<int>> knownPaths = vector<vector<int>>(row, vector<int>(col, -1));
    vector<vector<int>> board = vector<vector<int>>(row, vector<int>(col));
    
    // parse
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            cin >> board[i][j];
        }
    }

    // go through all board members and get the highest score
    int highest = 0;
    for (i = 0; i < board.size(); i++) {
        for (j = 0; j < board[i].size(); j++) {
            int score = search(i, j, row, col, board, knownPaths);
            if (score > highest) highest = score;
        }
    }

    cout << highest;

    return 0;
}