/*
 * Problem: Subsets (LeetCode #78)
 * Link: https://leetcode.com/problems/subsets/description/
 *
 * Approach: This problem is solved using a recursive backtracking approach
 * known as the "pick/don't pick" or "include/exclude" method. We generate all
 * possible subsets by making a decision for each element in the input array.
 *
 *           1. The recursive function `generateSubsets` explores possibilities
 *              starting from an index `i`.
 *           2. **Base Case:** When the index `i` reaches the end of the array,
 *              it means we have considered all elements. The current partial
 *              subset (`pSet`) is a complete subset, so we add it to our
 *              answer.
 *           3. **Recursive Step (Decision for element at index `i`):**
 *              a) **Include:** Add `nums[i]` to `pSet` and make a recursive
 *                 call for the next element, `i + 1`.
 *              b) **Exclude:** Backtrack by removing `nums[i]` from `pSet`,
 *                 then make another recursive call for `i + 1`.
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(N) - for the recursion call stack depth.
 */

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> subsets(vector<int>& nums);
void generateSubsets(vector<vector<int>>& ans, vector<int>& nums,
                     vector<int>& pSet, int i);

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

    vector<vector<int>> ans = subsets(nums);

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

vector<vector<int>> subsets(vector<int>& nums) {
  vector<vector<int>> ans;
  vector<int> pSet;

  generateSubsets(ans, nums, pSet, 0);
  return ans;
}

void generateSubsets(vector<vector<int>>& ans, vector<int>& nums,
                     vector<int>& pSet, int i) {
  if (i == nums.size()) {
    ans.emplace_back(pSet);
    return;
  }

  // Include the number at current index and generate all subsets.
  pSet.emplace_back(nums[i]);
  generateSubsets(ans, nums, pSet, i + 1);

  // Exclude and generate all subsets.
  pSet.pop_back();
  generateSubsets(ans, nums, pSet, i + 1);
}
