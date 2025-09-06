/*
 * Problem: Subsets II (LeetCode #90)
 * Link: https://leetcode.com/problems/subsets-ii/description/
 *
 * Approach: This problem is a variation of "Subsets" where the input array can
 *           contain duplicates. The goal is to find all unique subsets. The key
 *           is to sort the input array first, which groups duplicates together
 *           and makes them easier to handle. Two common recursive backtracking
 *           approaches are shown.
 *
 *           Method 1: Pick/Don't Pick
 *           - For each element, we decide to either include it or not.
 *           - To avoid duplicates, when we decide *not* to pick an element, we
 *             also skip all its subsequent identical elements. This ensures
 *             that we only consider the "don't pick" path once for a group of
 *             duplicates.
 *
 *           Method 2: For-Loop Based Recursion (More Common)
 *           - This is similar to the approach for Combination Sum problems.
 *           - We add the current subset to the answer at each step.
 *           - We then loop from a `startIndex` to the end. Inside the loop, we
 *             add an element and recurse.
 *           - To avoid duplicates, we add a check:
 *             `if (i > startIndex && nums[i] == nums[i-1]) continue;`. This
 *             ensures that for a given level of recursion, we only start a new
 *             path with the first occurrence of a number in a sequence of
 *             duplicates.
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(N) - for the recursion call stack depth.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> subsetsWithDup(vector<int>& nums);
void generateSubsetsMethod1(vector<vector<int>>& ans, vector<int>& nums,
                            vector<int>& pSet, int i);
void generateSubsetsMethod2(vector<vector<int>>& ans, vector<int>& nums,
                            vector<int>& pSet, int startIndex);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "nums: [ ";
    for (int num : nums) {
      cout << num << " ";
    }
    cout << "]" << endl;

    vector<vector<int>> ans = subsetsWithDup(nums);

    cout << "Subsets: [ ";
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

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
  vector<vector<int>> ans;
  vector<int> pSet;
  sort(nums.begin(), nums.end());

  // Uncomment the method to use.
  generateSubsetsMethod2(ans, nums, pSet, 0);
  //   generateSubsetsMethod1(ans, nums, pSet, 0);
  return ans;
}

void generateSubsetsMethod1(vector<vector<int>>& ans, vector<int>& nums,
                            vector<int>& pSet, int i) {
  if (i == nums.size()) {
    ans.emplace_back(pSet);
    return;
  }

  // Pick.
  pSet.emplace_back(nums[i]);
  generateSubsetsMethod1(ans, nums, pSet, i + 1);
  pSet.pop_back();

  // Don't Pick: Skip all duplicates to avoid considering them again.
  while (i + 1 < nums.size() && nums[i] == nums[i + 1]) i++;
  generateSubsetsMethod1(ans, nums, pSet, i + 1);
}

void generateSubsetsMethod2(vector<vector<int>>& ans, vector<int>& nums,
                            vector<int>& pSet, int startIndex) {
  ans.emplace_back(pSet);

  for (int j = startIndex; j < nums.size(); j++) {
    // Skip duplicates: Only pick the first occurrence in a sequence of
    // duplicates at any given level of recursion.
    if (j > startIndex && nums[j] == nums[j - 1]) {
      continue;
    }

    pSet.emplace_back(nums[j]);
    generateSubsetsMethod2(ans, nums, pSet, j + 1);
    pSet.pop_back();
  }
}
