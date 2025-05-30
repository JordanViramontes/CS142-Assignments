#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

struct Node {
    vector<shared_ptr<Node>> children;
    bool traitor = false;
    bool head = true;
    int value = -1; // used for dp
    int element = 0;

    Node() {}
};

// dfs
int search(shared_ptr<Node> n) {
    // dp
    if (n->value != -1) {
        return n->value;
    }
    
    // traitor
    if (n->traitor) {
        n->value = 0;
        return 0;
    }

    bool isLeaf = true;

    // look over children
    int total = 1;
    for (auto i : n->children) {
        if (i->traitor) continue;
        // cout << "check: " << i->element << endl;
        total += search(i);
        i->head = false;
        isLeaf = false;
    }

    // our element is a leaf
    if (isLeaf) {
        // cout << "leaf!" << endl;
        n->head = false;
        n->value = 1;
        return 1;
    }

    n->value = total;
    return total;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");
    
    // parse
    int n, m;
    cin >> n >> m;

    // cout << "n: " << n << ", m: " << m << endl;

    vector<shared_ptr<Node>> tree(n, nullptr);
    for (unsigned int i = 0; i < tree.size(); i++) {
        tree[i] = make_shared<Node>();
        tree[i]->element = i;
    }

    // parse children and traitors
    vector<int> childrenVector;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;

        // push the new child to the parent
        tree[p]->children.push_back(tree[i]);
    }

    for (int i = 0; i < m; i++) {
        int p;
        cin >> p;

        // set traitor
        tree[p]->traitor = true;
    }

    for (unsigned int it = 0; it < tree.size(); it++) {
        auto i = tree[it];
        if (i->traitor) {
            // cout << "traitor!" << endl;
            continue;
        }
        search(i);
    }

    // for (auto i : tree) {
    //     cout << "e: " << i->element << ", h: " << i->head << ", t: " << i->traitor << ", v: " << i->value << endl;
    // }


    int total = 0;
    for (auto i : tree) {
        if (i->traitor || i->head == false) continue;
        int get = search(i);
        // cout << "e: " << i->element << ", adding: " << get << endl;
        total += get;
    }

    cout << total;

    return 0;
}