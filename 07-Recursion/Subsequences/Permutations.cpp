/*
 * Problem: Permutations (LeetCode #46)
 * Link: https://leetcode.com/problems/permutations/description/
 *
 * Approach: This problem is solved using a recursive backtracking approach that
 *           generates permutations by swapping elements in place.
 *
 *           1. The recursive function `generatePermutations` takes the array
 *              `nums` and a starting index `i`. The goal is to generate all
 *              permutations for the subarray from `i` to the end.
 *           2. **Base Case:** When the index `i` reaches the end of the array,
 *              it means we have fixed the positions for all elements, forming
 *              one complete permutation. We add the current state of `nums` to
 *              our answer list.
 *           3. **Recursive Step:** We iterate from the current index `i` to the
 *              end of the array (with index `j`). In each iteration:
 *              a) We swap the elements at indices `i` and `j`. This places the
 *                 `j`-th element at the `i`-th position.
 *              b) We make a recursive call for the next index, `i + 1`.
 *              c) After the call returns, we swap `nums[i]` and `nums[j]` back.
 *                 This is the "backtracking" step, which restores the array
 *                 for the next iteration of the loop.
 *
 * Time Complexity: O(N * N!)
 * Space Complexity: O(N) - for the recursion call stack depth.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> permute(vector<int>& nums);
void generatePermutations(vector<vector<int>>& ans, vector<int>& nums, int i);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input: [ ";
    for (int num : nums) {
      cout << num << " ";
    }
    cout << "]" << endl;

    vector<vector<int>> ans = permute(nums);

    cout << "Permutations: [ ";
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

vector<vector<int>> permute(vector<int>& nums) {
  vector<vector<int>> ans;

  generatePermutations(ans, nums, 0);
  return ans;
}

void generatePermutations(vector<vector<int>>& ans, vector<int>& nums, int i) {
  if (i == nums.size()) {
    ans.push_back(nums);
    return;
  }

  for (int j = i; j < nums.size(); j++) {
    swap(nums[i], nums[j]);

    generatePermutations(ans, nums, i + 1);

    swap(nums[i], nums[j]);
  }
}
