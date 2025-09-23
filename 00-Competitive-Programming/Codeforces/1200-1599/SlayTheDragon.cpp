/*
 * Problem: Slay the Dragon (Codeforces Educational Round Div. 2 #1574C)
 * Rating: 1300
 * Link: https://codeforces.com/problemset/problem/1574/C
 *
 * Approach: For each query, we need to select one hero to be the main
 *           attacker and the rest to be defenders. The goal is to minimize the
 *           coins spent. The cost for choosing hero `i` is:
 *           `cost(i) = max(0, x - a[i]) + max(0, y - (sum - a[i]))`
 *           where `a` is the sorted array of hero strengths and `sum` is the
 *           total strength.
 *
 *           The first term `max(0, x - a[i])` is non-increasing as `i`
 *           increases. The second term `max(0, y - sum + a[i])` is
 *           non-decreasing as `i` increases. The sum of these two functions
 *           results in a unimodal (V-shaped) function. This property allows us
 *           to use ternary search on the index `i` of the chosen hero to find
 *           the index that minimizes the total cost.
 *
 * Time Complexity: O(N log N + M log N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

ll calculateCost(vll& a, ll x, ll y, ll sum, ll mid) {
  ll defenderSum = sum - a[mid];
  ll cost = 0;

  if (a[mid] < x) cost += (x - a[mid]);
  if (defenderSum < y) cost += (y - defenderSum);

  return cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // cout << fixed << setprecision(8);

  int n;
  cin >> n;

  vll a(n);
  ll sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum += a[i];
  }
  sort(a.begin(), a.end());

  int m;
  cin >> m;

  while (m--) {
    ll x, y;
    cin >> x >> y;

    ll low = 0;
    ll high = n - 1;
    ll ans = -1;

    while (high - low >= 4) {
      ll mid1 = low + (high - low) / 3LL;
      ll mid2 = high - (high - low) / 3LL;

      ll f1 = calculateCost(a, x, y, sum, mid1);
      ll f2 = calculateCost(a, x, y, sum, mid2);

      if (f1 < f2) {
        high = mid2;
      } else if (f2 < f1) {
        low = mid1;
      } else {
        low = mid1;
        high = mid2;
      }
    }

    ll minCost = LLONG_MAX;
    for (int i = low; i <= high; i++) {
      ll cost = calculateCost(a, x, y, sum, i);
      minCost = min(minCost, cost);
    }

    cout << minCost << "\n";
  }

  return 0;
}
