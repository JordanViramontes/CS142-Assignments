#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <memory>

using std::cout, std::cin, std::vector, std::set, std::ifstream, std::getline, std::string, std::endl, std::stoi;

// state struct
struct State {
    int score = -1;
    int bookPtr = -1;
    int currentShelf = -1;
    vector<vector<int>> shelf;
    vector<int> booksLeft;
    State(vector<vector<int>> &s, int b, int c, int sc) {
        shelf = s;
        bookPtr = b;
        currentShelf = c;
        score = sc;
    }
};

// used for making sure the set orders the boards by score
struct StateComparison {
    bool operator()(const State& a, const State& b) const { 
        return a.score <= b.score;
     }
};

void printState(State s) {
    cout << "score: " << s.score << endl;
    for (unsigned int i = 0; i < s.shelf.size(); i++) {
        if (s.shelf.at(i).size() == 0) cout << "-1";
        for (unsigned int j = 0; j < s.shelf.at(i).size(); j++) {
            cout << s.shelf.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

// for printing the overall set
void printSet(set<State, StateComparison> s) {
    for (auto i : s) {
        cout << i.score << ", ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
    string str = "";
    
    // get total books and level
    getline(cin, str);
    int totalBooks = -1;
    int maxLvl = -1;
    string parseStr = "";
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str.at(i) == ' ') {
            // i += 1;
            totalBooks = stoi(parseStr);
            parseStr = "";
            continue;
        }
        parseStr += str.at(i);
        if (i == str.size()-1) {
            maxLvl = stoi(parseStr);
        }
    }
    
    vector<int> books(totalBooks, -1);
    
    // parse input
    for (int i = 0; i < totalBooks; i++) {
        getline(cin, str);
        books.at(i) = stoi(str);
    }

    // init state and set
    set<State, StateComparison> states;
    vector<vector<int>> v(maxLvl);
    State init = State(v, 0, 0, 0);
    states.insert(init);
    bool foundSolution = false;

    // search
    while (!foundSolution) {
    // for (int i = 0; i < 3; i++) {
        // check if we have possible states
        if (states.size() == 0) {
            cout << "no more states left!" << endl;
            break;
        }

        // get most potential state
        State state = *states.begin(); // highest priority
        states.erase(states.begin()); // remove the board from the queue
        int bookPtr = state.bookPtr;

        // check if we're done
        if (state.bookPtr > totalBooks - 1) {
            cout << state.score << endl;
            foundSolution = true;
            break;
        }

        // generate new states
        vector<vector<int>> shelf = state.shelf;
        bool newShelf = false; // so that we dont have more states than needed
        for (unsigned int i = (unsigned int)state.currentShelf; i < shelf.size(); i++) {
            if (shelf.at(i).size() == 0 && newShelf) continue; // avoid unneccesary states
            else if (shelf.at(i).size() == 0) newShelf = true;

            // make new shelf
            vector<vector<int>> newShelf = shelf;
            newShelf.at(i).push_back(books.at(bookPtr));

            // make new score
            int score = 0;
            for (auto i : newShelf.at(i)) { score += i; }
            if (score < state.score) { score = state.score; }

            // make new state
            State newState = State(newShelf, bookPtr + 1, i, score);
            states.insert(newState); 
            // printState(newState);
        }

        // printSet(states);
    }



    return 0;
}