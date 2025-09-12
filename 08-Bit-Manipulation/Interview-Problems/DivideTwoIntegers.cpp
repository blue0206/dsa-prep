/*
 * Problem: Divide Two Integers (LeetCode #29)
 * Link: https://leetcode.com/problems/divide-two-integers/description/
 *
 * Approach: This problem is solved by simulating division using bit
 *           manipulation and subtraction, as the use of `*`, `/`, and `%` is
 *           forbidden.
 *
 *           1.  **Sign Handling:** The sign of the final result is determined
 *               first using XOR and stored separately. The rest of the
 *               calculation is performed on the absolute values of the dividend
 *               and divisor.
 *           2.  **Absolute Values:** To prevent overflow when dealing with
 *               `INT_MIN`, the dividend and divisor are converted to `long
 *               long`.
 *           3.  **Optimized Subtraction:** Instead of subtracting the divisor
 *               one by one (which would be too slow), we subtract multiples of
 *               the divisor that are powers of two.
 *               -   In each step, we find the largest `(divisor * 2^k)` that is
 *                   less than or equal to the current dividend.
 *               -   This is done by left-shifting the divisor (`mask <<= 1`)
 *                   and a counter (`shiftVal *= 2`) until the `mask` exceeds
 *                   the dividend.
 *               -   We then subtract this `mask` from the dividend and add the
 *                   `shiftVal` (which is `2^k`) to our quotient.
 *           4.  **Edge Cases:** The final result is clamped to the `INT_MAX`
 *               and `INT_MIN` range to handle overflow as required.
 *
 * Time Complexity: O((log N)^2), where N is the dividend.
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

int divide(int dividend, int divisor);
ll solve(ll dividend, ll divisor);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int divisor, dividend;
    cin >> divisor >> dividend;

    cout << "Divisor: " << divisor << endl;
    cout << "Dividend: " << dividend << endl;

    cout << "Quotient: " << divide(dividend, divisor) << endl;

    cout << endl;
  }

  return 0;
}

int divide(int dividend, int divisor) {
  int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
  ll count = solve(dividend, divisor) * sign;

  if (count > INT_MAX)
    return INT_MAX;
  else if (count < INT_MIN)
    return INT_MIN;

  return (int)count;
}

ll solve(ll dividend, ll divisor) {
  if (dividend < 0) dividend *= -1;
  if (divisor < 0) divisor *= -1;

  ll res = 0;
  while (dividend - divisor >= 0) {
    ll mask = divisor;
    ll shiftVal = 1;
    while ((mask << 1) < dividend) {
      mask <<= 1;
      shiftVal *= 2LL;
    }

    dividend -= mask;
    res += shiftVal;
  }

  return res;
}
