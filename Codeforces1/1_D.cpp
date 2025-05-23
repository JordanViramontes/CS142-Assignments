#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

using std::cout, std::cin, std::vector, std::ifstream, std::getline, std::string, std::endl, std::stoi, std::pair,
      std::pow, std::sqrt;

int startingNumber = -1;
vector<pair<vector<int>, int>> stateDictionary;

pair<vector<int>, int> checkDictionary(vector<int> moves) {
    for (auto i : stateDictionary) {
        if (moves == i.first) return i;
    }
    return pair<vector<int>, int>({}, -1);
}

pair<vector<int>, int> calculateMoves(vector<int> points, vector<int> moveList, int score, int moves) {
    // base case
    if (moves == 0) {
        return pair<vector<int>, int>({}, score);
    }

    // normal
    pair<vector<int>, int> bestState({}, -1);
    int bestMove = -1;
    for (unsigned int i = 0; i < points.size(); i++) {
        // check dictionary
        vector<int> newMoveList = moveList;
        newMoveList.push_back(i);
        sort(newMoveList.begin(), newMoveList.end());
        pair<vector<int>, int> test = checkDictionary(newMoveList);

        // if dictionary turns up nothing
        pair<vector<int>, int> current({}, -1);
        if (test.second == -1) {
            // calculate new score
            int newScore = score - points.at(i);
            if (newScore < 0) newScore = startingNumber;
            current = calculateMoves(points, newMoveList, newScore, moves -1);
            // cout << "current: " << i << ", p: " << points.at(i) << ", s: " << newScore << endl;
        }
        else {
            current = test;
        }

        // cout << "new score: " << newScore << endl;
        if (bestState.second == -1) {
            bestState = current;
            bestMove = i;
        }
        else if (current.second < bestState.second) {
            bestState = current;
            bestMove = i;
        }
    }

    bestState.first.push_back(bestMove);

    return bestState;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    // get dart info
    int sectors = -1;
    scanf("%d %d", &sectors, &startingNumber);

    // get points
    vector<int> points = {0};
    for (int i = 0; i < sectors; i++) {
        int p;
        scanf("%d", &p);
        points.push_back(p);
    }

    // vector<int> moves;
    pair<vector<int>, int> fin = calculateMoves(points, {}, startingNumber, 4);
    // cout << "final: " << fin.score << endl;
    for (auto i : fin.first) {
        cout << i << " ";
    }
    // cout << endl;
    
    
    return 0;
}