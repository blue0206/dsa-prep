/*
 * Problem: Almost Prime (Codeforces Beta Round #26A)
 * Rating: 900
 * Link: https://codeforces.com/contest/26/problem/A
 *
 * Approach: An "almost prime" number is a positive integer that has exactly
 *           two distinct prime factors. This problem can be solved by finding
 *           the number of distinct prime factors for every number up to `n`
 *           and then counting how many of them have exactly two.
 *
 *           The solution uses a clever, modified Sieve of Eratosthenes:
 *           1. Create an integer array, `primes`, of size `n+1`.
 *           2. Initialize `primes[i] = i` for all `i`. This serves as a dual-
 *              purpose flag: if `primes[i] == i`, `i` is prime; otherwise, it
 *              stores the count of distinct prime factors.
 *           3. Iterate from `i = 2` to `n`.
 *           4. If `primes[i] == i`, we've found a prime number `i`.
 *           5. For this prime `i`, iterate through all its multiples `j` (from
 *              `2*i` to `n`). If `primes[j]` is still `j`, it's the first prime
 *              factor we've found for `j`, so we set `primes[j] = 1`.
 * Otherwise, we increment `primes[j]` to count another distinct prime factor.
 *
 * Time Complexity: O(N * log(log N))
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  // `primes[i]` will be used to store the count of distinct prime factors of i.
  // It's initialized with `primes[i] = i` to also act as a primality test:
  // if `primes[i] == i`, then `i` is a prime number.
  vi primes(n + 1);
  iota(primes.begin(), primes.end(), 0);

  // Modified Sieve to count distinct prime factors.
  for (int i = 2; i <= n; i++) {
    // If `primes[i] == i`, it means 'i' is a prime number.
    if (primes[i] == i) {
      // For this prime 'i', iterate through all its multiples.
      for (int j = i + i; j <= n; j += i) {
        // If `primes[j] == j`, this is the first prime factor found for `j`.
        // We initialize its count to 1.
        if (primes[j] == j) {
          primes[j] = 1;
        } else {
          // Otherwise, `j` has been visited by another prime factor.
          // We increment its count of distinct prime factors.
          primes[j]++;
        }
      }
    }
  }

  // Count the numbers with exactly 2 distinct prime factors.
  int count = 0;
  for (int i = 4; i < primes.size(); i++) {
    if (primes[i] == 2) {
      count++;
    }
  }

  cout << count << "\n";

  return 0;
}
