#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Number {
    int V = 0;
    int I = 0;
    int D = 0;
    Number() {}
    Number(int value) {
        V = value;
    }
};

void findIncreasing(vector<Number> &nums) {
    nums[0].I = 1; // set base case
    for (int i = 1; i < nums.size(); i++) {
        int highest = 1;
        for (int j = 0; j < i; j++) {
            if (nums[i].V > nums[j].V) {
                int count = nums[j].I + 1;
                if (count > highest) highest = count;
            }
        }
        nums[i].I = highest;
    }
}

void findDecreasing(vector<Number> &nums) {
    nums[nums.size()-1].D = 1; // set base case
    for (int i = nums.size()-2; i >= 0; i--) {
        int highest = 1;
        for (int j = nums.size()-1; j >= i; j--) {
            if (nums[i].V > nums[j].V) {
                int count = nums[j].D + 1;
                if (count > highest) highest = count;
            }
        }
        nums[i].D = highest;
    }
}

int findUniform(vector<Number> &nums) {
    // track the highest inc and dec, first = value, second = coords
    int highest = 0;

    for (int i = 1; i < nums.size()-1; i++) {
        int current = nums[i].I - 1 + nums[i].D - 1 + 1;
        if (current > highest) highest = current;
    }

    return highest;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    // parse inputs
    int n;
    cin >> n;

    vector<Number> nums(n);
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        Number number(num);
        nums[i] = number;
    }

    // for (auto i : nums) {
    //     cout << i.V << ", ";
    // }
    // cout << endl;
    
    findIncreasing(nums);
    findDecreasing(nums);
    
    // cout << "INCREASING: ";
    // for (auto i : nums) {
    //     cout << i.I << ", ";
    // }
    // cout << endl;

    // cout << "DECREASING: ";
    // for (auto i : nums) {
    //     cout << i.D << ", ";
    // }
    // cout << endl;

    cout << findUniform(nums);

    return 0;
}