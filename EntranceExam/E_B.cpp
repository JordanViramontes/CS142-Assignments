#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using std::ifstream, std::pair, std::string, std::cout, std::endl, std::vector, std::pair;

int main(int argc, char* argv[]) {
    // ifstream file("input.txt");
    vector<int> steps;

    // get inputs
    string str = "blank";
    getline(std::cin, str);
    int stepSize = std::stoi(str);

    for (int i = 0; i < stepSize; i++) {
        getline(std::cin, str);
        steps.push_back(std::stoi(str));
    }

    vector<pair<int, int>> numsVec; // <difference between 2 points, amount of times that difference been found throughout vector>
    for (unsigned int i = 1; i < steps.size(); i++) {
        int difference = steps.at(i)-steps.at(i-1);

        // check if difference already in vec
        bool isIn = false;
        unsigned int it = 0;
        for (unsigned int i = 0; i < numsVec.size(); i++) {
            if (numsVec.at(i).first == difference) {
                isIn = true;
                it = i;
            }
        }

        // update vector info
        if (!isIn) { // not in the vector
            pair <int, int> temp (difference, 1);
            numsVec.push_back(temp);
        }
        else { // it is in the vector
            numsVec.at(it).second++;
        }
    }

    // 2 cases,
    // case 1: mistake is at one of the ends of the vector - 2 different differences
    // case 2: mistake is in the middle of the vector - 3 different differences, use math to calculate correct distance and find wrong ones
    int finalAns = -1;

    // case 1
    if (numsVec.size() == 2) {
        int wrongStepNum = -1;

        // get lowest step count (will be the wrong step) 
        for (unsigned int i = 0; i < numsVec.size(); i++) {
            if (numsVec.at(i).second == 1) {
                wrongStepNum = numsVec.at(i).first;
                break;
            }
        }
        
        // check ends of vector for distance
        if (steps.at(1) - steps.at(0) == wrongStepNum) finalAns = 1; // beginning of vec
        else if (steps.at(steps.size()-1) - steps.at(steps.size()-2) == wrongStepNum) finalAns = steps.size(); // end of vec
    }
    
    // case 2
    else if (numsVec.size() >= 3) {
        // use math to find correct step size: (end - beginning) / (size-1)
        int correctLength = (steps.at(steps.size()-1) - steps.at(0)) / (stepSize-1);

        // parse through and find it
        for (unsigned int i = 1; i < steps.size()-1; i++) {
            if (steps.at(i)-steps.at(i-1) != correctLength && steps.at(i+1)-steps.at(i) != correctLength) 
                finalAns = i + 1; // it will have to be here since the element to the left and right are incorrect
        }
    }

    cout << finalAns;

    return 0;
}