#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int search(int i, int j, vector<int> &str, vector<int> &costs, vector<vector<int>> &minCost) {
    // base cases 
    if (minCost[i][j] != -1) { return minCost[i][j]; }
    if (i > j) { return 0; } // if out of bounds, get 0 (diag edge case)

    // // if i and j are the same, we don't need to insert anything, pull diagonal
    if (str[i] == str[j]) {
        // cout << "match!: " << i << ", " << j << "; <" << str[i] << ", " << str[j] << ">" << endl;
        int c = search(i+1, j-1, str, costs, minCost);
        minCost[i][j] = c;
        return c;
    }

    // cout << "not match!: " << i << ", " << j << "; <" 
    //      << str[i] << ", " << str[j] << ">" 
    //      << ", costs: (" << costs[str[i]] << ", " << costs[str[j]] << ")"
    //      << endl;
    
    // // else, insert 1 and pull from left and bottom
    int c = min(
        search(i+1, j, str, costs, minCost) + costs[str[i]], // choose i+1 value
        search(i, j-1, str, costs, minCost) + costs[str[j]] // choose j-1 value
    );

    // cout << i << ", " << j << "\tCHOSE: " << c << endl;
    minCost[i][j] = c;
    return c;
}

void printBoard(vector<vector<int>> &minInsertions) {
    for (auto i : minInsertions) {
        for (auto j : i) {
            cout << j << ",\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    // parse inputs
    int n, k;
    cin >> n >> k;

    // string of 1 check
    if (n == 1) {
        cout << 0;
        return 0;
    }

    vector<int> costs(k);
    for (int i = 0; i < k; i++) {
        cin >> costs[i];
    }

    vector<int> str(n);
    string c;
    cin >> c;
    for (unsigned int i = 0; i < c.size(); i++) {
        str[i] = c[i] - 'a';
    }

    // tracks the minimum amount of cost for string[i..j]
    // we know that string[i][i] is a palendrome, so the diagonal across the table will be 0
    vector<vector<int>> minCost(n, vector<int>(n, -1));
    for (unsigned int i = 0; i < n; i++) {
        minCost[i][i] = 0;
    }

    int ans = search(0, n-1, str, costs, minCost);
    cout << ans;

    

    return 0;
}