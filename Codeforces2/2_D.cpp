#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
 
using namespace std;
 
struct Node {
    shared_ptr<Node> L = nullptr;
    shared_ptr<Node> R = nullptr;
    int num = 0;
    int max = 0;
    // int best = 0;
    // int index = 0;
 
    Node(int n, int m) {
        num = n;
        max = m;
        // index = i;
    }
};
 
class Tree {
    public:
    shared_ptr<Node> head = nullptr;
 
    void insert(shared_ptr<Node> n) {
        // if head is empty
        if (head == nullptr) {
            head = n;
            return;
        }
 
        // go through binary tree
        shared_ptr<Node> curr = head;
        while (true) {
            // less
            if (n->num < curr->num) {
                // if L is empty
                if (curr->L == nullptr) {
                    curr->L = n;
                    break;
                }
                else {
                    curr = curr->L;
                }
            }
            else {
                if (curr->R == nullptr) {
                    curr->R = n;
                    break;
                }
                else {
                    curr = curr->R;
                }
            }
            
        }
    }

    int findIncreasingMax(shared_ptr<Node> n, int num) {
        if (n == nullptr) return 0;
 
        // the new number is less than current (still need to traverse tree)
        if (num < n->num) {  return findIncreasingMax(n->L, num); }
        
        int current = n->max;
        // we're at a valid point
        int L = findIncreasingMax(n->L, num);
        int R = findIncreasingMax(n->R, num);
        
        // cout << "CURRENT: <" << n->num << ", " << n->max << ">\n";
        // cout << "L: " << L << ", R: " << R << endl;

        return max(L, max(R, current));
    }

    int findIncreasingMax(int num) {
        return findIncreasingMax(head, num);
    }
};
 
void printTree(shared_ptr<Node> node) {
    if (node == nullptr) return;
    printTree(node->L);
    // cout << "<" << node->num << ", " << node->max << ", " << node->index << ">, ";
    // cout << "<" << node->num << ", " << node->max << ">;" << node->best << ", ";
    cout << "<" << node->num << ", " << node->max << ">, ";
    printTree(node->R);
}
 
void printTree(Tree & values) {
    printTree(values.head);
    cout << endl;
}
 
int findIncreasing(vector<int> &nums) {
    // initialize tree
    Tree values;
    shared_ptr<Node> initNode = make_shared<Node>(nums[0], nums[0]);
    values.insert(initNode);

    // printTree(values);
 
    int realHighest = 0;
 
    for (int i = 1; i < nums.size(); i++) {
        // get the max of all nodes under n and add it with new num
        int found = values.findIncreasingMax(nums[i]) + nums[i];
        // cout << "FINDING: " << nums[i] << ", FOUND: " << found << endl; 
        
        shared_ptr<Node> n = make_shared<Node>(nums[i], found);
        values.insert(n);

        if (found > realHighest) realHighest = found;
        // printTree(values);
    }
 
    return realHighest;
}
 
int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
 
    // parse
    int n;
    cin >> n;
 
    vector<int> memories(n);
    for (int i = 0; i < n; i++) {
        cin >> memories[i];
    }
 
    // LIS
    int ans = findIncreasing(memories);
    cout << ans;
}