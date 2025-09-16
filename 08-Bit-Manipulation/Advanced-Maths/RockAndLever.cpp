/*
 * Problem: Rock and Lever (Codeforces Div. 2 #1420B)
 * Rating: 1200
 * Link: https://codeforces.com/problemset/problem/1420/B
 *
 * Approach: The problem asks for the number of pairs (i, j) with i < j such
 *           that `a[i] & a[j] >= a[i] ^ a[j]`.
 *
 *           The core insight comes from analyzing the condition with respect to
 *           the most significant bit (MSB) of the numbers.
 *           - If two numbers `x` and `y` have the same MSB at position `k`,
 *             then the `k`-th bit of `x & y` will be 1, and the `k`-th bit of
 *             `x ^ y` will be 0. Since this is the highest bit, it guarantees
 *             that `x & y >= x ^ y`.
 *           - If `x` and `y` have different MSBs, let the MSB of `x` be at `k1`
 *             and `y` at `k2` (with `k1 > k2`). Then the MSB of `x ^ y` will be
 *             at `k1`, while the MSB of `x & y` will be at a position less than
 *             `k1`. This means `x ^ y > x & y`.
 *
 *           Therefore, the condition holds if and only if `a[i]` and `a[j]`
 *           have the same MSB. The algorithm is:
 *           1. Group all numbers by their MSB position. A map can be used for
 *              this.
 *           2. For each group of size `k`, any pair of numbers from that group
 *              will satisfy the condition. The number of such pairs is `kC2`,
 *              which is `k * (k - 1) / 2`.
 *           3. Sum the pair counts for all groups to get the total.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the input array + O(log(max(A))) for the map.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using umpi = unordered_map<int, int>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vi a(n);
    // Map to store the frequency of each MSB position.
    umpi msb;
    for (int i = 0; i < n; i++) {
      cin >> a[i];

      // __builtin_clz(x) counts leading zeros for a 32-bit integer.
      // Numbers with the same MSB will have the same count of leading zeros,
      // so we can use this value to group them.
      int posn = __builtin_clz(a[i]);
      msb[posn]++;
    }

    ll count = 0;
    // For each group of numbers with the same MSB,
    // if the group size is k, they form kC2 pairs.
    for (auto i : msb) {
      ll k = i.second;
      count += (k * (k - 1)) / 2;
    }

    cout << count << "\n";
  }

  return 0;
}
