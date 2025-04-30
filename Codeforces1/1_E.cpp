#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>

using std::cout, std::cin, std::vector, std::ifstream, std::getline, std::string, std::endl, std::stoi, std::pair,
      std::pow, std::sqrt, std::atan2;

double distance(pair<int, int> x, pair<int, int> y) {
    return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
}

pair<double, double> findIntersection(vector<pair<int,int>> coords) {
    // coords
    pair<int, int> A = coords.at(0);
    pair<int, int> B = coords.at(1);
    pair<int, int> C = coords.at(2);
    pair<int, int> D = coords.at(3);

    // reorder coords
    double B_dist = distance(A, B);
    double C_dist = distance(A, C);
    double D_dist = distance(A, D);
    double max_dist = std::max(B_dist, std::max(C_dist, D_dist));
    if (max_dist == C_dist) {
        swap(B, C);
    }
    else if (max_dist == D_dist) {
        swap(B, D);
    }

    // direction vectors
    pair<int, int> AB = pair<int,int>(B.first-A.first, B.second-A.second);
    pair<int, int> AC = pair<int,int>(C.first-A.first, C.second-A.second);
    pair<int, int> AD = pair<int,int>(D.first-A.first, D.second-A.second);

    // cout << "AB: " << AB.first << ", " << AB.second << endl;
    // cout << "AC: " << AC.first << ", " << AC.second << endl;
    // cout << "AD: " << AD.first << ", " << AD.second << endl;

    // find cross products
    double ABxAC = AB.first * AC.second - AB.second * AC.first;
    double ABxAD = AB.first * AD.second - AB.second * AD.first;

    // cout << "ABxAC: " << ABxAC << endl;
    // cout << "ABxAD: " << ABxAD << endl;

    // find intersection
    pair<double, double> inter = pair<double,double>(
        (ABxAD * C.first - ABxAC * D.first) / (ABxAD - ABxAC),
        (ABxAD * C.second - ABxAC * D.second) / (ABxAD - ABxAC)
    );
    return inter;
}

vector<vector<pair<double, double>>> findTriangles(vector<pair<int, int>> coords, pair<double, double> intersection) {
    // reorder coords in clockwise order using arctan angles
    sort(coords.begin(), coords.end(), [&](const pair<int,int>& a, const pair<int, int> b) {
        double angleA = atan2(a.second - intersection.second, a.first - intersection.first);
        double angleB = atan2(b.second - intersection.second, b.first - intersection.first);
        return angleA < angleB;
    });
    
    vector<vector<pair<double, double>>> triangles;
    for (unsigned int i = 0; i < coords.size(); i++) {
        vector<pair<double, double>> triangle;
        
        triangle.push_back(intersection);
        triangle.push_back(coords.at(i));
        if (i == 0) triangle.push_back(coords.at(coords.size()-1));
        else triangle.push_back(coords.at(i-1));
        
        triangles.push_back(triangle);
    }

    // for (auto i : triangles) {
    //     for (auto j : i) {
    //         cout << "<" << j.first << ", " << j.second << ">, ";
    //     }
    //     cout << endl;
    // }

    return triangles;
}

double findAreas(vector<vector<pair<double, double>>> triangles) {
    double area = 0;
    for (auto i: triangles) {
        // using determinant method
        double a1 = i.at(0).first * (i.at(1).second - i.at(2).second);
        double a2 = i.at(1).first * (i.at(2).second - i.at(0).second);
        double a3 = i.at(2).first * (i.at(0).second - i.at(1).second);
        double a = 0.5 * (a1 + a2 + a3);
        if (a < 0) a *= -1;
        area += a;
    }
    return area;
}

double sign(const pair<int, int>& p1, const pair<int, int>& p2, const pair<int, int>& p3) {
    return (p1.first - p3.first) * (p2.second - p3.second) -
           (p2.first - p3.first) * (p1.second - p3.second);
}

pair<bool, vector<pair<double, double>>> isTriangle(vector<pair<int, int>> coords) {
    // check triangle - coordTriangles is a vector of first: triangle, second: left out point
    vector<pair<vector<pair<double, double>>, pair<int, int>>> coordTriangles;
    for (unsigned int i = 0; i < coords.size(); i++) {
        vector<pair<double, double>> triangle;
        for (unsigned int j = 0; j < coords.size(); j++) {
            if (j == i) continue;
            triangle.push_back(coords.at(j));
        }
        auto coordT = pair<vector<pair<double, double>>, pair<int, int>>(triangle, coords.at(i));
        coordTriangles.push_back(coordT);
    }

    bool isTriangle = false;
    vector<pair<double, double>> triangle = {};
    for (auto i : coordTriangles) {
        double d1 = sign(i.second, i.first.at(0), i.first.at(1));
        double d2 = sign(i.second, i.first.at(1), i.first.at(2));
        double d3 = sign(i.second, i.first.at(2), i.first.at(0));

        bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        if (!(has_neg && has_pos)) {
            isTriangle = true;
            triangle = i.first;
        }
    }

    return pair<bool, vector<pair<double, double>>>(isTriangle, triangle);
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
    string str = "";

    // get dart info
    vector<pair<int, int>> coords;
    for (int k = 0; k < 4; k++) {
        int x = -1;
        int y = -1;
        string parseStr = "";

        // parse
        getline(cin, str);
        for (unsigned int i = 0; i < str.size(); i++) {
            if (str.at(i) == ' ') {
                x = stoi(parseStr);
                parseStr = "";
                continue;
            }
            parseStr += str.at(i);
            if (i == str.size()-1) {
                y = stoi(parseStr);
                parseStr = "";
            }
        }
        coords.push_back(pair<int, int>(x, y));
    }

    // get intersection first just to check same line 
    pair<double, double> intersection = findIntersection(coords);
    // if nan then we're on the same line
    if (std::isnan(intersection.first) || std::isnan(intersection.second)) {
        cout << std::fixed << std::setprecision(6) << 0.000000;
        return 0;
    }

    // check if we're a triangle
    pair<bool, vector<pair<double, double>>> isT = isTriangle(coords);
    if (isT.first) {
        // cout << "is triangle!: " << endl;
        vector<vector<pair<double, double>>> tVec;
        tVec.push_back(isT.second);
        // float ans = static_cast<float>(findAreas(tVec));
        float ans = findAreas(tVec);
        cout << std::fixed << std::setprecision(6) << ans;
        return 0;
    }

    // if quad
    vector<vector<pair<double, double>>> triangles = findTriangles(coords, intersection);
    // float ans = static_cast<float>(findAreas(triangles));
    float ans = findAreas(triangles);
    cout << std::fixed << std::setprecision(6) << ans;
}