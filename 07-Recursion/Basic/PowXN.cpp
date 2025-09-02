/*
 * Problem: Pow(x, n) (LeetCode #50)
 * Link: https://leetcode.com/problems/powx-n/description/
 */

#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Approach: This is a recursive, divide-and-conquer implementation of binary
 *           exponentiation. It calculates `x^(n/2)` recursively and then
 *           squares the result. If `n` is odd, it multiplies by an extra `x`.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) due to the recursion call stack.
 */
double recursiveApproach(double x, int n);

/**
 * Approach: This is an iterative implementation of binary exponentiation (also
 *           known as exponentiation by squaring). It works by repeatedly
 *           squaring `x` and reducing `n` by half. If `n` is odd at any step,
 *           the current `x` is multiplied into the result. This leverages the
 *           binary representation of `n` to compute the power in logarithmic
 *           time.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
double iterativeApproach(double x, int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    double x;
    cin >> x;
    int n;
    cin >> n;

    cout << "x: " << x << endl;
    cout << "n: " << n << endl;

    cout << "Result (Recursive Approach): " << recursiveApproach(x, n) << endl;
    cout << "Result (Iterative Approach): " << iterativeApproach(x, n) << endl;

    cout << endl;
  }

  return 0;
}

double recursiveApproach(double x, int n) {
  if (n == INT_MIN) {
    x *= x;
    n /= 2;
  }
  if (n < 0) {
    x = 1 / x;
    n = -n;
  }

  if (n == 0) return 1;
  if (n == 1) return x;

  double pw = recursiveApproach(x, n / 2);
  if (n & 1) {
    return (x * pw * pw);
  }
  return (pw * pw);
}

double iterativeApproach(double x, int n) {
  if (n == 0) return 1;
  if (n == 1) return x;

  if (n == INT_MIN) {
    x *= x;
    n /= 2;
  }

  if (n < 0) {
    x = 1 / x;
    n = -n;
  }

  double ans = 1.0;
  while (n > 0) {
    if (n & 1) {
      ans *= x;
    }
    x *= x;
    n /= 2;
  }

  return ans;
}
