/*
 * Problem: Beautiful Numbers (Codeforces Div. 2 #300C)
 * Link: https://codeforces.com/problemset/problem/300/C
 *
 * Approach: This is a combinatorial problem. A number is "beautiful" if it
 *           only contains digits `a` and `b`. We need to find the count of
 *           `n`-digit numbers that are beautiful, and whose sum of digits is
 *           also a beautiful number.
 *
 *           1.  **Combinations:** An `n`-digit beautiful number is formed by
 *               some combination of digits `a` and `b`. We can iterate through
 *               all possible compositions: `r` occurrences of digit `a` and
 *               `(n-r)` occurrences of digit `b`, where `r` ranges from `0` to
 *               `n`.
 *           2.  **Sum of Digits:** For each composition (defined by `r`), the
 *               sum of digits is `S = a*r + b*(n-r)`.
 *           3.  **Check Sum:** We must check if this sum `S` is itself a
 *               beautiful number (i.e., all its digits are either `a` or `b`).
 *           4.  **Count Permutations:** If the sum `S` is beautiful, we count
 *               how many `n`-digit numbers can be formed with `r` `a`'s and
 *               `(n-r)` `b`'s. This is given by the binomial coefficient `nCr`.
 *           5.  **Modular Arithmetic:** Since `n` can be large, `nCr` must be
 *               calculated modulo `10^9 + 7`. This is done efficiently by
 *               pre-computing factorials and their modular inverses.
 *
 * Time Complexity: O(N * log(N)), for iterating N times and checking the sum.
 * Space Complexity: O(N), for storing factorials and inverse factorials.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const ll M = 1e9 + 7;
using vll = vector<ll>;

ll nCr(vll& fact, vll& invFact, ll n, ll r, ll m);
bool goodSum(ll sum, int a, int b);
void computeFact(vll& fact, vll& invFact, ll n, ll m);
ll modInverse(ll b, ll m);
ll myPow(ll x, ll n, ll m);

// Main logic
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll a, b, n;
  cin >> a >> b >> n;

  // Pre-compute factorials and their modular inverses for nCr calculation.
  vll fact(n + 1), invFact(n + 1);
  computeFact(fact, invFact, n, M);

  ll count = 0;
  // Iterate through all possible counts `r` of digit `a`.
  for (int r = 0; r <= n; r++) {
    ll sum = (a * r) + ((n - r) * b);

    // Check if the sum of digits is a "beautiful" number.
    if (goodSum(sum, a, b)) {
      count = ((count % M) + (nCr(fact, invFact, n, r, M) % M)) % M;
    }
  }

  cout << count << "\n";

  return 0;
}

// Calculates nCr % m using pre-computed factorials and inverse factorials.
ll nCr(vll& fact, vll& invFact, ll n, ll r, ll m) {
  if (r > n) {
    return 0;
  }

  ll ans = fact[n] % m;

  ans = ((ans % m) * (invFact[r] % m)) % m;
  ans = ((ans % m) * (invFact[n - r] % m)) % m;

  return ans;
}

// Checks if a number's decimal representation consists only of digits a and b.
bool goodSum(ll sum, int a, int b) {
  while (sum > 0) {
    int digit = sum % 10;
    if (digit != a && digit != b) {
      return false;
    }
    sum /= 10;
  }

  return true;
}

// Pre-computes factorials and their modular inverses up to n.
void computeFact(vll& fact, vll& invFact, ll n, ll m) {
  fact[0] = 1;
  invFact[0] = 1;

  ll factorial = 1;
  for (ll i = 1; i < n + 1; i++) {
    factorial = ((factorial % m) * (i % m)) % m;

    fact[i] = factorial;
  }

  // Compute inverse of n! using Fermat's Little Theorem.
  invFact[n] = modInverse(fact[n], m);

  // Compute inverse factorials from n-1 down to 0 using the relation:
  // invFact[i] = invFact[i+1] * (i+1)
  for (ll i = n - 1; i >= 0; i--) {
    invFact[i] = ((invFact[i + 1] % m) * ((i + 1) % m)) % m;
  }
}

// Calculates modular inverse using Fermat's Little Theorem: a^(m-2) % m.
ll modInverse(ll b, ll m) {
  ll bInverse = myPow(b, m - 2, m);
  return bInverse;
}

// Calculates (x^n) % m using iterative binary exponentiation.
ll myPow(ll x, ll n, ll m) {
  if (n == 0) return 1;
  if (n == 1) return x % m;

  ll res = 1;
  while (n > 0) {
    if (n & 1) {
      res = ((res % m) * (x % m)) % m;
    }
    x = ((x % m) * (x % m)) % m;
    n /= 2;
  }

  return res;
}
