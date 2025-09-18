/*
 * Problem: Turtle vs. Rabbit Race: Optimal Trainings (Codeforces Div. 3 #1933E)
 * Rating: 1500
 * Link: https://codeforces.com/problemset/problem/1933/E
 *
 * Time Complexity: O(Q * log N)
 * Space Complexity: O(N) for the prefix sum array.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

ll calculatePerformance(vll& a, vll& pSum, ll l, ll u, ll mid) {
  ll total = pSum[mid];
  if (l > 0) {
    total -= pSum[l - 1];
  }

  ll performance = (total * (2 * u - total + 1)) / 2;

  return performance;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vll a(n), pSum(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    pSum[0] = a[0];
    for (int i = 1; i < n; i++) {
      pSum[i] = pSum[i - 1] + a[i];
    }

    int q;
    cin >> q;

    while (q--) {
      ll l, u;
      cin >> l >> u;
      l--;  // Make 0-indexed.

      ll low = l;
      ll high = n - 1;

      while (high - low > 4) {
        ll mid1 = low + (high - low) / 3;
        ll mid2 = high - (high - low) / 3;

        ll f1 = calculatePerformance(a, pSum, l, u, mid1);
        ll f2 = calculatePerformance(a, pSum, l, u, mid2);

        if (f1 > f2) {
          high = mid2;
        } else if (f1 < f2) {
          low = mid1;
        } else {
          low = mid1;
          high = mid2;
        }
      }

      ll maxPerformance = LLONG_MIN;
      ll ans = -1;
      for (int i = low; i <= high; i++) {
        ll performance = calculatePerformance(a, pSum, l, u, i);
        if (performance > maxPerformance) {
          ans = i + 1;  // Store 1-indexed.
          maxPerformance = performance;
        }
      }

      cout << ans << " ";
    }

    cout << "\n";
  }

  return 0;
}
