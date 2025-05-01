#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <memory>

using std::cout, std::cin, std::vector, std::set, std::string, std::endl, std::shared_ptr, std::make_shared;

// state struct
struct State {
    int row = 0;
    int rowScore = 0;
    int score = 0;
    int bookPtr = 0;
    State(int r, int rS, int s, int b) {
        row = r;
        rowScore = rS;
        score = s;
        bookPtr = b;
    }
};

struct Node {
    shared_ptr<State> left = nullptr;
    shared_ptr<State> right = nullptr;
};

// used for making sure the set orders the boards by score
struct StateComparison {
    bool operator()(const shared_ptr<State>& a, const shared_ptr<State>& b) const {
        if (a->score != b->score) return a->score < b->score;
        if (a->bookPtr != b->bookPtr) return a->bookPtr > b->bookPtr;
        return a->row < b->row;
    }
};

void printState(shared_ptr<State> state) {
    cout << "score: " << state->score << endl;
    cout << "row: " << state->row << endl;
    cout << "rowScore: " << state->rowScore << endl;
    cout << "newbook: " << state->bookPtr << endl << endl;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
    string str = "";
    
    // get total books and level
    int totalBooks = 0;
    int maxLvl = 0;
    string parseStr = "";
    cin >> totalBooks >> maxLvl;
    
    vector<int> books = vector<int>(totalBooks, 0);
    
    // parse input
    for (int i = 0; i < totalBooks; i++) {
        int book = 0;
        cin >> book;
        books.at(i) = book;
    }

    // init state and set
    set<shared_ptr<State>, StateComparison> states;
    shared_ptr<State> init = make_shared<State>(0, 0, 0, 0);
    bool initStateFlag = true;
    states.insert(init);
    bool foundSolution = false;

    // search
    while (!foundSolution) {
    // for (int i = 0; i < 3; i++) {
        // check if we have possible states
        if (states.empty()) {
            cout << "no answer" << endl;
            break;
        }

        // get most potential state
        shared_ptr<State> state = *states.begin(); // highest priority
        states.erase(states.begin()); // remove the board from the queue
        int bookPtr = state->bookPtr;

        // check if we're done
        if (state->bookPtr > totalBooks - 1) {
            cout << state->score << endl;
            foundSolution = true;
            break;
        }

        // make new state on current row
        int bookScore = books.at(state->bookPtr);
        int rowScore = state->rowScore + bookScore;
        int score = state->score;
        if (rowScore > state->score) score = rowScore;
        
        shared_ptr<State> newState = make_shared<State>(state->row, rowScore, score, state->bookPtr + 1);
        states.insert(newState);

        // check if we're at first loop
        if (initStateFlag) {
            initStateFlag = false;
            continue;
        }
        
        // check if we're at the end
        if (state->row >= maxLvl - 1) continue;

        // make new state on next row
        rowScore = bookScore;
        score = state->score;
        if (rowScore > state->score) score = rowScore;
        
        shared_ptr<State> newState2 = make_shared<State>(state->row + 1, rowScore, score, state->bookPtr + 1);
        states.insert(newState2);
    }
    return 0;
}