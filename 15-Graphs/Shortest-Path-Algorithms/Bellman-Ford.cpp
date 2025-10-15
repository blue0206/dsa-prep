/*
 * Problem: Bellman-Ford
 * Link:
 * https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1
 *
 * Approach: The Bellman-Ford algorithm finds the shortest paths from a single
 *           source vertex to all other vertices in a weighted, directed graph.
 *           Unlike Dijkstra's, it can handle graphs with negative edge weights.
 *           1.  Initialize a `distance` array with infinity for all vertices
 *               and 0 for the source.
 *           2.  Relax all edges `V-1` times. A single relaxation step for an
 *               edge `u -> v` with weight `w` checks if `dist[u] + w < dist[v]`
 *               and updates `dist[v]` if true. After `i` iterations, the
 *               algorithm finds all shortest paths of at most `i` edges.
 *           3.  Perform one final (V-th) relaxation pass. If any distance is
 *               updated during this pass, it indicates a negative-weight cycle
 *               is reachable from the source.
 *
 * Time Complexity: O(V * E), where V is vertices and E is edges.
 * Space Complexity: O(V) for the distance array.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

vector<int> bellmanFord(int V, const vector<vector<int>>& edges, int src);

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

    cout << "Vertices: " << v << endl;
    cout << "Source Node: " << src << endl;
    cout << "Edges:" << endl;
    cout << "u\tv\tw" << endl;
    for (auto edge : edges) {
      cout << edge[0] << "\t" << edge[1] << "\t" << edge[2] << endl;
    }

    vector<int> distance = bellmanFord(v, edges, src);

    cout << "Shortest Paths from " << src << ":" << endl;
    for (int i = 0; i < v; i++) {
      cout << src << " -> " << i << ": " << distance[i] << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
  const int INF = 1e8;
  vector<int> distance(V, INF);

  distance[src] = 0;
  for (int i = 0; i < V - 1; i++) {
    for (int j = 0; j < edges.size(); j++) {
      int u = edges[j][0];
      int v = edges[j][1];
      int w = edges[j][2];

      if (distance[u] != INF && distance[v] > distance[u] + w) {
        distance[v] = distance[u] + w;
      }
    }
  }

  for (int i = 0; i < edges.size(); i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    int w = edges[i][2];

    if (distance[u] != INF && distance[v] > distance[u] + w) {
      return {-1};
    }
  }

  return distance;
}
