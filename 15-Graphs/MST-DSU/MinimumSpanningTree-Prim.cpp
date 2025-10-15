/*
 * Problem: Minimum Spanning Tree - Prim's Algorithm
 * Link: https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1
 *
 * Approach: Prim's algorithm is a greedy algorithm that finds a Minimum
 *           Spanning Tree (MST) for a weighted, undirected graph. It works by
 *           building the MST one vertex at a time.
 *           1.  Start with an arbitrary vertex (e.g., vertex 0).
 *           2.  Use a min-priority queue to store pairs of `{weight, node}`.
 *               Initially, it contains `{0, source_node}`.
 *           3.  While the priority queue is not empty, extract the node with
 *               the minimum edge weight.
 *           4.  If the node has already been included in the MST (is visited),
 *               skip it.
 *           5.  Otherwise, mark the node as visited, add the edge weight to the
 *               total MST sum, and add all its adjacent, unvisited neighbors
 *               to the priority queue.
 *
 * Time Complexity: O(E log V), where E is the number of edges and V is the
 *                  number of vertices.
 * Space Complexity: O(V + E) for the adjacency list and priority queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int spanningTree(int V, vector<vector<int>>& edges);

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

    cout << "Minimum Spanning Tree: " << spanningTree(n, edges) << endl;

    cout << endl;
  }

  return 0;
}

int spanningTree(int V, vector<vector<int>>& edges) {
  vector<vector<pii>> adj(V);
  for (int i = 0; i < edges.size(); i++) {
    adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
    adj[edges[i][1]].push_back({edges[i][0], edges[i][2]});
  }

  vector<int> visited(V, 0);
  priority_queue<pii, vector<pii>, greater<pii>> minheap;
  minheap.push({0, 0});

  int mstSum = 0;
  while (!minheap.empty()) {
    auto [wt, node] = minheap.top();
    minheap.pop();

    if (visited[node]) continue;

    visited[node] = 1;
    mstSum += wt;
    for (auto [next, w] : adj[node]) {
      if (!visited[next]) {
        minheap.push({w, next});
      }
    }
  }

  return mstSum;
}
