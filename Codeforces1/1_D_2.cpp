#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

using std::cout, std::cin, std::vector, std::ifstream, std::getline, std::string, std::endl, std::stoi, std::pair,
      std::pow, std::sqrt;

      
int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
    
    // get dart info
    int sectors = 0;
    int startingNumber = 0;
    scanf("%d %d", &sectors, &startingNumber);

    // get points
    vector<int> darts(sectors, 0);
    vector<int> points = {0};
    for (int i = 0; i < sectors; i++) {
        int p;
        scanf("%d", &p);
        points.push_back(p);
        darts.at(i) = i;
    }

    for (auto i : darts) {
        cout << i << ", ";
    }
    cout << endl;

    for (auto i : points) {
        cout << i << ", ";
    }
    cout << endl;

    // sort points so that we start with the lowest first mm
    // sort(points.begin(), points.end());

    int bestScore = startingNumber;
    vector<int> bestDarts(4, 0);
    cout << "t: " << bestScore << endl;
    for (int i = 0; i < darts.size(); i++) {
        for (int j = 0; j < darts.size(); j++) {
            for (int k = 0; k < darts.size(); k++) {
                for (int n = 0; n < darts.size(); n++) {
                    vector<int> new_darts = {
                        darts.at(i), darts.at(j), darts.at(k), darts.at(n)
                    };
                    vector<int> new_points = {
                        points.at(i), points.at(j), points.at(k), points.at(n)
                    };

                    // calculate score
                    int currentScore = startingNumber;
                    for (auto m : new_points) {
                        currentScore -= m;
                        if (currentScore < 0) currentScore = startingNumber;
                    }

                    if (currentScore < bestScore) {
                        bestScore = currentScore;
                        bestDarts = new_darts;
                    }
                }
            }
        }
    }
    cout << "A: " << bestScore << endl;
    for (auto i : bestDarts) {
        cout << i << " ";
    }
    
    
    return 0;
}