/*
 * Problem: Minimum Spanning Tree - Kruskal's Algorithm
 * Link:
 * https://www.geeksforgeeks.org/problems/minimum-spanning-tree-kruskals-algorithm/1
 *
 * Approach:
 * Kruskal's algorithm is a greedy algorithm that finds a Minimum Spanning Tree
 * (MST) for a weighted, undirected graph. It works by sorting all the edges
 * by weight and adding them to the MST if they don't form a cycle.
 * 1.  Sort all edges in non-decreasing order of their weight.
 * 2.  Initialize a Disjoint Set Union (DSU) data structure, with each vertex
 *     as a separate component.
 * 3.  Iterate through the sorted edges. For each edge (u, v), check if u and
 *     v are already in the same component using the DSU's `find` operation.
 * 4.  If they are in different components, adding the edge will not create a
 *     cycle. Add its weight to the MST sum and merge the two components
 *     using the DSU's `union` operation.
 * 5.  If they are in the same component, discard the edge.
 * 6.  The algorithm terminates when V-1 edges have been added to the MST.
 *
 * Time Complexity: O(E log E) for sorting the edges.
 * Space Complexity: O(V + E) for the DSU data structure and storing edges.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class DisjointSet {
 private:
  vector<int> size, parent;

 public:
  DisjointSet(int n) {
    size.assign(n, 1);
    parent.assign(n, 0);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    if (parent[i] == i) return i;

    parent[i] = find(parent[i]);
    return parent[i];
  }

  void unionBySize(int i, int j) {
    int pi = find(i);
    int pj = find(j);

    if (pi == pj) return;

    if (size[pi] >= size[pj]) {
      size[pi] += size[pj];
      parent[pj] = pi;
    } else {
      size[pj] += size[pi];
      parent[pi] = pj;
    }
  }
};

int kruskalsMST(int V, vector<vector<int>>& edges);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> edges(e, vector<int>(3));
    for (int i = 0; i < e; i++) {
      cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    cout << "n: " << n << endl;
    cout << "Node-1\tNode-2\tWeight:" << endl;
    for (auto edge : edges) {
      cout << edge[0] << "\t" << edge[1] << "\t" << edge[2] << endl;
    }
    cout << endl;

    cout << "Minimum Spanning Tree: " << kruskalsMST(n, edges) << endl;

    cout << endl;
  }

  return 0;
}

int kruskalsMST(int V, vector<vector<int>>& edges) {
  sort(edges.begin(), edges.end(),
       [](vector<int>& a, vector<int>& b) { return a[2] < b[2]; });

  DisjointSet dsu(V);
  int mst = 0;
  for (int i = 0; i < edges.size(); i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    int w = edges[i][2];

    if (dsu.find(u) != dsu.find(v)) {
      dsu.unionBySize(u, v);
      mst += w;
    }
  }

  return mst;
}
