/*
 * Problem: 4Sum (LeetCode #18)
 * Link: https://leetcode.com/problems/4sum/description/
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;

/**
 * Approach: This approach uses three nested loops and a hash set.
 *           1. Iterate with three nested loops using pointers `a`, `b`, and
 *              `c`.
 *           2. For each combination, calculate the required fourth element:
 *              `d = target - (a + b + c)`.
 *           3. Use a hash map (acting as a hash set) to check if this fourth
 *              element has been seen in the innermost loop.
 *           4. To handle duplicate quadruplets, sort each found quadruplet and
 *              store it in a `std::set`.
 *
 * Time Complexity: O(N^3 * log(M)), where M is the no. of unique quadruplets.
 * Space Complexity: O(N) for the hash map + O(M) for the set of M quadruplets.
 */
vector<vector<int>> hashApproach(vector<int>& nums, int target);

/**
 * Approach: This is the optimal approach which extends the 3Sum two-pointer
 *           technique.
 *           1. Sort the input array.
 *           2. Use two outer loops to fix the first two elements, `a` and `b`.
 *              Skip duplicates for both `a` and `b` to avoid redundant work.
 *           3. For each pair `(a, b)`, use a two-pointer approach with `c`
 *              (from `b+1`) and `d` (from the end) to find a pair that sums to
 *              `target - (a + b)`.
 *           4. Adjust `c` and `d` based on the sum, and skip duplicates.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(1) auxiliary space. O(N^2) for the answer.
 */
vector<vector<int>> twoPointerApproach(vector<int>& nums, int target);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, target;
    cin >> n >> target;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<vector<int>> hashApproachResult = hashApproach(nums, target);
    vector<vector<int>> twoPointerApproachResult =
        twoPointerApproach(nums, target);

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

vector<vector<int>> hashApproach(vector<int>& nums, int target) {
  if (nums.size() < 4) return {};

  set<vector<int>> quadruplets;

  for (int a = 0; a < nums.size(); a++) {
    for (int b = a + 1; b < nums.size(); b++) {
      unordered_map<long long, int> fq;

      for (int c = b + 1; c < nums.size(); c++) {
        // a + b + c + d = target
        // d = target - a - b - c
        long long fourthElement =
            target - (ll)nums[a] - (ll)nums[b] - (ll)nums[c];

        // If fourthElement is found, then it means it was stored in some
        // previous iteration into the map and forms the sum with distinct
        // indices.
        if (fq.find(fourthElement) != fq.end()) {
          vector<int> temp = {nums[a], nums[b], nums[c], (int)fourthElement};
          // Sort vector and store in set to prevent duplicates.
          sort(temp.begin(), temp.end());
          quadruplets.insert(temp);
        } else {
          fq[nums[c]] = c;
        }
      }
    }
  }

  vector<vector<int>> ans(quadruplets.begin(), quadruplets.end());
  return ans;
}

vector<vector<int>> twoPointerApproach(vector<int>& nums, int target) {
  if (nums.size() < 4) return {};

  vector<vector<int>> ans;
  sort(nums.begin(), nums.end());

  for (int a = 0; a < nums.size(); a++) {
    // Move 'a' pointer to some other element as we tried all
    // possible quadruplets with current element.
    if (a > 0 && nums[a] == nums[a - 1]) continue;

    for (int b = a + 1; b < nums.size(); b++) {
      // Move 'b' pointer to some other element as we tried all
      // possible quadruplets with current element.
      if (b > a + 1 && nums[b] == nums[b - 1]) continue;

      int c = b + 1;  // Track smaller elements (moves in ascending order).
      // Track greater elements (moves in descending order).
      int d = nums.size() - 1;

      while (c < d) {
        ll sum = (ll)nums[a] + (ll)nums[b] + (ll)nums[c] + (ll)nums[d];

        if (sum == target) {
          ans.push_back({nums[a], nums[b], nums[c], nums[d]});

          c++;
          d--;
          // Move 'c' and 'd' pointers to some other element as we have
          // all possible quadruplets with the current elements.
          while (c < d && nums[c] == nums[c - 1]) c++;
          while (c < d && nums[d] == nums[d + 1]) d--;
        } else if (sum < target) {
          // We have a sorted array. Since the sum is less than needed, we need
          // a greater number which we get moving moving the 'c' pointer to
          // right.
          c++;
        } else {
          // sum > target; we need a smaller number, so we move 'd' pointer to
          // left.
          d--;
        }
      }
    }
  }

  return ans;
}
