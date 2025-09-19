/*
 * Problem: Meeting on the Line (Codeforces Div. 2 #1730B)
 * Rating: 1600
 * Link: https://codeforces.com/problemset/problem/1730/B
 *
 * Approach: The problem asks to find an optimal meeting point `p` on a line
 *           that minimizes the maximum time required for any person to reach
 *           `p` and finish their task. The time for person `i` is
 *           `abs(x_i - p) + t_i`.
 *           We need to minimize `f(p) = max_i(abs(x_i - p) + t_i)`.
 *
 *           The function `abs(x_i - p)` is a V-shaped convex function. The sum
 *           of a convex function and a constant (`t_i`) is also convex. The
 *           maximum of several convex functions is also a convex function.
 *           Therefore, `f(p)` is a convex (unimodal) function.
 *
 *           This property allows us to use ternary search on the answer (the
 *           meeting point `p`) to find the point that minimizes `f(p)`.
 *
 * Time Complexity: O(N * log(Range/precision)) or O(N) for fixed iterations.
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using vd = vector<double>;
using pdd = pair<double, double>;
using vpdd = vector<pdd>;

double getMaxTime(vpdd& xt, double mid) {
  double maxTime = 0.0;
  for (int i = 0; i < xt.size(); i++) {
    double time = abs(xt[i].first - mid) + xt[i].second;
    maxTime = max(maxTime, time);
  }

  return maxTime;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    double n;
    cin >> n;

    vpdd xt(n);
    for (int i = 0; i < n; i++) cin >> xt[i].first;
    for (int i = 0; i < n; i++) cin >> xt[i].second;

    double low = 0.0;
    double high = 1e9;

    // Ternary search for the optimal meeting point `p`.
    // Run for a fixed number of iterations to achieve desired precision.
    for (int i = 0; i <= 200; i++) {
      double mid1 = low + (high - low) / 3.0;
      double mid2 = high - (high - low) / 3.0;

      double f1 = getMaxTime(xt, mid1);
      double f2 = getMaxTime(xt, mid2);

      if (f1 < f2) {
        high = mid2;
      } else if (f1 > f2) {
        low = mid1;
      } else {
        low = mid1;
        high = mid2;
      }
    }

    // The optimal meeting point is `high` (or `low`).
    cout << fixed << setprecision(7) << high << "\n";
  }

  return 0;
}
