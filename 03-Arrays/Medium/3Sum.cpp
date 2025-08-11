/*
 * Problem: 3Sum (LeetCode #15)
 * Link: https://leetcode.com/problems/3sum/description/
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: This approach uses a hash set to find triplets. It iterates
 *           through the array with a primary pointer `i`. For each `i`, it
 *           iterates through the rest of the array with a pointer `j`. The
 *           problem is now reduced to finding a third element `k` such that
 *           `nums[i] + nums[j] + k = 0`, i.e., `k = 0 - nums[i] - nums[k]`
 *
 *           We use a hash map to store elements seen by the `j` pointer. If
 *           we find the required third element in the hash map, we have a
 *           valid triplet. To handle duplicate triplets, we sort each
 *           found triplet and store it in a `std::set`.
 *
 * Time Complexity: O(N^2 * log(M)), where M is the number of unique triplets.
 * Space Complexity: O(N) for the hash map + O(M) for the set.
 */
vector<vector<int>> hashApproach(vector<int>& nums);

/**
 * Approach: This is the optimal approach which combines sorting with the
 *           two-pointer technique.
 *           1. Sort the input array.
 *           2. Iterate through the array with a pointer `i`. For each `i`,
 *              skip it if it's the same as the previous element to avoid
 *              duplicate triplets.
 *           3. For each `i`, use two pointers, `j` (from `i+1`) and `k` (from
 *              the end), to find a pair that sums to `0 - nums[i]`.
 *           4. Adjust `j` and `k` based on the sum, and skip duplicates.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1) auxiliary space. O(N^2) for the answer.
 */
vector<vector<int>> twoPointerApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<vector<int>> hashApproachResult = hashApproach(nums);
    vector<vector<int>> twoPointerApproachResult = twoPointerApproach(nums);

    cout << "Hash Approach: [ ";
    for (auto i : hashApproachResult) {
      cout << "[ ";
      for (auto j : i) {
        cout << j << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Two-Pointer Approach: [ ";
    for (auto i : twoPointerApproachResult) {
      cout << "[ ";
      for (auto j : i) {
        cout << j << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<vector<int>> hashApproach(vector<int>& nums) {
  set<vector<int>> triplets;

  for (int i = 0; i < nums.size(); i++) {
    unordered_map<int, int> fq;  // Can also use unordered_set.

    for (int j = i + 1; j < nums.size(); j++) {
      // i + j + k = 0
      // k = 0 - i - j
      int thirdElement = 0 - nums[i] - nums[j];

      // If thirdElement is found, then it means it was stored in some
      // previous iteration into the map and forms the sum with distinct
      // indices.
      if (fq.find(thirdElement) != fq.end()) {
        vector<int> temp = {nums[i], nums[j], thirdElement};
        // Sort vector and store in set to prevent duplicates.
        sort(temp.begin(), temp.end());
        triplets.insert(temp);
      } else {
        fq[nums[j]] = j;
      }
    }
  }

  vector<vector<int>> ans(triplets.begin(), triplets.end());
  return ans;
}

vector<vector<int>> twoPointerApproach(vector<int>& nums) {
  vector<vector<int>> ans;
  sort(nums.begin(), nums.end());

  for (int i = 0; i < nums.size(); i++) {
    // Move i pointer to some other element as we tried all
    // possible triplets with current element.
    if (i > 0 && nums[i] == nums[i - 1]) continue;

    int j = i + 1;  // Track smaller elements (moves in ascending order).
    int k =
        nums.size() - 1;  // Track greater elements (moves in descending order).
    while (j < k) {
      int sum = nums[i] + nums[j] + nums[k];

      if (sum == 0) {
        ans.push_back({nums[i], nums[j], nums[k]});

        j++;
        k--;
        // Move j and k pointer to some other element as we have
        // all possible triplets with the current elements.
        while (j < k && nums[j] == nums[j - 1]) j++;
        while (j < k && nums[k] == nums[k + 1]) k--;
      } else if (sum < 0) {
        // We have a sorted array. Since the sum is less than needed, we need
        // a greater number which we get moving moving the j pointer to right.
        j++;
      } else {
        // sum > 0; we need a smaller number, so we move k pointer to left.
        k--;
      }
    }
  }

  return ans;
}
