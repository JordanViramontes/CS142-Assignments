#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

struct Node {
    int x = 0;
    int y = 0;

};

int row, col;
vector<shared_ptr<Node>> room;

void findCandy(int r, int c) {
    cout << "cell: [" << r << ", " << c << "], " << room[r][c] << endl;
    vector<pair<int, int>> choices = {
        {-1, 0}, // up
        {1, 0}, // down
        {0, -1}, // left
        {0, 1} // right
    };

    int best = -1;
    for (auto i : choices) {
        pair<int, int> coords = { r + i.first, c + i.second };
        if (r + i.first < 0 || r + i.first >= row) continue;
        if (c + i.second < 0 || c + i.second >= row) continue;
        cout << "coord: " << coords.first << ", " << coords.second << endl;

        // if (best)
    }

}

int main(int argc, char* argv[]) {
    ifstream cin("input.txt");
    
    // parse
    cin >> row >> col;
    
    room = vector<vector<int>>(row, vector<int>(col, -1));
    // candies = vector<vector<int>>(row, vector<int>(col, -1));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> room[i][j];
        }
    }

    for (auto i : room) {
        for (auto j : i) {
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << endl;

    for (auto i : candies) {
        for (auto j : i) {
            cout << j << ", ";
        }
        cout << endl;
    }
    cout << endl;

    findCandy(0, 0);

    

    return 0;
}