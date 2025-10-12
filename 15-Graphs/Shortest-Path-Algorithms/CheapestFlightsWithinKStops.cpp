/*
 * Problem: Cheapest Flights Within K Stops (LeetCode #787)
 * Link:
 * https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
 *
 * Approach:
 * This problem is a variation of the single-source shortest path problem, but
 * with the added constraint of a maximum number of stops (`k`). A standard
 * Dijkstra's algorithm isn't a perfect fit because we might need to revisit
 * nodes via a more expensive path if that path uses fewer stops.
 *
 * This solution uses a modified BFS-like approach. The state stored in the
 * queue is `{price, stops, city}`. We also maintain a `prices` array to store
 * the minimum cost to reach each city found so far.
 *
 * When we explore from a city, we check its neighbors. If we find a path to a
 * neighbor with a lower cost than what's stored in the `prices` array, we
 * update the price and enqueue the new state. This prunes paths that are
 * already more expensive than another path found with the same or fewer stops.
 * The search is naturally constrained by the number of stops, as we do not
 * proceed further if `stops > k`.
 *
 * Time Complexity: O(E * K), where E is the number of flights. In the worst
 *                  case, we might explore each flight at each stop level.
 * Space Complexity: O(V + E + V*K) for the graph, prices array, and queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

struct Info {
  int price;
  int stops;
  int city;
};

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst,
                      int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, e, src, dst, k;
    cin >> n >> e >> src >> dst >> k;

    vector<vector<int>> flights(e, vector<int>(3));
    for (int i = 0; i < e; i++) {
      cin >> flights[i][0] >> flights[i][1] >> flights[i][2];
    }

    cout << "Flights:" << endl;
    cout << "From\tTo\tPrice" << endl;
    for (auto flight : flights) {
      cout << flight[0] << "\t" << flight[1] << "\t" << flight[2] << endl;
    }
    cout << endl;

    cout << "Source: " << src << endl;
    cout << "Destination: " << dst << endl;
    cout << "Number of Stops: " << k << endl;

    cout << "Cheapest Price: " << findCheapestPrice(n, flights, src, dst, k)
         << endl;

    cout << endl;
  }

  return 0;
}

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst,
                      int k) {
  vector<vector<pii>> adj(n);
  for (int i = 0; i < flights.size(); i++) {
    adj[flights[i][0]].push_back({flights[i][1], flights[i][2]});
  }

  const int INF = 1e9;
  vector<int> prices(n, INF);
  prices[src] = 0;

  queue<Info> q;
  q.push({0, 0, src});
  while (!q.empty()) {
    auto [price, stops, city] = q.front();
    q.pop();

    if (stops > k) continue;

    for (auto [next, p] : adj[city]) {
      if (stops <= k && price + p < prices[next]) {
        prices[next] = price + p;
        q.push({price + p, stops + 1, next});
      }
    }
  }

  return (prices[dst] == INF) ? -1 : prices[dst];
}
