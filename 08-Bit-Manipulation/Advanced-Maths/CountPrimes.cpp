/*
 * Problem: Count Primes (LeetCode #204)
 * Link: https://leetcode.com/problems/count-primes/description/
 *
 * Approach: This problem is solved using the Sieve of Eratosthenes algorithm,
 *           which is a highly efficient way to find all prime numbers up to a
 *           specified integer.
 *           1.  Create a boolean array `isPrime` of size `n`, initializing all
 *               entries to `true`. A value `isPrime[i]` will be `false` if `i`
 *               is not a prime, and `true` otherwise.
 *           2.  Iterate from `p = 2` up to `sqrt(n)`.
 *           3.  If `isPrime[p]` is still `true`, it means `p` is a prime
 *               number.
 *           4.  For each prime `p`, mark all of its multiples (starting from
 *               `p*p`) as not prime by setting `isPrime[i] = false`.
 *           5.  Finally, count the number of `true` values in the `isPrime`
 *               array from 2 to `n-1`.
 *
 * Time Complexity: O(N * log(log N))
 * Space Complexity: O(N)
 */

#include <iostream>
#include <vector>

using namespace std;

int countPrimes(int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    cout << "n: " << n << endl;

    cout << "Prime Count: " << countPrimes(n) << endl;

    cout << endl;
  }

  return 0;
}

int countPrimes(int n) {
  if (n <= 2) {
    return 0;
  }
  vector<bool> isPrime(n, true);

  // Sieve of Eratosthenes: Mark non-prime numbers
  for (int p = 2; p * p < n; p++) {
    if (isPrime[p]) {
      // Mark all multiples of p starting from p*p
      for (int i = p * p; i < n; i += p) {
        isPrime[i] = false;
      }
    }
  }

  // Count prime numbers
  int count = 0;
  for (int p = 2; p < n; p++) {
    if (isPrime[p]) count++;
  }
  return count;
}
