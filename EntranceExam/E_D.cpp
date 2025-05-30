#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::ifstream, std::pair, std::string, std::cout, std::endl, std::vector;

// global lookup table
vector<vector<int>> lookup;

void printLookupTable(string str1, string str2) {
    cout << endl;
    for (unsigned int i = 0; i < lookup.size(); i++) {
        // str1 header
        if (i == 0) {
            cout << "\t";
            for (unsigned int i = 0; i < str2.size(); i++) {
                cout << str2.at(i) << "\t";
            }
            cout << endl;
        }
        
        for (unsigned int j = 0; j < lookup.at(i).size(); j++) {
            if (j == 0 && i != 0) {
                cout << str1.at(i-1) << "  ";
            }
            else if (j == 0) cout << "   ";

            cout << lookup.at(i).at(j) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int findOptimalPath(const string &str1, const string &str2, int it1, int it2); // definition to avoid compiler errors

int compare(const string &str1, const string &str2, int it1, int it2, int dir) {
    // base case: we're at an edge (already calculated)
    if (it1 == 0 || it2 == 0) {
        switch(dir) {
            case(0): return lookup.at(it1-1).at(it2-1); break;
            case(1): return lookup.at(it1-1).at(it2); break;
            case(2): return lookup.at(it1).at(it2-1); break;
            default: return -1; break;
        }
    }

    // when dir equals 0: diag, 1: up, 2: left, this switch case will get num the optimal number in the direction specified
    int num = -1;
    switch(dir) {
        case (0):
            if (lookup.at(it1-1).at(it2-1) != -1) num = lookup.at(it1-1).at(it2-1); // look diag
            else num = findOptimalPath(str1, str2, it1-1, it2-1);
            break;
        case (1):
            if (lookup.at(it1-1).at(it2) != -1) num = lookup.at(it1-1).at(it2); // look up
            else num = findOptimalPath(str1, str2, it1-1, it2);
            break;
        case (2):
            if (lookup.at(it1).at(it2-1) != -1) num = lookup.at(it1).at(it2-1); // look left
            else num = findOptimalPath(str1, str2, it1, it2-1);
            break;
        default:
            return num;
            break;
    }    

    // compare and give new number
    if (str1.at(it1-1) != str2.at(it2-1)) num++;
    else num = lookup.at(it1-1).at(it2-1);
    return num;
}

// recursive DP algorithm
int findOptimalPath(const string &str1, const string &str2, int it1, int it2) {
    // check lookup table
    if (lookup.at(it1).at(it2) != -1) return lookup.at(it1).at(it2); // check table

    // base cases
    if (it1 == 0 || it2 == 0) { // at one of the edges
        return lookup.at(it1).at(it2);
    }

    // normal
    vector<int> possibles = { compare(str1, str2, it1, it2, 0), // diag
                              compare(str1, str2, it1, it2, 1), // up
                              compare(str1, str2, it1, it2, 2)  // left
                            };
    std::sort(possibles.begin(), possibles.end()); // sort to get the lowest option

    lookup.at(it1).at(it2) = possibles.at(0);
    // printLookupTable();
    return lookup.at(it1).at(it2);
}

int main(int argc, char* argv[]) {
    // ifstream file("input.txt");
    string str = "blank";
    string str1 = "";
    string str2 = "";
    getline(std::cin, str);
    int strLen = std::stoi(str);
    getline(std::cin, str1);
    getline(std::cin, str2);

    if (strLen == 0) { // edge case
        cout << "0";
        return 0;
    }

    // fill out lookup table
    lookup = vector<vector<int>>(strLen+1, vector<int>(strLen+1, -1)); 
    for (int i = 0; i < strLen+1; i++) {
        lookup.at(i).at(0) = i;
        lookup.at(0).at(i) = i;
    }

    cout << findOptimalPath(str1, str2, strLen, strLen);
    // printLookupTable(str1, str2);

    return 0;
}