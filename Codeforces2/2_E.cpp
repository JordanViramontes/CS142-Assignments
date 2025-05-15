#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

// for inserting the set

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    // parse
    int n;
    cin >> n;

    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; i++) {
        pair<int, int> cow;
        cin >> cow.first >> cow.second;
        cows[i] = cow;
    }

    unordered_map<int, int> dp;
    dp.insert(pair<int, int>(0, 0));

    for (int i = 0; i < n; i++) {
        unordered_map<int, int> tempDP;

        // iterate over dp and make a whole bunch of new states yippie
        for (auto j : dp) {
            int newS = j.first + cows[i].first;
            int newF = j.second + cows[i].second;

            if (!tempDP.count(newS) || tempDP[newS] < newF) {
                tempDP[newS] = newF;
            }
        }

        // update the real dp with the temp dp data
        for (auto j : tempDP) {
            if (!dp.count(j.first) || dp[j.first] < j.second) {
                dp[j.first] = j.second;
            }
        }
    }

    // cout << "DP STUFF" << endl;
    // get highest
    int highest = 0;
    for (auto i : dp) {
        // cout << "<" << i.first << ", " << i.second << ">, " << endl;
        if (i.first < 0 || i.second < 0) {
            continue;
        }
        if (i.first + i.second > highest) {
            // cout << "new highest!" << endl;
            highest = i.second + i.first;
        }
    }
    // cout << endl;
    cout << highest;
}