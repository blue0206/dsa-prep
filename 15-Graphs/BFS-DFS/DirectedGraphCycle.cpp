/*
 * Problem: Directed Graph Cycle
 * Link:
 * https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
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
 * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the colors array and recursion stack.
 */
bool isCyclic(int V, vector<vector<int>>& adj);
bool dfs(const vector<vector<int>>& adjList, vector<int>& colors, int node);

/**
 * Approach: This solution uses Breadth-First Search (BFS) and the concept of
 *           in-degrees, also known as Kahn's algorithm for topological sort.
 *           A directed graph has a cycle if and only if it does not have a
 *           valid topological sort.
 *           1.  Calculate the in-degree (number of incoming edges) for every
 *               vertex.
 *           2.  Initialize a queue with all vertices that have an in-degree of
 *               0.
 *           3.  While the queue is not empty, dequeue a vertex, add it to the
 *               sorted list (or simply count it), and decrement the in-degree
 *               of all its neighbors.
 *           4.  If a neighbor's in-degree becomes 0, enqueue it.
 *           5.  If the final count of sorted vertices is not equal to the total
 *               number of vertices, the graph contains a cycle.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */
bool bfsApproach(int V, vector<vector<int>>& adj);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int v;
    cin >> v;  // Number of vertices

    int e;
    cin >> e;  // Number of edges

    vector<vector<int>> adj(v);
    for (int i = 0; i < e; i++) {
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

    cout << "Has Cycle (DFS): " << (isCyclic(v, adj) ? "True" : "False")
         << endl;
    cout << "Has Cycle (BFS): " << (bfsApproach(v, adj) ? "True" : "False")
         << endl;
  }

  return 0;
}

//------------------------------DFS APPROACH------------------------------------
bool isCyclic(int V, vector<vector<int>>& adj) {
  // The 'adj' parameter is already an adjacency list from main.
  vector<int> colors(V, 0);
  for (int i = 0; i < V; i++) {
    if (colors[i] == 0 && dfs(adj, colors, i)) {
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

//------------------------------BFS APPROACH------------------------------------
bool bfsApproach(int V, vector<vector<int>>& adj) {
  vector<int> inCount(V, 0);
  for (int i = 0; i < V; i++) {
    for (int node : adj[i]) {
      inCount[node]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < V; i++) {
    if (inCount[i] == 0) q.push(i);
  }

  int count = 0;
  while (!q.empty()) {
    int node = q.front();
    q.pop();

    count++;
    for (int next : adj[node]) {
      inCount[next]--;
      if (inCount[next] == 0) q.push(next);
    }
  }

  return count != V;
}
