#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using std::cout, std::cin, std::vector, std::ifstream, std::getline, std::string, std::endl, std::stoi, std::pair,
      std::pow, std::sqrt;

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
    vector<pair<int, int>> missiles;
    for (int i = 0; i < totalMissiles; i++) {
        getline(cin, str);
        pair<int, int> missile;
        for (unsigned int i = 0; i < str.size(); i++) {
            if (str.at(i) == ' ') {
                missile.first = stoi(parseStr);
                parseStr = "";
                continue;
            }
            parseStr += str.at(i);
            if (i == str.size()-1) {
                missile.second = stoi(parseStr);
                parseStr = "";
            }
        }
        missiles.push_back(missile);
    }

    // cout << "d1: " << detector1.first << ", " << detector1.second << endl;
    // cout << "d2: " << detector2.first << ", " << detector2.second << endl;
    long double size1 = 0;
    long double size2 = 0;
    for (unsigned int i = 0; i < missiles.size(); i++) {
        // check distances for missile to each detector
        // cout << "m: " << missiles.at(i).first << ", " << missiles.at(i).second << endl;
        long double dist1 = distance(detector1, missiles.at(i));
        long double dist2 = distance(detector2, missiles.at(i));
        // cout << "coord: " << missiles.at(i).first << ", " << missiles.at(i).second << "\tdist: " << dist1 << ", " << dist2 << endl;

        // check if we already cover it
        if (dist1 <= size1 || dist2 <= size2) {
            continue;
        }

        if(dist1 < dist2) { // 1 is better
            if (dist1 > size1) size1 = dist1;
        }
        else if (dist1 > dist2){ // 2 is better
            if (dist2 > size2) size2 = dist2;
        }
        else {
            // if equal, keep the smaller one and change the larger one
            if (size2 <= size1) size1 = dist1;
            else size2 = dist1;
        }
    }
    // cout << "sizes: " << size1 << ", " << size2 << endl;
    long double fin = (size1*size1) + (size2*size2);
    // cout << "size: " << size1 << ", " << size2 << endl;
    cout << static_cast<int>(round(fin)) << endl;


    return 0;
}