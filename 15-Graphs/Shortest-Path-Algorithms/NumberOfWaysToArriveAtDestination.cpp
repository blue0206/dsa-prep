/*
 * Problem: Number of Ways to Arrive at Destination (LeetCode #1976)
 * Link:
 * https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/
 *
 * Approach:
 * This problem requires finding not only the shortest time to travel from a
 * source to a destination but also the number of distinct paths that achieve
 * this shortest time. This can be solved by modifying Dijkstra's algorithm.
 *
 * We maintain two arrays: `distance[]`, which stores the shortest time to
 * reach each node, and `ways[]`, which stores the number of ways to reach
 * each node in that shortest time.
 *
 * 1.  When Dijkstra's algorithm finds a **new, shorter path** to a neighbor,
 *     we update its distance and set its `ways` count to be the same as the
 *     `ways` count of the current node.
 * 2.  When it finds an **alternative path of the exact same length**, we don't
 *     update the distance, but we add the `ways` count of the current node to
 *     the neighbor's `ways` count.
 *
 * Time Complexity: O(E log V), where V is the number of intersections (n) and E
 *                  is the number of roads.
 * Space Complexity: O(V + E) for the adjacency list, distance/ways arrays, and
 *                   priority queue.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

int countPaths(int n, const vector<vector<int>>& roads);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> roads(e, vector<int>(3));
    for (int i = 0; i < e; i++) {
      cin >> roads[i][0] >> roads[i][1] >> roads[i][2];
    }

    cout << "n: " << n << endl;
    cout << "Road-1\tRoad-2\tTime:" << endl;
    for (auto road : roads) {
      cout << road[0] << "\t" << road[1] << "\t" << road[2] << endl;
    }
    cout << endl;

    cout << "Number of Ways: " << countPaths(n, roads) << endl;

    cout << endl;
  }

  return 0;
}

int countPaths(int n, const vector<vector<int>>& roads) {
  const ll m = 1e9 + 7;

  vector<vector<pll>> adj(n);
  for (const auto& road : roads) {
    adj[road[0]].push_back({(ll)road[1], (ll)road[2]});
    adj[road[1]].push_back({(ll)road[0], (ll)road[2]});
  }

  const ll INF = LLONG_MAX / 2;
  vector<ll> ways(n, 0);
  vector<ll> distance(n, INF);
  priority_queue<pll, vector<pll>, greater<pll>> minheap;

  minheap.push({0, 0});
  distance[0] = 0;
  ways[0] = 1;
  while (!minheap.empty()) {
    auto [dist, road] = minheap.top();
    minheap.pop();

    if (distance[road] < dist) continue;

    for (auto [next, d] : adj[road]) {
      if (d + dist < distance[next]) {
        ways[next] = ways[road];
        distance[next] = d + dist;
        minheap.push({d + dist, next});
      } else if (d + dist == distance[next]) {
        ways[next] = ((ways[next] % m) + (ways[road] % m)) % m;
      }
    }
  }

  return ways[n - 1];
}
