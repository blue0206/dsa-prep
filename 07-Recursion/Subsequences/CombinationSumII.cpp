/*
 * Problem: Combination Sum II (LeetCode #40)
 * Link: https://leetcode.com/problems/combination-sum-ii/description/
 *
 * Approach: This problem is solved using a recursive backtracking approach.
 *           Since we need to find unique combinations and the input array can
 *           have duplicates, sorting the array is the first crucial step.
 *
 *           The recursive function explores combinations starting from an
 *           index. Instead of a "pick/don't pick" choice, we use a `for` loop
 *           to iterate through candidates.
 *
 *           1. **Base Case:** If `target` becomes 0, we've found a valid
 *              combination.
 *           2. **Recursive Step:** We loop from the current `start` index to
 *              the end of the array.
 *           3. **Handling Duplicates:** To avoid duplicate combinations (e.g.,
 *              using the first '1' vs. the second '1' to start a path), we add
 *              a condition: `if (i > start && candidates[i] == candidates[i-1])
 *              continue;`. This ensures that for any given level of recursion,
 *              we only pick a number once.
 *
 * Time Complexity: O(2^N * k), where k is the average length of a combination.
 * Space Complexity: O(N) for the recursion depth.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

vvi combinationSum2(vi& candidates, int target);
void generateCombinations(vvi& ans, vi& candidates, vi& combination, int target,
                          int start);

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

    vector<vector<int>> ans = combinationSum2(nums, target);

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

vvi combinationSum2(vi& candidates, int target) {
  vvi ans;
  vi combination;
  sort(candidates.begin(), candidates.end());

  generateCombinations(ans, candidates, combination, target, 0);
  return ans;
}

void generateCombinations(vvi& ans, vi& candidates, vi& combination, int target,
                          int start) {
  if (target == 0) {
    ans.emplace_back(combination);
    return;
  }

  for (int i = start; i < candidates.size(); i++) {
    // Pruning: If current candidate is larger than target, subsequent ones will
    // also be (since the array is sorted).
    if (candidates[i] > target) break;

    // Skip duplicates: If we are not at the start of the loop for this level,
    // and the current element is the same as the previous, skip it to avoid
    // duplicate combinations.
    if (i > start && candidates[i] == candidates[i - 1]) {
      continue;
    }

    // Pick the candidate.
    combination.emplace_back(candidates[i]);
    // Recurse with the next index, as each element can be used only once.
    generateCombinations(ans, candidates, combination, target - candidates[i],
                         i + 1);
    combination.pop_back();  // Backtrack.
  }
}
