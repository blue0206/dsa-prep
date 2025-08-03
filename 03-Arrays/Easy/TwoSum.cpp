/*
 * Problem: Two Sum (LeetCode #1)
 * Link: https://leetcode.com/problems/two-sum/description/
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: We know that solution is element-1 + element-2 = target.
 *           Hence we can say that element-1 = target - element-2 and vice-versa
 *           for element-2 as well.
 *           In this approach, we create an unordered_map and iterate through
 *           the array. In each pass, we check if there is a key equal to
 *           (target - nums[i]) in the map. If not, we create an entry
 *           with the current element (nums[i]) as key and index (i) as value.
 *           As we iterate, we keep checking and if false, create keys in the
 *           map and when the key is matched, we have found our two elements.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
vector<int> hashApproach(vector<int>& nums, int target);

/**
 * NOTE: This is NOT a solution to this LeetCode problem. Rather, this optimized
 *       approach is for use-cases where the returning index is not required.
 *
 * Approach:  We sort the array and initialize two pointers, left and right at
 *            start and end of the array. Next, we loop through the array and
 *            check if sum (nums[left], nums[right]) is equal, greater, or
 *            lesser than the target.
 *            If sum > target, then we reduce the sum by going to a smaller
 *            element by decrementing right pointer.
 *            If sum < target, then we increase the sum by going to a greater
 *            element by incrementing the left pointer.
 *            If sum == target, we have found our two elements.
 *            In this case, we CAN'T return index as the array has been sorted.
 *
 * Time Complexity: O(N log N)
 * Space Complexity: O(1)
 */
vector<int> twoPointerApproach(vector<int>& nums, int target);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, target;
    cin >> n >> target;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<int> hashApproachResult = hashApproach(nums, target);
    vector<int> twoPointerApproachResult = twoPointerApproach(nums, target);

    cout << "Hash Approach (Indices): [ " << hashApproachResult[0] << ", "
         << hashApproachResult[1] << " ]" << endl;
    cout << "Two-Pointer Approach (Numbers): [ " << twoPointerApproachResult[0]
         << ", " << twoPointerApproachResult[1] << " ]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> hashApproach(vector<int>& nums, int target) {
  unordered_map<int, int> mp;

  for (int i = 0; i < nums.size(); i++) {
    if (mp.find(target - nums[i]) != mp.end()) {
      // Return the indices.
      return {mp[target - nums[i]], i};
    } else {
      mp[nums[i]] = i;
    }
  }
  return {};
}

vector<int> twoPointerApproach(vector<int>& nums, int target) {
  sort(nums.begin(), nums.end());
  int left = 0;
  int right = nums.size() - 1;

  while (left < right) {
    long long sum = nums[left] + nums[right];
    if (sum == target) {
      // We can return either a boolean or the values in this approach.
      // Indices cannot be returned as array has been sorted.
      return {nums[left], nums[right]};
    } else if (sum > target) {
      right--;
    } else {
      left++;
    }
  }
  return {};
}
