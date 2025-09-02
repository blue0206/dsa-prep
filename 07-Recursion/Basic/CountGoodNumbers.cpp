/*
 * Problem: Count Good Numbers (LeetCode #1922)
 * Link: https://leetcode.com/problems/count-good-numbers/description/
 *
 * Approach: This is a combinatorial problem that can be solved with modular
 *           exponentiation.
 *           A "good" number string of length `n` has digits at even indices
 *           from the set {0, 2, 4, 6, 8} (5 choices) and digits at odd indices
 *           from the set {2, 3, 5, 7} (4 choices).
 *           - The number of even indices is `ceil(n/2.0)`, which is `(n+1)/2`.
 *           - The number of odd indices is `floor(n/2.0)`, which is `n/2`.
 *           The total count is `(5^num_even_indices) * (4^num_odd_indices)`.
 *           Since `n` can be large, we must use a modular exponentiation
 *           (binary exponentiation) to compute the powers modulo 10^9 + 7.
 *
 * Time Complexity: O(log n) due to the binary exponentiation.
 * Space Complexity: O(log n) for the recursion call stack.
 */

#include <algorithm>
#include <iostream>

using namespace std;
const long long M = 1e9 + 7;

int countGoodNumbers(long long n);
long long myPow(long long x, long long n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    long long n;
    cin >> n;

    cout << "n: " << n << endl;
    cout << "Good Numbers Count: " << countGoodNumbers(n) << endl;

    cout << endl;
  }

  return 0;
}

int countGoodNumbers(long long n) {
  // Number of even indices (0, 2, 4, ...): (n+1)/2
  // There are 5 choices for even indices {0, 2, 4, 6, 8}.
  long long even_indices = (n + 1) / 2;

  // Number of odd indices (1, 3, 5, ...): n/2
  // There are 4 choices for odd indices {2, 3, 5, 7}.
  long long odd_indices = n / 2;

  long long pow5 = myPow(5, even_indices);
  long long pow4 = myPow(4, odd_indices);

  return (int)((pow5 * pow4) % M);
}

long long myPow(long long x, long long n) {
  if (n == 0) return 1;
  if (n == 1) return x % M;

  long long pw = myPow(x, n / 2) % M;
  long long res = (pw * pw) % M;

  if (n & 1) {
    return ((x % M) * (res % M)) % M;
  }
  return res;
}
