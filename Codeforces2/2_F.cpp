#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <unordered_map>
#include <list>

using namespace std;

struct Node {
    int value = 0;
    int connections = 0;
    bool visited = false;
    vector<shared_ptr<Node>> connectedNodes;
    Node(int v) {
        value = v;
    }
    void addConnection(shared_ptr<Node> n) {
        connectedNodes.push_back(n);
        connections++;
    }
    void printConnected() {
        for (auto i : connectedNodes) {
            cout << i->value << ", ";
        }
        cout << endl;
    }
};

// modification of BFS with visited logic
int findLongest(shared_ptr<Node> n) {
    if (n == nullptr) return 0;
    if (n->connectedNodes.size() == 0) return 0;

    n->visited = true;
    int highest = 0;
    // cout << "in: " << n->value << endl;
    for (shared_ptr<Node> i : n->connectedNodes) {
        if (i->visited == false) {
            // cout << "Visiting: " << i->value << endl;
            int current = findLongest(i) + 1;
            if (current > highest) highest = current;
        }
    }

    n->visited = false;
    return highest;
}

int main(int argc, char* argv[]) {
    // ifstream cin("input.txt");

    // parse
    int n;
    cin >> n;
    vector<shared_ptr<Node>> exhibits;
    for (unsigned int i = 0; i < n; i++) {
        shared_ptr<Node> exhibit = make_shared<Node>(i+1);
        exhibits.push_back(exhibit);
    }

    // add connections
    for (int i = 0; i < n-1; i++) {
        int from;
        int to;
        cin >> from >> to;

        // connect exhibits
        exhibits[from-1]->addConnection(exhibits[to-1]);
        exhibits[to-1]->addConnection(exhibits[from-1]);
    }

    // get leaf nodes
    list<shared_ptr<Node>> leaves;
    for (auto i : exhibits) {
        if (i->connectedNodes.size() == 1) { // leaf
            leaves.push_back(i);
        }
    }

    // if the amount of nodes left are less than 2 we have our 2 winners!
    int totalExhibitCount = exhibits.size();
    int finalCount = 0;
    // cout << "total: " << totalExhibitCount << endl;
    while(totalExhibitCount > 2) {
        shared_ptr<Node> front = leaves.front();
        leaves.pop_front();
        totalExhibitCount--;

        // cout << "REMOVING: " << front->value << endl;

        // lower the connection count for connected nodes
        for (auto i : front->connectedNodes) {
            i->connections -= 1;
            if (i->connections == 1) {
                leaves.push_back(i);
            }
        }

    }

    // 2 nodes left
    if (totalExhibitCount == 2) {
        list<shared_ptr<Node>>::iterator it = leaves.begin();
        int first = findLongest(*it);
        int second = findLongest(*std::next(it));
        // cout << first << ", " << second << endl;
        cout << min(first, second);
    }
    else {
        // cout << "final: " << leaves.front()->value << endl;
        cout << findLongest(leaves.front());
    }


    return 0;
}