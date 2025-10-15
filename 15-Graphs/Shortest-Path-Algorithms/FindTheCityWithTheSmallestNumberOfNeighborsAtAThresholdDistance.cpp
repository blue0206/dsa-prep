/*
 * Problem: Find the City With the Smallest Number of Neighbors at a Threshold
 *          Distance (LeetCode #1334)
 * Link:
 * https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/
 *
 * Approach:
 * The problem asks to find a city that can reach the fewest other cities
 * within a given distance threshold. This requires knowing the shortest path
 * between all pairs of cities.
 * 1.  The Floyd-Warshall algorithm is used to compute the all-pairs shortest
 *     paths. We initialize a distance matrix with edge weights and set the
 *     distance from each city to itself as 0.
 * 2.  After running the algorithm, the matrix contains the shortest distance
 *     between every pair of cities.
 * 3.  We then iterate through each city, count how many other cities are
 *     reachable within the `distanceThreshold`, and keep track of the city
 *     with the minimum count. If there's a tie, we choose the city with the
 *     greater index as per the problem statement.
 *
 * Time Complexity: O(N^3) due to the Floyd-Warshall algorithm.
 * Space Complexity: O(N^2) for the distance matrix.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, e, distanceThreshold;
    cin >> n >> e >> distanceThreshold;

    vector<vector<int>> edges(e, vector<int>(3));
    for (int i = 0; i < e; i++) {
      cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    cout << "n: " << n << endl;
    cout << "Distance Threshold: " << distanceThreshold << endl;
    cout << "City-1\tCity-2\tDistance:" << endl;
    for (auto edge : edges) {
      cout << edge[0] << "\t" << edge[1] << "\t" << edge[2] << endl;
    }
    cout << endl;

    cout << "City With the Smallest Number of Neighbors at a Threshold "
            "Distance: "
         << findTheCity(n, edges, distanceThreshold) << endl;

    cout << endl;
  }

  return 0;
}

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
  const int INF = 1e9;
  vector<vector<int>> dist(n, vector<int>(n, INF));

  for (int i = 0; i < edges.size(); i++) {
    int u = edges[i][0], v = edges[i][1], wt = edges[i][2];
    dist[u][v] = wt;
    dist[v][u] = wt;
  }

  for (int i = 0; i < n; i++) dist[i][i] = 0;

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

  int minCount = n;
  int ans = -1;
  for (int i = 0; i < n; i++) {
    int count = 0;
    for (int j = 0; j < n; j++) {
      if (i != j && dist[i][j] <= distanceThreshold) {
        count++;
      }
    }

    if (count <= minCount) {
      minCount = count;
      ans = i;
    }
  }

  return ans;
}
