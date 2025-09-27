/*
 * Problem: Rotate and Sum Query (ABC #425)
 * Rating: Beginner-C
 * Link: https://atcoder.jp/contests/abc425/tasks/abc425_c
 *
 * Approach: A naive approach of actually rotating the array for each query
 *           would be too slow (O(N*Q)). A more efficient method is to simulate
 *           the rotation by simply tracking the starting index of the array
 *           and using a pre-computed prefix sum array to answer range sum
 *           queries in O(1).
 *
 *           1.  **Track Rotation:** We use a variable, `startIndex`, to
 *               represent the effective starting position of the array in the
 *               original, un-rotated sequence. A right shift by `C` means the
 *               new start is the element that was `C` positions to the left
 *               (cyclically). This is equivalent to a left shift of `C` on the
 *               starting pointer.
 *           2.  **Prefix Sum on Doubled Array:** To handle cyclic queries
 *               easily, we create a prefix sum array `psum` on a doubled
 *               version of the original array `a`. This allows us to query
 *               any subarray of length up to `N` starting at any index
 *               without worrying about wrapping around.
 *           3.  **Answering Queries:**
 *               -   **Type 1 (Rotate):** A right shift by `C` updates our
 *                   `startIndex` variable: `startIndex = (startIndex + C) % N`.
 *               -   **Type 2 (Sum):** A query for the range `[l, r]` in the
 *                   current rotated array corresponds to the range
 *                   `[startIndex + l, startIndex + r]` in our doubled prefix
 *                   sum array. The sum is calculated as
 *                   `psum[startIndex + r] - psum[startIndex + l - 1]`.
 *
 * Time Complexity: O(N + Q)
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n, q;
  cin >> n >> q;

  vll a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  ll startIndex = 0;  // Tracks the effective start of the array.

  // Create a prefix sum array on the doubled original array.
  vll psum(n * 2, 0);
  psum[0] = a[0];
  for (int i = 1; i < n * 2; i++) {
    psum[i] = psum[i - 1] + a[i % n];
  }

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      ll c;
      cin >> c;
      // A right shift of the array is equivalent to a left shift of the
      // starting pointer.
      startIndex = (startIndex + c) % n;
    } else {
      ll l, r;
      cin >> l >> r;
      l--;
      r--;

      // The query range [l, r] in the rotated array corresponds to
      // [startIndex + l, startIndex + r] in the doubled prefix sum array.
      ll lowIndex = startIndex + l;
      ll sumLow = (lowIndex <= 0) ? 0 : psum[lowIndex - 1];

      ll sum = psum[startIndex + r] - sumLow;

      cout << sum << "\n";
    }
  }

  return 0;
}
