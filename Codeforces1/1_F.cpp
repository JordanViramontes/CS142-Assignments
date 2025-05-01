#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>

using std::cout, std::cin, std::vector, std::ifstream, std::getline, std::string, std::endl, std::stoi, std::pair,
      std::pow, std::sqrt, std::sort;

long double distance(pair<int, int> x, pair<int, int> y) {
    return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
}

// used for making sure the set orders the boards by score
struct MissileCompare {
    bool operator()(const pair<pair<int, int>, long double>& a, const pair<pair<int, int>, long double>& b) const {
        return a.second < b.second;
    }
};

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
    vector<pair<pair<int, int>, long double>> detector1Missils;
    vector<pair<pair<int, int>, long double>> detector2Missils;
    for (unsigned int i = 0; i < missiles.size(); i++) {
        // check distances for missile to each detector
        // cout << "m: " << missiles.at(i).first << ", " << missiles.at(i).second << endl;
        long double dist1 = distance(detector1, missiles.at(i));
        long double dist2 = distance(detector2, missiles.at(i));
        // cout << "coord: " << missiles.at(i).first << ", " << missiles.at(i).second << "\tdist: " << dist1 << ", " << dist2 << endl;
        
        // check if its exactly on top
        if (dist1 == 0) {
            detector1Missils.push_back(pair<pair<int, int>, long double>(missiles.at(i), dist1));
            continue;
        }
        if (dist2 == 0) {
            detector2Missils.push_back(pair<pair<int, int>, long double>(missiles.at(i), dist2));
            continue;
        }

        // check if we already cover it
        if (dist1 <= size1 || dist2 <= size2) {
            continue;
        }
 
        if(dist1 < dist2) { // 1 is better
            if (dist1 > size1) size1 = dist1;
            detector1Missils.push_back(pair<pair<int, int>, long double>(missiles.at(i), dist1));
        }
        else if (dist1 > dist2){ // 2 is better
            if (dist2 > size2) size2 = dist2;
            detector2Missils.push_back(pair<pair<int, int>, long double>(missiles.at(i), dist2));
        }
        else {
            // if equal, keep the smaller one and change the larger one
            if (size2 <= size1) {
                size1 = dist1;
                detector1Missils.push_back(pair<pair<int, int>, long double>(missiles.at(i), dist1));
            }
            else {
                size2 = dist1;
                detector2Missils.push_back(pair<pair<int, int>, long double>(missiles.at(i), dist2));
            }
        }
    }

    sort(detector1Missils.begin(), detector1Missils.end(),
     [](const pair<pair<int, int>, long double>& a, const pair<pair<int, int>, long double>& b) {
         return a.second < b.second;
     });

    sort(detector2Missils.begin(), detector2Missils.end(),
     [](const pair<pair<int, int>, long double>& a, const pair<pair<int, int>, long double>& b) {
         return a.second < b.second;
     });

    // cout << "1" << endl;
    // for (auto i : detector1Missils) {
    //     cout << i.first.first << ", " << i.first.second << "; " << i.second << endl;
    // }
    // cout << endl;

    // cout << "2" << endl;
    // for (auto i : detector2Missils) {
    //     cout << i.first.first << ", " << i.first.second << "; " << i.second << endl;
    // }
    // cout << endl;

    long double max1 = detector1Missils.at(detector1Missils.size()-1).second;
    long double max2 = detector2Missils.at(detector2Missils.size()-1).second;

    // cout << "1:" << max1 << endl;
    // cout << "2:" << max2 << endl;

    // detector 1 had the smaller max
    if (max1 > max2) {
        // cout << "1 was larger" << endl;
        for (int i = detector2Missils.size()-1; i >= 0; i--) {
            long double dist = distance(detector1, detector2Missils.at(i).first);
            // cout << "dist: " << dist << endl;

            // already within the range
            if (dist < max1) {
                // cout << "bad" << endl;
                detector2Missils.pop_back();
            }
            else {
                break;
            }
        }
    }
    else if (max2 > max1) {
        // cout << "2 was smaller" << endl;
        for (int i = detector1Missils.size()-1; i >= 0; i--) {
            long double dist = distance(detector2, detector1Missils.at(i).first);
            // cout << "dist: " << dist << endl;

            // already within the range
            if (dist < max2) {
                // cout << "bad" << endl;
                detector1Missils.pop_back();
            }
            else {
                break;
            }
        }
    }
    

    if (detector1Missils.size() == 0) max1 = 0;
    else max1 = detector1Missils.at(detector1Missils.size()-1).second;
    if (detector2Missils.size() == 0) max2 = 0;
    else max2 = detector2Missils.at(detector2Missils.size()-1).second;

    // cout << "1: " << max1 << endl;
    // cout << "2: " << max2 << endl;

    // cout << "sizes: " << size1 << ", " << size2 << endl;
    long double fin = (max1 * max1) + (max2 * max2);
    // cout << "size: " << size1 << ", " << size2 << endl;
    cout << static_cast<int>(round(fin)) << endl;


    return 0;
}