/*
 * Problem: Sigma Cubes (ABC #425)
 * Rating: Beginner-A
 * Link: https://atcoder.jp/contests/abc425/tasks/abc425_a
 *
 * Approach: The problem asks for the value of the alternating sum of cubes:
 *           S = -1^3 + 2^3 - 3^3 + ... + (-1)^n * n^3.
 *           This can be solved by a direct simulation. We can loop from i = 1
 *           to n, calculate i^3, determine the correct sign based on whether i
 *           is odd or even, and add the result to a running total.
 *
 * Time Complexity: O(N)
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

  ll sum = 0;
  for (ll i = 1; i <= n; i++) {
    ll one = (i & 1) ? -1 : 1;
    ll cube = i * i * i;
    sum += (one * cube);
  }

  cout << sum << "\n";

  return 0;
}
