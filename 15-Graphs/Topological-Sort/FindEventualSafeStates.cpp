/*
 * Problem: Find Eventual Safe States (LeetCode #802)
 * Link: https://leetcode.com/problems/find-eventual-safe-states/description/
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Approach: This solution uses Depth-First Search (DFS) with a 3-color
 *           system to identify nodes that are part of or lead to a cycle.
 *           - Color 0: Unvisited.
 *           - Color 1: Currently in the recursion stack (visiting).
 *           - Color 2: Visited and confirmed to be safe.
 *           A node is considered "safe" if all paths starting from it
 *           eventually lead to a terminal node (one with no outgoing edges).
 *           This means a safe node cannot be part of a cycle and cannot reach
 *           a cycle. The DFS marks a node as safe (color 2) only after
 *           verifying that all its neighbors are also safe.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the color array and recursion stack.
 */
vector<int> dfsApproach(vector<vector<int>>& graph);
void dfs(vector<vector<int>>& graph, vector<int>& safeStates,
         vector<int>& colors, int node);

/**
 * Approach: This solution uses a BFS-based topological sort on a reversed
 *           graph. The insight is that a node is safe if and only if it can
 *           reach a terminal node (a node with an out-degree of 0).
 *           1.  Reverse the graph: For every edge u -> v, create an edge v ->
 * u.
 *           2.  Calculate the out-degree of each node in the original graph.
 *           3.  Initialize a queue with all terminal nodes (out-degree 0).
 *           4.  Perform a topological sort (Kahn's algorithm) on the reversed
 *               graph. The nodes that are processed are precisely those that
 *               can reach a terminal node, making them the safe states.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E) for the reversed graph.
 */
vector<int> bfsApproach(vector<vector<int>>& graph);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
      int e;
      cin >> e;

      while (e--) {
        int val;
        cin >> val;

        graph[i].emplace_back(val);
      }
    }

    cout << "Graph: [";
    for (auto u : graph) {
      cout << "[ ";
      for (int v : u) {
        cout << v << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    // Uncomment the approach to use.
    vector<int> ans = bfsApproach(graph);
    // vector<int> ans = dfsApproach(graph);

    cout << "Safe States: [ ";
    for (int val : ans) {
      cout << val << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}

//------------------------------DFS APPROACH------------------------------------
vector<int> dfsApproach(vector<vector<int>>& graph) {
  int n = graph.size();

  vector<int> colors(n, 0);
  vector<int> safeStates;
  for (int i = 0; i < n; i++) {
    if (colors[i] == 0) {
      dfs(graph, safeStates, colors, i);
    }
  }

  sort(safeStates.begin(), safeStates.end());
  return safeStates;
}

void dfs(vector<vector<int>>& graph, vector<int>& safeStates,
         vector<int>& colors, int node) {
  colors[node] = 1;

  bool pointsToLoop = false;
  for (int next : graph[node]) {
    if (colors[next] == 1) pointsToLoop = true;
    if (colors[next] == 0) {
      dfs(graph, safeStates, colors, next);
      if (colors[next] == 1) pointsToLoop = true;
    }
  }

  if (!pointsToLoop) {
    safeStates.emplace_back(node);
    colors[node] = 2;
  }
}

//------------------------------BFS APPROACH------------------------------------
vector<int> bfsApproach(vector<vector<int>>& graph) {
  int n = graph.size();

  vector<int> outCount(n, 0);
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    for (int node : graph[i]) {
      adj[node].emplace_back(i);
      outCount[i]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (outCount[i] == 0) q.push(i);
  }

  vector<int> safeStates;
  while (!q.empty()) {
    int node = q.front();
    q.pop();

    safeStates.emplace_back(node);
    for (int next : adj[node]) {
      outCount[next]--;
      if (outCount[next] == 0) q.push(next);
    }
  }

  sort(safeStates.begin(), safeStates.end());
  return safeStates;
}
