/*
 * Problem: Nth Root of M
 *
 * Statement: Given two numbers N and M, find the Nth root of M. The nth root of
 *            a number M is defined as a number X when raised to the power N
 *            equals M. If the 'nth root is not an integer, return -1.
 *
 * Approach: This is a "Binary Search on Answers" problem. The answer (the Nth
 *           root) must lie within the range [1, M]. We can use binary search
 *           to efficiently find this value. For each `mid` value in our
 *           search, we check if `mid^N` is equal to, less than, or greater
 *           than M. Based on this comparison, we can eliminate half of the
 *           search space.
 *
 * Time Complexity: O(N * log M)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int nthRoot(int n, int m);

// Returns 0 if the Nth power of number is less than M.
// Returns 1 if the Nth power of number is equal to M.
// Returns 2 if the Nth power of number is greater than M.
int nthPower(int num, int power, int m);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    cout << nthRoot(n, m) << endl;

    cout << endl;
  }

  return 0;
}

int nthRoot(int n, int m) {
  if (m <= 1) return m;

  int low = 1;
  int high = m;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    int val = nthPower(mid, n, m);
    if (val == 1) {
      return mid;
    } else if (val == 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return -1;
}

int nthPower(int num, int power, int m) {
  ll ans = 1;

  for (int i = 0; i < power; i++) {
    ans *= num;
    // If at any point the calculated power exceeds m, we can stop early.
    if (ans > m) {
      return 2;
    }
  }

  if (ans < m) {
    return 0;
  }

  return 1;
}
