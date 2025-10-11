/*
 * Problem: Shortest Path in Undirected Graph
 * Link:
 * https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1
 *
 * Approach: The shortest path in an unweighted (or unit-weighted) graph can be
 *           found using Breadth-First Search (BFS). BFS explores the graph
 *           level by level from the source node, guaranteeing that when we
 *           first encounter a node, it is through the shortest possible path.
 *           1. Initialize a distance array with -1 (or infinity).
 *           2. Create a queue and add the source node, setting its distance to
 *              0.
 *           3. While the queue is not empty, dequeue a node, and for each of
 *              its unvisited neighbors, update their distance and enqueue them.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the distance array and queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> shortestPath(const vector<vector<int>>& adj, int src);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, src;
    cin >> n >> src;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
      int m;
      cin >> m;

      while (m--) {
        int node;
        cin >> node;
        adj[i].emplace_back(node);
      }
    }

    vector<int> ans = shortestPath(adj, src);

    cout << "Shortest Path in Undirected Unit-Weighted Graph: " << endl;
    for (int i = 0; i < n; i++) {
      cout << src << " -> " << i << ": " << ans[i] << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<int> shortestPath(const vector<vector<int>>& adj, int src) {
  int n = adj.size();
  vector<int> nodeDistance(n, -1);
  queue<int> q;

  q.push(src);
  nodeDistance[src] = 0;

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int next : adj[node]) {
      if (nodeDistance[next] == -1) {  // If not visited
        nodeDistance[next] = nodeDistance[node] + 1;
        q.push(next);
      }
    }
  }

  return nodeDistance;
}
