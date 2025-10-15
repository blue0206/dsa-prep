/*
 * Problem: Floyd Warshall
 * Link:
 * https://www.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1
 *
 * Approach:
 * The Floyd-Warshall algorithm is a dynamic programming algorithm for finding
 * the shortest paths between all pairs of vertices in a weighted graph. It can
 * handle both positive and negative edge weights but not negative cycles.
 * 1.  Initialize a distance matrix `dist[V][V]` with the direct edge weights.
 *     If there is no edge between `i` and `j`, `dist[i][j]` is infinity. The
 *     distance from a vertex to itself, `dist[i][i]`, is 0.
 * 2.  Iterate through all vertices `k` from 0 to `V-1`. For each `k`, treat it
 *     as an intermediate vertex in the path from `i` to `j`.
 * 3.  Update the shortest path: `dist[i][j] = min(dist[i][j], dist[i][k] +
 *     dist[k][j])`.
 * After iterating through all possible intermediate vertices, the matrix will
 * contain the all-pairs shortest paths.
 *
 * Time Complexity: O(V^3), where V is the number of vertices.
 * Space Complexity: O(V^2) for the distance matrix.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void floydWarshall(vector<vector<int>>& dist);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> dist[i][j];
      }
    }

    cout << "Distance Matrix: [ ";
    for (auto row : dist) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    floydWarshall(dist);

    cout << "Shortest Path Matrix: [ ";
    for (auto row : dist) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

void floydWarshall(vector<vector<int>>& dist) {
  const int n = dist.size();
  const int INF = 1e8;

  for (int node = 0; node < n; node++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][node] != INF && dist[node][j] != INF) {
          int newDist = dist[i][node] + dist[node][j];
          dist[i][j] = min(dist[i][j], newDist);
        }
      }
    }
  }
}
