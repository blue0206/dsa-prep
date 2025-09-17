/*
 * Problem: Hexagons (Codeforces Educational Round Div. 2 #630D)
 * Rating: 1100
 * Link: https://codeforces.com/problemset/problem/630/D
 *
 * Approach: This is a pattern recognition and combinatorial problem. The goal
 *           is to count the total number of hexagons within a distance `n`
 *           from a central hexagon.
 *           - At distance 0, there is 1 hexagon (the center).
 *           - At distance 1, there is a layer of 6 hexagons.
 *           - At distance `k`, there is a layer of `6*k` hexagons.
 *           The total number of hexagons is the sum of all hexagons from
 *           distance 0 to `n`.
 *           Total = 1 (for k=0) + 6*1 + 6*2 + ... + 6*n
 *                 = 1 + 6 * (1 + 2 + ... + n)
 *           The sum `1 + 2 + ... + n` is the n-th triangular number, which is
 *           `n * (n + 1) / 2`.
 *           So, the final formula is `1 + 6 * (n * (n + 1) / 2)`.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <iostream>

using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n;
  cin >> n;

  // Calculate 1 + 6 * (n * (n + 1) / 2)
  ll res = (n * (n + 1)) / 2;
  res = (res * 6LL) + 1LL;

  cout << res << "\n";

  return 0;
}
