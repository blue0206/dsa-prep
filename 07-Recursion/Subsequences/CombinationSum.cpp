/*
 * Problem: Combination Sum (LeetCode #39)
 * Link: https://leetcode.com/problems/combination-sum/description/
 *
 * Approach: This problem is solved using a recursive backtracking approach. We
 *           use a "pick/don't pick" strategy to generate all possible
 *           combinations that sum up to the target.
 *
 *           1. The input `candidates` array is sorted first. This allows for an
 *              important optimization: if a candidate is greater than the
 *              remaining target, we can prune that entire branch of the
 *              recursion since all subsequent candidates will also be too
 *              large.
 *           2. The recursive function `generateCombinations` explores two
 *              choices for each candidate at index `i`:
 *              a) **Don't Pick:** Skip the current candidate and make a
 *                 recursive call for the next candidate (`i + 1`).
 *              b) **Pick:** Add the current candidate to the combination,
 *                 reduce the target by its value, and make a recursive call for
 *                 the *same* index `i`. This is the key step that allows a
 *                 candidate to be used multiple times.
 *           3. **Base Cases:** The recursion stops if the target becomes 0 (a
 *              valid combination is found), if the target becomes negative, or
 *              if we run out of candidates.
 *
 * Time Complexity: O(2^T * k), where T is the target and k is the average
 *                  length of a combination. The recursion can go as deep as T,
 *                  and we branch, leading to an exponential number of calls.
 * Space Complexity: O(T) - The recursion depth can go up to the target value.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

vvi combinationSum(vi& candidates, int target);
void generateCombinations(vvi& ans, vi& candidates, vi& combination, int target,
                          int i);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, target;
    cin >> n >> target;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input: [ ";
    for (int num : nums) {
      cout << num << " ";
    }
    cout << "]" << endl;

    vector<vector<int>> ans = combinationSum(nums, target);

    cout << "Combinations with Sum " << target << ": [ ";
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

vvi combinationSum(vi& candidates, int target) {
  vvi ans;
  vi combination;
  sort(candidates.begin(), candidates.end());

  generateCombinations(ans, candidates, combination, target, 0);
  return ans;
}

void generateCombinations(vvi& ans, vi& candidates, vi& combination, int target,
                          int i) {
  // Base Case 1: A valid combination is found.
  if (target == 0) {
    ans.emplace_back(combination);
    return;
  }

  // Base Case 2: Pruning/Invalid path.
  // - We've run out of candidates.
  // - The target has become negative.
  // - The current candidate is larger than the remaining target (due to
  // sorting).
  if (i == candidates.size() || target < 0 || candidates[i] > target) {
    return;
  }

  // Choice 1: Don't pick the current candidate. Move to the next one.
  generateCombinations(ans, candidates, combination, target, i + 1);

  // Choice 2: Pick the current candidate.
  // Stay at the same index `i` to allow for its reuse.
  combination.emplace_back(candidates[i]);
  generateCombinations(ans, candidates, combination, target - candidates[i], i);
  combination.pop_back();  // Backtrack
}
