/*
 * Problem: Undirected Graph Cycle
 * Link:
 * https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

/**
 * Approach: This solution uses Depth-First Search (DFS) to detect a cycle.
 *           While traversing, we keep track of the parent of the current node.
 *           If we encounter a neighbor that is already visited and is *not* the
 *           immediate parent of the current node, we have found a back edge,
 *           which indicates a cycle.
 *
 * Time Complexity: O(V + E), where V is vertices and E is edges.
 * Space Complexity: O(V) for the visited array and recursion stack.
 */
bool dfsApproach(int V, vector<vector<int>>& edges);
bool dfs(int node, int parent, vector<vector<int>>& adj, vector<int>& visited);

/**
 * Approach: This solution uses Breadth-First Search (BFS) to detect a cycle.
 *           The queue stores pairs of `(node, parent)`. When exploring a
 *           node's neighbors, if we find a neighbor that is already visited
 *           and is *not* the immediate parent, it means we've found an
 *           alternative path to it, indicating a cycle.
 *
 * Time Complexity: O(V + E), where V is vertices and E is edges.
 * Space Complexity: O(V) for the visited array and queue.
 */
bool bfsApproach(int V, vector<vector<int>>& edges);
bool bfs(int node, vector<vector<int>>& adj, vector<int>& visited);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> edges(E, vector<int>(2));
    for (int i = 0; i < E; i++) {
      cin >> edges[i][0] >> edges[i][1];
    }

    cout << "Edges: [ ";
    for (int i = 0; i < E; i++) {
      cout << "[ " << edges[i][0] << " " << edges[i][1] << " ] ";
    }
    cout << "]" << endl;

    cout << "Result (DFS): " << (dfsApproach(V, edges) ? "Yes" : "No") << endl;
    cout << "Result (BFS): " << (bfsApproach(V, edges) ? "Yes" : "No") << endl;
  }

  return 0;
}

//---------------------------------DFS APPROACH---------------------------------
bool dfsApproach(int V, vector<vector<int>>& edges) {
  vector<vector<int>> adj(V);
  for (int i = 0; i < edges.size(); i++) {
    adj[edges[i][0]].emplace_back(edges[i][1]);
    adj[edges[i][1]].emplace_back(edges[i][0]);
  }

  vector<int> visited(V, 0);
  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      if (dfs(i, -1, adj, visited)) return true;
    }
  }

  return false;
}

bool dfs(int node, int parent, vector<vector<int>>& adj, vector<int>& visited) {
  visited[node] = 1;

  for (auto i : adj[node]) {
    if (!visited[i]) {
      if (dfs(i, node, adj, visited)) return true;
    } else if (parent != i) {
      return true;
    }
  }

  return false;
}

//---------------------------------BFS APPROACH---------------------------------
bool bfsApproach(int V, vector<vector<int>>& edges) {
  vector<vector<int>> adj(V);
  for (int i = 0; i < edges.size(); i++) {
    adj[edges[i][0]].emplace_back(edges[i][1]);
    adj[edges[i][1]].emplace_back(edges[i][0]);
  }

  vector<int> visited(V, 0);

  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      if (bfs(i, adj, visited)) return true;
    }
  }

  return false;
}

bool bfs(int node, vector<vector<int>>& adj, vector<int>& visited) {
  queue<pii> q;
  q.push({node, -1});
  visited[node] = 1;

  while (!q.empty()) {
    auto [v, parent] = q.front();
    q.pop();

    for (int j : adj[v]) {
      if (!visited[j]) {
        visited[j] = 1;
        q.push({j, v});
      } else if (j != parent) {
        return true;
      }
    }
  }

  return false;
}
