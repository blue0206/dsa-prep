/*
 * Problem: Dijkstra Algorithm
 * Link:
 * https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
 *
 * Approach: This implementation uses Dijkstra's algorithm with a min-priority
 *           queue to efficiently find the single-source shortest paths in a
 *           weighted graph with non-negative edge weights.
 *
 *           1.  A min-priority queue stores pairs of `{distance, node}`. It
 *               always provides the unvisited node with the smallest known
 *               distance from the source.
 *           2.  A `distance` array is initialized to infinity for all nodes
 *               except the source, which is 0.
 *           3.  The algorithm repeatedly extracts the minimum distance node
 *               from the queue and "relaxes" its adjacent edges, updating the
 *               distances of its neighbors if a shorter path is found through
 *               the current node.
 *
 * Time Complexity: O(E log V), where E is edges and V is vertices.
 * Space Complexity: O(V + E) for the adjacency list and priority queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

vector<int> dijkstra(int V, const vector<vector<int>>& edges, int src);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int v, e, src;
    cin >> v >> e >> src;

    vector<vector<int>> edges(e, vector<int>(3));

    for (int i = 0; i < e; i++) {
      cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    vector<int> ans = dijkstra(v, edges, src);

    cout << "Shortest Path in Undirected Non-Negative Weighted Graph: " << endl;
    for (int i = 0; i < v; i++) {
      cout << src << " -> " << i << ": " << ans[i] << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<int> dijkstra(int V, const vector<vector<int>>& edges, int src) {
  vector<vector<pii>> adj(V);
  for (const auto& edge : edges) {
    int u = edge[0];
    int v = edge[1];
    int wt = edge[2];

    adj[u].push_back({v, wt});
    adj[v].push_back({u, wt});
  }

  const int INF = 1e9;
  vector<int> distance(V, INF);
  priority_queue<pii, vector<pii>, greater<pii>> minheap;

  minheap.push({0, src});
  distance[src] = 0;
  while (!minheap.empty()) {
    auto [dist, node] = minheap.top();
    minheap.pop();

    if (distance[node] < dist) continue;

    for (auto [next, wt] : adj[node]) {
      if (distance[next] > dist + wt) {
        minheap.push({dist + wt, next});
        distance[next] = dist + wt;
      }
    }
  }

  for (int i = 0; i < V; i++) {
    if (distance[i] == INF) distance[i] = -1;
  }

  return distance;
}
