/*
 * Problem: Network Delay Time (LeetCode #743)
 * Link: https://leetcode.com/problems/network-delay-time/description/
 *
 * Approach: This problem asks for the minimum time it takes for a signal to
 *           travel from a source node `k` to all other nodes in the network.
 *           This is a classic single-source shortest path problem on a
 *           weighted, directed graph.
 *
 *           Dijkstra's algorithm is the ideal solution.
 *           1.  Build an adjacency list to represent the graph.
 *           2.  Use a min-priority queue to always explore the node that is
 *               reachable in the shortest amount of time from the source.
 *           3.  After finding the shortest path to all nodes, the answer is the
 *               maximum shortest path time. If any node is unreachable, it's
 *               impossible for the signal to reach everyone, so we return -1.
 *
 * Time Complexity: O(E log V), where V is the number of nodes (n) and E is the
 *                  number of connections (times.size()).
 * Space Complexity: O(V + E) for the adjacency list and priority queue.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int networkDelayTime(const vector<vector<int>>& times, int n, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, e, k;
    cin >> n >> e >> k;

    vector<vector<int>> times(e, vector<int>(3));
    for (int i = 0; i < e; i++) {
      cin >> times[i][0] >> times[i][1] >> times[i][2];
    }

    cout << "n: " << n << endl;
    cout << "k: " << k << endl;
    cout << "Source\tDestination\tTime:" << endl;
    for (auto time : times) {
      cout << time[0] << "\t" << time[1] << "\t" << time[2] << endl;
    }
    cout << endl;

    cout << "Minimum Time: " << networkDelayTime(times, n, k) << endl;

    cout << endl;
  }

  return 0;
}

int networkDelayTime(const vector<vector<int>>& times, int n, int k) {
  vector<vector<pii>> adj(n + 1);
  for (const auto& time : times) {
    adj[time[0]].push_back({time[1], time[2]});
  }

  const int INF = 1e9;
  vector<int> receiveTime(n + 1, INF);
  priority_queue<pii, vector<pii>, greater<pii>> minheap;

  minheap.push({0, k});
  receiveTime[k] = 0;
  while (!minheap.empty()) {
    auto [time, node] = minheap.top();
    minheap.pop();

    if (receiveTime[node] < time) continue;

    for (auto [next, t] : adj[node]) {
      if (t + time < receiveTime[next]) {
        receiveTime[next] = t + time;
        minheap.push({t + time, next});
      }
    }
  }

  int maxTime = 0;
  for (int i = 1; i <= n; i++) {
    if (receiveTime[i] == INF) return -1;
    maxTime = max(maxTime, receiveTime[i]);
  }

  return maxTime;
}
