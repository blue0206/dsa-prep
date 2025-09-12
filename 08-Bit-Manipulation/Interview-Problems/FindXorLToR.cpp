/*
 * Problem: Find XOR of Numbers from L to R
 * Link:
 * https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1
 *
 * Approach: The problem of finding the XOR sum of a range `[L, R]` can be
 *           efficiently solved using properties of prefix XORs. The XOR sum of
 *           `[L, R]` is equivalent to `(XOR from 0 to R) ^ (XOR from 0 to
 *           L-1)`.
 *
 *           The core of the solution is a helper function, `xorSum(n)`, which
 *           calculates the XOR sum from 0 to `n`. This function exploits a
 *           repeating pattern that emerges every 4 numbers:
 *           - If `n % 4 == 0`, the XOR sum is `n`.
 *           - If `n % 4 == 1`, the XOR sum is `1`.
 *           - If `n % 4 == 2`, the XOR sum is `n + 1`.
 *           - If `n % 4 == 3`, the XOR sum is `0`.
 *
 *           By implementing this O(1) helper function, the XOR sum for the
 *           range `[L, R]` can be computed instantly as
 *           `xorSum(R) ^ xorSum(L-1)`.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
#include <algorithm>
#include <iostream>

using namespace std;

int findXOR(int l, int r);
int xorSum(int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int l, r;
    cin >> l >> r;

    cout << "L: " << l << endl;
    cout << "R: " << r << endl;

    cout << "XOR: " << findXOR(l, r) << endl;

    cout << endl;
  }

  return 0;
}

int findXOR(int l, int r) { return (xorSum(l - 1) ^ xorSum(r)); }

int xorSum(int n) {
  if (n % 4 == 0) {
    return n;
  } else if (n % 4 == 1) {
    return 1;
  } else if (n % 4 == 2) {
    return n + 1;
  }

  return 0;
}
