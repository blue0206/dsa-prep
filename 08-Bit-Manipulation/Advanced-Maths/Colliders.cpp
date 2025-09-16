/*
 * Problem: Colliders (Codeforces Div. 1 #154B)
 * Rating: 1600
 * Link: https://codeforces.com/problemset/problem/154/B
 *
 * Approach: The problem requires checking for conflicts when turning on
 * colliders. A conflict occurs if a new collider `i` is turned on while another
 *           collider `j` is already on, and `gcd(i, j) > 1`. This condition is
 *           equivalent to `i` and `j` sharing at least one common prime factor.
 *
 *           This suggests an efficient way to handle the problem:
 *           1.  **Pre-computation:** Use a Sieve to pre-compute the Smallest
 *               Prime Factor (SPF) for all numbers up to the maximum possible
 *               value (100000). This allows for very fast prime factorization.
 *           2.  **State Tracking:**
 *               - Use a boolean array `colliders` to keep track of which
 *                 colliders are currently on.
 *               - Use a map `primeConsumed` where `primeConsumed[p]` stores the
 *                 ID of the collider that is currently "using" the prime `p`.
 *           3.  **Handling Operations:**
 *               - **On (+ i):** Find all distinct prime factors of `i`. For
 *                 each prime factor `p`, check if `primeConsumed[p]` is
 *                 non-zero. If it is, a conflict exists with the collider
 *                 `primeConsumed[p]`. If no conflicts are found, turn on
 *                 collider `i` and update `primeConsumed[p] = i` for all its
 *                 prime factors.
 *               - **Off (- i):** Find all prime factors of `i` and set
 *                 `primeConsumed[p] = 0` for each, effectively releasing them.
 *
 * Time Complexity: O(MAX_N * log(log(MAX_N)) + M * log(N))
 * Space Complexity: O(MAX_N)
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vb = vector<bool>;
using umpi = unordered_map<int, int>;
using usi = unordered_set<int>;

const int MAX_N = 100001;

void computeSpf(vi& spf, int n);
vi getPrimeFactors(vi& spf, int n);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  // `colliders[i]` is true if collider `i` is on.
  vb colliders(n + 1, false);
  // `spf` array for Smallest Prime Factor pre-computation.
  vi spf(MAX_N);
  computeSpf(spf, MAX_N);
  // `primeConsumed[p] = i` means prime `p` is used by active collider `i`.
  umpi primeConsumed;

  while (m--) {
    char sign;
    cin >> sign;

    int i;
    cin >> i;

    if (sign == '+') {
      // Case 1: Turn on collider `i`.
      if (colliders[i]) {
        cout << "Already on\n";
      } else {
        int conflictCollider = -1;
        vi factors = getPrimeFactors(spf, i);

        // Check if any prime factor of `i` is already consumed by another
        // active collider.
        for (int j : factors) {
          if (primeConsumed[j] != 0) {
            conflictCollider = primeConsumed[j];
            break;
          }
        }

        // If no conflict, turn on the collider and mark its primes as consumed.
        if (conflictCollider == -1) {
          colliders[i] = true;
          for (int j : factors) {
            primeConsumed[j] = i;
          }
          cout << "Success\n";
        } else {
          cout << "Conflict with " << conflictCollider << "\n";
        }
      }

    } else {
      // Case 2: Turn off collider `i`.
      if (colliders[i]) {
        vi factors = getPrimeFactors(spf, i);

        // Release all prime factors consumed by this collider.
        for (int j : factors) {
          primeConsumed[j] = 0;
        }
        colliders[i] = false;
        cout << "Success\n";
      } else {
        cout << "Already off\n";
      }
    }
  }

  return 0;
}

// Pre-computes Smallest Prime Factor (SPF) for numbers up to `n`.
void computeSpf(vi& spf, int n) {
  iota(spf.begin(), spf.end(), 0);

  for (int i = 2; i * i < n; i++) {
    // If `i` is prime (its smallest prime factor is itself).
    if (spf[i] == i) {
      // Mark all multiples of `i`.
      for (int j = i * i; j < n; j += i) {
        if (spf[j] == j) {
          spf[j] = i;
        }
      }
    }
  }
}

// Returns a vector of distinct prime factors of `n` using the pre-computed SPF.
vi getPrimeFactors(vi& spf, int n) {
  usi factorSet;

  while (n > 1) {
    factorSet.insert(spf[n]);

    // Keep dividing `n` by its smallest prime factor.
    n = n / spf[n];
  }

  return vi(factorSet.begin(), factorSet.end());
}
