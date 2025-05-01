// new approach: give all to 1, then sort, then move all to 2 that make a difference

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

using std::cout, std::cin, std::vector, std::ifstream, std::getline, std::string, std::endl, std::stoi, std::pair,
      std::pow, std::sqrt, std::sort;

struct Missile {
    pair<int, int> coords;
    double dist;
    Missile(pair<int, int> &c, double d) {
        coords = c;
        dist = d;
    }
};
double distance(pair<int, int> x, pair<int, int> y) {
    return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
    string str = "";

    // get detectors
    vector<int> inputDetector;
    string parseStr = "";
    getline(cin, str);
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str.at(i) == ' ') {
            inputDetector.push_back(stoi(parseStr));
            parseStr = "";
            continue;
        }
        parseStr += str.at(i);
        if (i == str.size()-1) {
            inputDetector.push_back(stoi(parseStr));
            parseStr = "";
        }
    }
    pair<int, int> detector1(inputDetector.at(0), inputDetector.at(1));
    pair<int, int> detector2(inputDetector.at(2), inputDetector.at(3));

    // get missiles
    getline(cin, str);
    int totalMissiles = stoi(str);
    vector<Missile> missiles;
    for (int i = 0; i < totalMissiles; i++) {
        getline(cin, str);
        double c1;
        double c2;
        for (unsigned int i = 0; i < str.size(); i++) {
            if (str.at(i) == ' ') {
                c1 = stoi(parseStr);
                parseStr = "";
                continue;
            }
            parseStr += str.at(i);
            if (i == str.size()-1) {
                c2 = stoi(parseStr);
                parseStr = "";
            }
        }
        pair<int, int> coords(c1, c2);
        Missile missile(coords, distance(detector1, coords));
        missiles.push_back(missile);
    }

    // sort missiles
    sort(missiles.begin(), missiles.end(),
        [](const Missile& a, const Missile& b) {
            return a.dist < b.dist;
    });

    // for (auto i : missiles) {
    //     cout << i.coords.first << ", " << i.coords.second << "; " << i.dist << endl;
    // }

    // go through missiles
    double detector1Dist = missiles.at(missiles.size()-1).dist;
    double detector2Dist = 0;
    for (int i = missiles.size()-1; i >= 0; i--) {
        double dist = distance(missiles.at(i).coords, detector2);

        // if distance to detector 2 is less than our current
        if (dist < missiles.at(i).dist) {
            if (dist > detector2Dist) {
                detector2Dist = dist;
            }
        }
    }

    // cout << "1: " << detector1Dist << endl;
    // cout << "2: " << detector2Dist << endl;
    cout << static_cast<int>(round(detector1Dist * detector1Dist + detector2Dist * detector2Dist));

    return 0;
}