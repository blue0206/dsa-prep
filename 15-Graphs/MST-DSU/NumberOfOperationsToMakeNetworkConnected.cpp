/*
 * Problem: Number of Operations to Make Network Connected (LeetCode #1319)
 * Link:
 * https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/
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

  int soloCount() {
    int count = 0;
    for (int i = 0; i < parent.size(); i++) {
      if (find(i) == i) count++;
    }

    return count - 1;
  }
};

/**
 * Approach: This problem is about finding the number of connected components in
 *           a graph. If there are `k` components, we need `k-1` operations
 *           (moving a cable) to connect them all.
 *           First, a graph with `n` nodes requires at least `n-1` edges to be
 *           fully connected. If we have fewer, it's impossible.
 *           This solution uses DFS to count the components. We iterate through
 *           each node, and if it's unvisited, we increment our component count
 *           and start a DFS to find and mark all nodes in that component.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E) for the adjacency list and recursion stack.
 */
int dfsApproach(int n, vector<vector<int>>& connections);
void dfs(const vector<vector<int>>& adj, vector<int>& visited, int node);

/**
 * Approach: This problem can also be solved efficiently using a Disjoint Set
 *           Union (DSU) data structure. The number of operations needed is
 *           equal to the number of connected components minus one.
 *           1.  Check if there are enough edges (`n-1`). If not, return -1.
 *           2.  Initialize a DSU structure with `n` nodes.
 *           3.  Iterate through all connections, performing a `union` operation
 *               for each pair of connected nodes.
 *           4.  After processing all edges, the number of disjoint sets
 *               remaining is the number of connected components.
 *
 * Time Complexity: O(E * α(V)), where α is the inverse Ackermann function.
 * Space Complexity: O(V) for the DSU data structure.
 */
int dsuApproach(int n, vector<vector<int>>& connections);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> connections(e, vector<int>(2));
    for (int i = 0; i < e; i++) {
      cin >> connections[i][0] >> connections[i][1];
    }

    cout << "Connections: " << endl;
    cout << "From\tTo" << endl;
    for (auto connection : connections) {
      cout << connection[0] << "\t" << connection[1] << endl;
    }
    cout << endl;

    cout << "Minimum Operations (DFS): " << dfsApproach(n, connections) << endl;
    cout << "Minimum Operations (DSU): " << dsuApproach(n, connections) << endl;

    cout << endl;
  }

  return 0;
}

//------------------------------DFS APPROACH------------------------------------
int dfsApproach(int n, vector<vector<int>>& connections) {
  if (connections.size() < n - 1) {
    return -1;
  }

  vector<vector<int>> adj(n);
  for (int i = 0; i < connections.size(); i++) {
    adj[connections[i][0]].emplace_back(connections[i][1]);
    adj[connections[i][1]].emplace_back(connections[i][0]);
  }

  vector<int> visited(n, 0);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      count++;
      dfs(adj, visited, i);
    }
  }

  return count - 1;
}

void dfs(const vector<vector<int>>& adj, vector<int>& visited, int node) {
  visited[node] = 1;

  for (int next : adj[node]) {
    if (!visited[next]) {
      dfs(adj, visited, next);
    }
  }
}

//------------------------------DSU APPROACH------------------------------------
int dsuApproach(int n, vector<vector<int>>& connections) {
  if (connections.size() < n - 1) return -1;

  DisjointSet dsu(n);
  for (int i = 0; i < connections.size(); i++) {
    int u = connections[i][0];
    int v = connections[i][1];

    dsu.unionBySize(u, v);
  }

  int count = dsu.soloCount();
  return count;
}
