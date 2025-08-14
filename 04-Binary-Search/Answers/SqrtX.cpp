/*
 * Problem: Sqrt(x) (LeetCode #69)
 * Link: https://leetcode.com/problems/sqrtx/description/
 *
 * Approach: The problem of finding the integer square root of a number `x` can
 *           be solved by searching for the answer in a range of possible
 *           values. This is a classic "Binary Search on Answers" problem.
 *           1. The search space for the answer is from 1 to x. An optimization
 *              is to search from 1 to x/2, as the root is never larger.
 *           2. We use binary search to find the largest integer `mid` such that
 *              `mid * mid <= x`. This is equivalent to finding the "floor" of
 *              the true square root.
 *           3. If `mid * mid <= x`, `mid` is a potential answer, so we store it
 *              and search for a larger potential answer in the right half.
 *           4. If `mid * mid > x`, `mid` is too large, so we search in the
 *              left.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int mySqrt(int x);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int x;
    cin >> x;

    cout << "Sqrt(" << x << "): " << mySqrt(x) << endl;

    cout << endl;
  }

  return 0;
}

int mySqrt(int x) {
  if (x <= 1) return x;

  // The search space for the answer can be optimized to [1, x/2].
  int low = 1;
  int high = x / 2;
  int ans = 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    long long val = 1LL * mid * mid;
    if (val <= x) {
      // mid is a potential answer. Store it and look for a larger one.
      ans = mid;
      low = mid + 1;
    } else {
      // mid is too large.
      high = mid - 1;
    }
  }

  // We can also return high.
  return ans;
}
