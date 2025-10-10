/*
 * Problem: Directed Graph Cycle
 * Link:
 * https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
 *
 * Approach: This problem is solved using a Depth-First Search (DFS) with a
 *           3-color system to track the state of each node. A cycle is
 *           detected if we encounter a "back edge" during the traversal.
 *
 *           -   **Color 0 (White):** The node has not been visited yet.
 *           -   **Color 1 (Gray):** The node is currently being visited (it's
 *               in the current recursion stack).
 *           -   **Color 2 (Black):** The node and all its descendants have been
 *               fully visited.
 *
 *           The DFS starts from an unvisited (white) node. It marks the node as
 *           visiting (gray). For each neighbor, if the neighbor is gray, we
 *           have found a back edge, and thus a cycle. If the neighbor is white,
 *           we recurse on it. After visiting all neighbors, the node is marked
 *           as fully visited (black).
 *
 * * Time Complexity: O(V + E)
 * * Space Complexity: O(V) for the colors array and recursion stack.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool isCyclic(int V, vector<vector<int>>& edges);
bool dfs(const vector<vector<int>>& adjList, vector<int>& colors, int node);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int v;
    cin >> v;  // Number of vertices

    int e;
    cin >> e;  // Number of edges

    vector<vector<int>> adj(v);
    for (int i = 0; i < v; i++) {
      int u, v_node;
      cin >> u >> v_node;
      adj[u].emplace_back(v_node);
    }

    cout << "Edges: [";
    for (int i = 0; i < adj.size(); ++i) {
      cout << i << " -> ";
      cout << "[ ";
      for (int neighbor : adj[i]) {
        cout << neighbor << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Has Cycle: " << (isCyclic(v, adj) ? "True" : "False") << endl;
  }

  return 0;
}

bool isCyclic(int V, vector<vector<int>>& edges) {
  vector<vector<int>> adjList(V);
  for (int i = 0; i < edges.size(); i++) {
    adjList[edges[i][0]].emplace_back(edges[i][1]);
  }

  vector<int> colors(V, 0);
  for (int i = 0; i < V; i++) {
    if (colors[i] == 0 && dfs(adjList, colors, i)) {
      return true;
    }
  }

  return false;
}

bool dfs(const vector<vector<int>>& adjList, vector<int>& colors, int node) {
  colors[node] = 1;

  for (int i : adjList[node]) {
    if (colors[i] == 1) {
      return true;
    }
    if (colors[i] == 0 && dfs(adjList, colors, i)) {
      return true;
    }
  }

  colors[node] = 2;
  return false;
}
