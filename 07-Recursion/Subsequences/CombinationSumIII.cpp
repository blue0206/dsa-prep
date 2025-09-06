/*
 * Problem: Combination Sum III (LeetCode #216)
 * Link: https://leetcode.com/problems/combination-sum-iii/description/
 *
 * Approach: This problem is a classic backtracking problem. We need to find all
 *           combinations of `k` unique numbers from 1 to 9 that sum up to `n`.
 *
 *           The solution uses a recursive helper function that builds a
 *           combination.
 *
 *           1. **Base Case:** The recursion successfully terminates if the
 *              current combination has `k` numbers and their sum is exactly `n`
 *              (i.e., the remaining target `n` is 0).
 *           2. **Recursive Step:** A `for` loop iterates through possible
 *              candidates, starting from `startNum` up to 9.
 *           3. **Choices:** For each candidate `i`, we "pick" it by adding it
 *              to the current combination and then make a recursive call for
 *              the next number (`i + 1`) with an updated target (`n - i`).
 *              After the call returns, we "un-pick" it (backtrack) to explore
 *              other paths.
 *           4. **Pruning:** The loop is optimized to `break` early if the
 *              current candidate `i` is larger than the remaining target `n`,
 *              or if the combination size has already reached `k`. This avoids
 *              exploring futile branches.
 *
 * Time Complexity: O(k * C(9, k)) - We explore C(9, k) combinations, and each
 *                  takes O(k) to copy.
 * Space Complexity: O(k) - The recursion depth is at most k.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

vvi combinationSum3(int k, int n);
void generateCombinations(vvi& ans, vi& combination, int k, int n,
                          int startNum);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int k, n;
    cin >> k >> n;

    cout << "k: " << k << "\nn: " << n << endl;

    vvi ans = combinationSum3(k, n);

    cout << "Combinations with Sum " << n << ": [ ";
    for (auto subset : ans) {
      cout << "[ ";
      for (int num : subset) {
        cout << num << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vvi combinationSum3(int k, int n) {
  vvi ans;
  vi combination;

  generateCombinations(ans, combination, k, n, 1);
  return ans;
}

void generateCombinations(vvi& ans, vi& combination, int k, int n,
                          int startNum) {
  if (n == 0 && combination.size() == k) {
    ans.emplace_back(combination);
    return;
  }

  for (int i = startNum; i < 10; i++) {
    // Pruning: If the current number is too large or we already have k numbers,
    // we can stop exploring this path. Since numbers are increasing, we can
    // break the loop.
    if (i > n || combination.size() >= k) {
      return;
    }

    combination.emplace_back(i);
    generateCombinations(ans, combination, k, n - i, i + 1);
    combination.pop_back();
  }
}
