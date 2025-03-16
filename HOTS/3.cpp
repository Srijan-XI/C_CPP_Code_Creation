#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a graph edge
struct Edge {
    int src, dest, weight;
};

// Comparison function for sorting edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Structure for Union-Find operations
struct DisjointSet {
    vector<int> parent;
    vector<int> rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i; // Initialize parent array
    }

    // Find the root of a set with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by rank
    void unite(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);

        if (xroot == yroot) return;

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
};

// Function to find the MST using Kruskal's algorithm
vector<Edge> kruskalMST(int V, vector<Edge>& edges) {
    DisjointSet ds(V); // Initialize disjoint set
    vector<Edge> mst;

    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    for (Edge e : edges) {
        int x = ds.find(e.src);
        int y = ds.find(e.dest);

        if (x != y) {
            mst.push_back(e);
            ds.unite(x, y);
            if (mst.size() == V - 1) break;
        }
    }
    return mst;
}

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    // Define edges
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Find MST
    vector<Edge> mst = kruskalMST(V, edges);

    cout << "Edges in the Minimum Spanning Tree:\n";
    int totalWeight = 0;
    for (Edge e : mst) {
        cout << "Edge from " << e.src << " to " << e.dest << " with weight " << e.weight << "\n";
        totalWeight += e.weight;
    }
    cout << "Total weight of MST: " << totalWeight << "\n";

    return 0;
}
