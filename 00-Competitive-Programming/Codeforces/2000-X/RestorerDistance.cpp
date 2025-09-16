/*
 * Problem: Restorer Distance (Codeforces Div. 2 #1355E)
 * Rating: 2100
 * Link: https://codeforces.com/problemset/problem/1355/E
 *
 * Approach: The problem asks to find a target height `h` for all pillars that
 *           minimizes the total cost. The cost function, when plotted against
 *           the target height `h`, is convex (unimodal). This property allows
 *           us to use ternary search to find the minimum point of this
 *           function.
 *
 *           1.  **Ternary Search on Answer:** The answer is the optimal target
 *               height `h`. We can search for this `h` in a reasonable range
 *               (e.g., `[0, 10^9]`). Ternary search is used to efficiently
 *               narrow down this range to find the height that yields the
 *               minimum cost.
 *           2.  **Cost Calculation:** For any given target height `h`, we
 *               calculate the cost in O(N) by iterating through the pillars.
 *
 * Time Complexity: O(N * log N + N * log(Range))
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

ll calculateCost(vll& pillars, ll a, ll r, ll m, ll h) {
  ll cost = 0;

  if (m < (a + r)) {
    // Case 1: Moving blocks is cheaper than adding and removing separately.
    ll extras = 0;
    // Calculate total extra bricks.
    for (int i = pillars.size() - 1; i >= 0; i--) {
      if (pillars[i] <= h) break;
      extras += (pillars[i] - h);
    }

    for (int i = 0; i < pillars.size(); i++) {
      if (pillars[i] >= h) break;
      ll required = h - pillars[i];

      if (extras >= required) {
        cost += (required * m);
        extras -= required;
      } else {
        required -= extras;
        cost += (extras * m);
        cost += (required * a);

        extras = 0;
      }
    }

    if (extras > 0) {
      cost += (extras * r);
    }

  } else {
    // Case 2: It's cheaper to add/remove independently.
    for (int i = 0; i < pillars.size(); i++) {
      if (pillars[i] < h) {
        cost += ((h - pillars[i]) * a);
      } else {
        cost += ((pillars[i] - h) * r);
      }
    }
  }

  return cost;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n, a, r, m;
  cin >> n >> a >> r >> m;

  vll pillars(n);
  for (int i = 0; i < n; i++) {
    cin >> pillars[i];
  }
  sort(pillars.begin(), pillars.end());

  ll low = pillars[0];
  ll high = pillars[n - 1];

  while (high - low >= 3LL) {
    ll mid1 = low + (high - low) / 3;
    ll mid2 = high - (high - low) / 3;

    ll f1 = calculateCost(pillars, a, r, m, mid1);
    ll f2 = calculateCost(pillars, a, r, m, mid2);

    if (f1 < f2) {
      high = mid2;
    } else if (f1 > f2) {
      low = mid1;
    } else {
      low = mid1;
      high = mid2;
    }
  }

  ll minCost = LLONG_MAX;
  for (ll i = low; i <= high; i++) {
    ll cost = calculateCost(pillars, a, r, m, i);
    minCost = min(cost, minCost);
  }

  cout << minCost << "\n";

  return 0;
}
