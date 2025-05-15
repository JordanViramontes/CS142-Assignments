#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <set>

using namespace std;

int maxTime = 0;
int n = 0;

unordered_map<string, int> dp;

struct Coord {
    int row = 0;
    int col = 0;

    Coord(int r, int c) {
        row = r;
        col = c;
    }
};

struct Node {
    vector<Coord> coords;
    bool hasActivity = false;

    Node() { }
    
    void insert(int r, int c) {
        coords.push_back(Coord(r, c));
        hasActivity = true;
    }

    void print() {
        for (auto i : coords) {
            cout << "<" << i.row << ", " << i.col << ">, ";
        }
    }
};

// recursively move on the board
int traverseGame(int time, int score, int row, int col, vector<Node> &popcorns, vector<Node> &boulders) {
    if (time > maxTime + 1) {
        // cout << "CHECK: " << score << endl;
        return score;
    }


    // memoization
    string key = to_string(time) + "," + to_string(row) + "," + to_string(col) + "," + to_string(score);
    if (dp.count(key)) return dp[key];


    // popcorns
    int newScore = score;
    for (auto i : popcorns[time].coords) {
        if (i.row == row && i.col == col) {
            // cout << "POP at: " << time << "; <" << i.row << ", " << i.col << ">\t";
            // cout << "check: " << newScore;
            newScore += 1;
            // cout << " -> " << newScore << endl;
        }
    }

    // boulders
    for (auto i : boulders[time].coords) {
        if (i.row == row && i.col == col) {
            // cout << "BOL at: " << time << "; <" << i.row << ", " << i.col << ">\t";
            // cout << "check: " << newScore;
            newScore = newScore / 2;
            // cout << " -> " << newScore << endl;
        }
    }

    // next moves
    int s = -1, u = -1, d = -1, l = -1, r = -1;
    s = traverseGame(time + 1, newScore, row, col, popcorns, boulders); 
    if (row - 1 >= 0) { u = traverseGame(time + 1, newScore, row - 1, col, popcorns, boulders); }
    if (row + 1 < n) { d = traverseGame(time + 1, newScore, row + 1, col, popcorns, boulders); }
    if (col - 1 >= 0) { l = traverseGame(time + 1, newScore, row, col - 1, popcorns, boulders); }
    if (col + 1 < n) { r = traverseGame(time + 1, newScore, row, col + 1, popcorns, boulders); }

    int mapScore = max(s, max(u, max(d, max(l, r))));
    dp[key] = mapScore;
    return mapScore;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    int p, b;
    cin >> n >> p >> b;

    int sR, sC;
    cin >> sR >> sC;

    // vector<Node> popcorns(boundTime);
    vector<tuple<int, int, int>> popcornsInit;
    for (int i = 0; i < p; i++) {
        int r, c, t;
        cin >> r >> c >> t;

        if (t > maxTime) maxTime = t;
        popcornsInit.push_back(tuple<int, int, int>(r, c, t));
    }

    // vector<Node> boulders(boundTime);
    vector<tuple<int, int, int>> bouldersInit;
    for (int i = 0; i < b; i++) {
        int r, c, t;
        cin >> r >> c >> t;

        if (t > maxTime) maxTime = t;
        bouldersInit.push_back(tuple<int, int, int>(r, c, t));
    }

    // real popcorns and boulders
    vector<Node> popcorns(maxTime + 2);
    vector<Node> boulders(maxTime + 2);
    // vector<Node> popcorns(100);
    // vector<Node> boulders(100);

    for (auto i : popcornsInit) {
        popcorns[get<2>(i)].insert(get<0>(i), get<1>(i));
    }

    for (auto i : bouldersInit) {
        boulders[get<2>(i)].insert(get<0>(i), get<1>(i));
    }

    // for (int i = 0; i < maxTime + 2; i++) {
    //     dp.push_back(dpNode(n));
    // }

    // cout << "check: " << dp[0].map[0][0] << endl;

    // cout << "start spot: " << sR << ", " << sC << endl;
    // cout << "n: " << n << endl;
    // cout << "maxtime: " << maxTime << endl;

    // cout << "POPCORNS: ";
    // for (unsigned int i = 0; i < popcorns.size(); i++) {
    //     if (popcorns[i].hasActivity) {
    //         cout << i << ":{";
    //         popcorns[i].print();
    //         cout << "}, ";
    //     }
    // }
    // cout << endl;

    // cout << "BOULDERS: ";
    // for (unsigned int i = 0; i < boulders.size(); i++) {
    //     if (boulders[i].hasActivity) {
    //         cout << i << ":{";
    //         boulders[i].print();
    //         cout << "}, ";
    //     }
    // }
    // cout << endl;

    // maxTime = 2;
    int ans = traverseGame(0, 0, sR, sC, popcorns, boulders);
    cout << ans;




    return 0;
}