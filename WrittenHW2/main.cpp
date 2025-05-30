#include <iostream>
#include <vector>

using namespace std;

vector<int> A = {5, 1, 3, 9, 6, 2, 4, 8};
vector<vector<int>> f;

int search(int i, int j) {
    // memoization
    if (f.at(i).at(j) != -1) {
        return f.at(i).at(j);
    }

    // base case 1 element
    if (i == j) {
        f.at(i).at(j) = A.at(i);
        return A.at(i);
    }

    // base case 2 element
    if (i+1 == j) {
        int n = max(A.at(i), A.at(i+1));
        f.at(i).at(j) = n;
        return n;
    }

    // recursion
    return max(
        A.at(i) + min(search(i+2, j), search(i+1, j-1)),
        A.at(j) + min(search(i+1, j-1), search(i, j-2))
    );
}


int main(int argc, char* argv[]) {
    f = vector<vector<int>>(A.size(), vector<int>(A.size(), -1));
    cout << "TOTAL: " << search(0, A.size()-1);

    return 0;
}