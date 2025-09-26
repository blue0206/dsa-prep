/*
 * Problem: Cut in Half (ABC #424)
 * Rating: Beginner-E
 * Link: https://atcoder.jp/contests/abc424/tasks/abc424_e
 *
 * Approach: This is a greedy problem. To minimize the maximum length of any
 *           piece, we should always cut the currently longest piece. A
 *           max-priority queue is the perfect data structure to efficiently
 *           find the longest piece at each step.
 *
 *           To optimize the simulation, instead of performing one cut at a
 *           time, we group pieces of the same length. The priority queue will
 *           store pairs of `{length, count}`.
 *
 *           1.  **Greedy Simulation:** In a loop that runs until all `k` cuts
 *               are used, we extract the group of longest pieces from the PQ.
 *               We cut as many of these as possible, creating a new group of
 *               pieces with half the length and twice the count, and push it
 *               back into the PQ.
 *           2.  **Finding the x-th Smallest:** After all cuts, the PQ contains
 *               the final distribution of pieces. Since it's a max-heap, it
 *               gives us pieces from largest to smallest.
 *
 * Time Complexity: O((N + K) * log(N + K)) in the worst case, but much faster
 *                  in practice due to grouping.
 * Space Complexity: O(N + K)
 */

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << fixed << setprecision(10);

  int t;
  cin >> t;

  while (t--) {
    ll n, k, x;
    cin >> n >> k >> x;

    priority_queue<pair<double, ll>> pq;
    for (ll i = 0; i < n; i++) {
      double a;
      cin >> a;

      pq.push({a, 1});
    }

    // Greedily perform k cuts, always cutting the longest pieces.
    ll cuts = 0;
    while (cuts != k) {
      double len = pq.top().first;
      ll count = pq.top().second;
      pq.pop();

      if (cuts + count <= k) {
        pq.push({len / 2.0, count * 2LL});
        cuts += count;
      } else {
        ll possibleCuts = k - cuts;
        ll rem = count - possibleCuts;

        pq.push({len / 2.0, possibleCuts * 2LL});
        pq.push({len, rem});
        cuts = k;
      }
    }

    double ans = 0;
    while (!pq.empty()) {
      if (x <= pq.top().second) {
        ans = pq.top().first;
        break;
      }
      x -= pq.top().second;
      pq.pop();
    }

    cout << ans << "\n";
  }

  return 0;
}
