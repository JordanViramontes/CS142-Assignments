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
    int height = 1;
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

    void insert(shared_ptr<Node> newNode) {
        head = insert(head, newNode);
    }    
 
    shared_ptr<Node> insert(shared_ptr<Node> node, shared_ptr<Node> newNode) {
        if (!node) return newNode;
    
        if (newNode->num < node->num)
            node->L = insert(node->L, newNode);
        else
            node->R = insert(node->R, newNode);
    
        updateHeight(node);
        int balance = getBalance(node);
    
        // Left Left Case
        if (balance > 1 && newNode->num < node->L->num)
            return rotateRight(node);
    
        // Right Right Case
        if (balance < -1 && newNode->num >= node->R->num)
            return rotateLeft(node);
    
        // Left Right Case
        if (balance > 1 && newNode->num >= node->L->num) {
            node->L = rotateLeft(node->L);
            return rotateRight(node);
        }
    
        // Right Left Case
        if (balance < -1 && newNode->num < node->R->num) {
            node->R = rotateRight(node->R);
            return rotateLeft(node);
        }
    
        return node;
    }
    

    int height(shared_ptr<Node> n) {
        return n ? n->height : 0;
    }
    
    int getBalance(shared_ptr<Node> n) {
        return n ? height(n->L) - height(n->R) : 0;
    }
    
    void updateHeight(shared_ptr<Node> n) {
        n->height = 1 + max(height(n->L), height(n->R));
    }

    // rotations
    shared_ptr<Node> rotateRight(shared_ptr<Node> y) {
        shared_ptr<Node> x = y->L;
        shared_ptr<Node> T2 = x->R;
    
        x->R = y;
        y->L = T2;
    
        updateHeight(y);
        updateHeight(x);
    
        return x;
    }

    shared_ptr<Node> rotateLeft(shared_ptr<Node> x) {
        shared_ptr<Node> y = x->R;
        shared_ptr<Node> T2 = y->L;
    
        y->L = x;
        x->R = T2;
    
        updateHeight(x);
        updateHeight(y);
    
        return y;
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