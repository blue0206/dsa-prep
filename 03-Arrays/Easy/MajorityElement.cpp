/*
 * Problem: Majority Element (LeetCode #169)
 * Link: https://leetcode.com/problems/majority-element/description/
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: Initialize an unordered_map, a maxCount variable to track max count
 *           and a maxNum variable to track the number with max count.
 *           Iterate through the array, store array elements as keys of map
 *           with value as their count.
 *           Update maxCount and maxNum variable every time the count in map
 *           for current element exceeds maxCount.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int hashApproach(vector<int>& nums);

/**
 * Approach:  --------------------Moore's Voting Algorithm----------------------
 *            We iterate through the array and choose an element (for starters,
 *            the one at 0th index) and track the count.
 *            We increment the counter everytime element == nums[i] and
 *            decrement the counter otherwise.
 *            The moment the counter becomes 0, we can assert that the current
 *            chosen element is not the majority element.
 *            Therefore, when counter becomes 0, we choose the next arr[i] as
 *            out new element and continue traversing the array, performing the
 *            same operations.
 *            As per this algorithm, if there is a majority element, the counter
 *            after traversing the array will always be >0 and the element
 *            associated with that counter is the majority element.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int mooreVotingApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Majority Element (Hash-Map Approach): " << hashApproach(nums)
         << endl;
    cout << "Majority Element (Moore's Voting Algorithm Approach): "
         << mooreVotingApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

int hashApproach(vector<int>& nums) {
  unordered_map<int, int> mp;

  int maxCount = 1;
  int maxNum = nums[0];
  for (auto i : nums) {
    mp[i]++;
    if (mp[i] > maxCount) {
      maxCount = mp[i];
      maxNum = i;
    }
  }

  return maxNum;
}

int mooreVotingApproach(vector<int>& nums) {
  int element = nums[0];
  int count = 0;

  for (auto i : nums) {
    if (count == 0) {
      element = i;
    }
    if (element == i) {
      count++;
    } else {
      count--;
    }
  }

  return element;
}
