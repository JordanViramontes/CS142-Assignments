#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using std::cout, std::cin, std::vector, std::ifstream, std::getline, std::string, std::endl, std::stoi, std::pair,
      std::pow, std::sqrt;

int roomHeight = 500;
int roomWidth = 500;
int windowSize = 100;

double cross(pair<int, int> coord1, pair<int, int> coord2) {
    return (coord1.second*coord2.first) - (coord1.first*coord2.second);
}

bool testWindow(int north, int south, pair<int, int> coords) {
    // make line from north->south and move it to origin
    // the 2nd line is the same thing but with x += 100
    // also need to shift the coords
    // cout << "shift: " << shift << endl;
    if (north-south == 0) { // perfect rectangle
        if (coords.first <= north + 100 && coords.first >= north) return true;
        return false;
    }
    
    // transpose coords to the origin
    north -= south;
    coords.first -= south;
    pair<int, int> line(north, 500);
    pair<int, int> coords2(coords.first-windowSize, coords.second);

    // cout << "line: " << line.first << ", " << line.second << endl;
    // cout << "line2: " << line2.first << ", " << line2.second << endl;
    // cout << "coords: " << coords.first << ", " << coords.second << endl;


    
    // find crosses
    double cross1 = cross(line, coords);
    double cross2 = cross(line, coords2);
    // cout << "c: " << cross1 << ", " << cross2 << endl;

    // if one is opposite sign
    if ((cross1 >= 0 && cross2 <= 0) || (cross1 <= 0 && cross2 >= 0)) return true;
    return false;
}

bool testRadiation(pair<int, int> rad, pair<int, int> radDist, pair<int, int> coords) {
    double dist = sqrt(pow(rad.first-coords.first, 2) + pow(rad.second-coords.second, 2));
    // cout << "dist: " << dist << endl;
    if (dist <= radDist.second && dist >= radDist.first) return true;
    return false;
}

bool testTv(pair<int, int> coords) {
    // middle is clear
    if (coords.second > 200 && coords.second < 300) return false;
    // left side is all good
    if (coords.first <= 300) return true;

    // shift coords to origin of this problem
    coords.first -= 300;

    // above
    if (coords.second >= 300) {
        pair<int, int> line(-200, 200);
        coords.first -= 200;
        coords.second -= 300; // transpose + mid gap
        double c = cross(line, coords);
        if (c < 0) return true;
        return false;
    }

    // below
    else if (coords.second <= 200) {
        pair<int, int> line(200, 200);
        double c = cross(line, coords);
        cout << "below c: " << c << endl;
        if (c < 0) return true;
        return false;
    }

    return false;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
    string str = "";
    
    // get total books and level
    getline(cin, str);
    vector<int> radiations(4, -1);
    string parseStr = "";
    unsigned int radiationsPtr = 0;
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str.at(i) == ' ') {
            radiations.at(radiationsPtr) = stoi(parseStr);
            radiationsPtr++;
            parseStr = "";
            continue;
        }
        parseStr += str.at(i);
        if (i == str.size()-1) {
            radiations.at(radiationsPtr) = stoi(parseStr);
            parseStr = "";
        }
    }
    pair<int, int> radiatorDist(radiations.at(0), radiations.at(1));
    pair<int, int> radiator(radiations.at(2), radiations.at(3));

    // get window pairs
    getline(cin, str);
    int northWindow;
    int southWindow;
    parseStr = "";
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str.at(i) == ' ') {
            southWindow = stoi(parseStr);
            radiationsPtr++;
            parseStr = "";
            continue;
        }
        parseStr += str.at(i);
        if (i == str.size()-1) {
            northWindow = stoi(parseStr);
            parseStr = "";
        }
    }
    
    // cout << "radiator at : " << radiator.first << ", " << radiator.second << endl;
    // cout << "radiatorDist: " << radiatorDist.first << ", " << radiatorDist.second << endl;
    // cout << "north at : " << northWindow.first << ", " << northWindow.second << endl;
    // cout << "south at: " << southWindow.first << ", " << southWindow.second << endl;

    // parse through input
    getline(cin, str);
    int totalCoords = stoi(str);
    vector<pair<int,int>> allCoords;
    for (int i = 0; i < totalCoords; i++) {
        getline(cin, str);
        parseStr = "";
        pair<int, int> coords;
        for (unsigned int i = 0; i < str.size(); i++) {
            if (str.at(i) == ' ') {
                coords.first = stoi(parseStr);
                radiationsPtr++;
                parseStr = "";
                continue;
            }
            parseStr += str.at(i);
            if (i == str.size()-1) {
                coords.second = stoi(parseStr);
                parseStr = "";
            }
        }

        allCoords.push_back(coords);
    }

   
    for (int i = 0; i < allCoords.size(); i++) {
        pair<int,int> coords = allCoords.at(i);

        // test windows
        bool isWindow = testWindow(northWindow, southWindow, coords);

        // test radiation
        bool isRadiation = testRadiation(radiator, radiatorDist, coords);

        // test tv
        bool isTV = testTv(coords);

        // final
        // cout << "w: " << isWindow << ", r: " << isRadiation << ", t: " << isTV << endl;
        if (isWindow && isRadiation && isTV) cout << "yes" << endl;
        else cout << "no" << endl;
    }

    



    return 0;
}