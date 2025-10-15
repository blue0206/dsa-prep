/*
 * Problem: Strongly Connected Components - Kosaraju's Algorithm
 * Link:
 * https://www.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1
 *
 * Approach: Kosaraju's algorithm finds Strongly Connected Components (SCCs) in
 *           a directed graph using two DFS traversals. An SCC is a subgraph
 *           where every vertex is reachable from every other vertex.
 *           1.  **Order Nodes by Finish Time:** Perform a DFS on the original
 *               graph. Store the nodes in a stack based on their finishing
 *               times (a node is pushed to the stack after all its descendants
 *               have been visited). This is effectively a topological sort.
 *           2.  **Reverse the Graph:** Create a new graph where the direction
 *               of every edge is reversed.
 *           3.  **Count SCCs:** Process the nodes from the stack (in order of
 *               decreasing finish times). For each unvisited node, start a DFS
 *               on the reversed graph. All nodes visited in this DFS form one
 *               SCC. The number of times we start a new DFS is the number of
 *               SCCs.
 *
 * Time Complexity: O(V + E), as it involves three linear-time passes (DFS,
 *                  graph reversal, DFS).
 * Space Complexity: O(V + E) for the adjacency lists, visited array, and stack.
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int kosaraju(int V, vector<vector<int>>& adj);
void topoSort(const vector<vector<int>>& adj, stack<int>& st,
              vector<bool>& visited, int node);
void dfs(const vector<vector<int>>& adj, vector<bool>& visited, int node);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    for (int i = 0; i < E; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
    }

    cout << "Number of Strongly Connected Components (SCC): "
         << kosaraju(V, adj) << endl;

    cout << endl;
  }

  return 0;
}

int kosaraju(int V, vector<vector<int>>& adj) {
  // Step 1: Sort all the nodes in order of finishing time (Topological Sort)
  vector<bool> visited(V, false);
  stack<int> st;
  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      topoSort(adj, st, visited, i);
    }
  }

  // Step 2: Reverse the graph
  vector<vector<int>> reverseAdj(V);
  for (int i = 0; i < V; i++) {
    visited[i] = false;  // Re-use visited array for the next step
    for (int next : adj[i]) {
      reverseAdj[next].emplace_back(i);
    }
  }

  // Step 3: Perform DFS on the reversed graph according to finishing times
  int sccCount = 0;
  while (!st.empty()) {
    int node = st.top();
    st.pop();

    if (!visited[node]) {
      sccCount++;
      dfs(reverseAdj, visited, node);
    }
  }

  return sccCount;
}

void topoSort(const vector<vector<int>>& adj, stack<int>& st,
              vector<bool>& visited, int node) {
  visited[node] = true;

  for (int next : adj[node]) {
    if (!visited[next]) {
      topoSort(adj, st, visited, next);
    }
  }

  st.push(node);
}

void dfs(const vector<vector<int>>& adj, vector<bool>& visited, int node) {
  visited[node] = true;

  for (int next : adj[node]) {
    if (!visited[next]) {
      dfs(adj, visited, next);
    }
  }
}
