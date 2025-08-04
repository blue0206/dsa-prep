/*
 * Problem: Rearrange Array Elements by Sign (LeetCode #2149)
 * Link:
 * https://leetcode.com/problems/rearrange-array-elements-by-sign/description/
 *
 * Approach:Initialize an array of the same size as nums.
 *          Initialize two pointers, one for tracking positive indices which are
 *          even (as the array should start with positive number and 0th index
 *          is even), and one for tracking negative indices which are odd.
 *
 *          In this approach, we simply iterate through the nums array and if
 *          the current element is positive, we place it at positive index of
 *          answer array and vice-versa for negative elements.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

/**
 * Follow-up: What if the number of positive and negative integers are not
 * equal?
 *
 * Approach: Separate the positive and negative numbers into two separate
 *           arrays. Then, construct the result array by alternately taking
 *           elements from the positive and negative arrays. Once one of the
 *           arrays is exhausted, append the remaining elements from the other
 *           array to the end.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> rearrangeArray(vector<int>& nums) {
  if (nums.size() < 2) return {};

  vector<int> ans(nums.size());
  int posIndex = 0;  // Positive index is always at even indices.
  int negIndex = 1;  // Negative index is always at odd indices.

  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] < 0) {
      ans[negIndex] = nums[i];
      negIndex += 2;
    } else {
      ans[posIndex] = nums[i];
      posIndex += 2;
    }
  }

  return ans;
}

vector<int> rearrangeArrayFollowUp(vector<int>& nums) {
  vector<int> positives;
  vector<int> negatives;
  for (int num : nums) {
    if (num >= 0) {
      positives.push_back(num);
    } else {
      negatives.push_back(num);
    }
  }

  vector<int> ans;
  int i = 0, j = 0;
  while (i < positives.size() && j < negatives.size()) {
    ans.push_back(positives[i++]);
    ans.push_back(negatives[j++]);
  }

  while (i < positives.size()) {
    ans.push_back(positives[i++]);
  }

  while (j < negatives.size()) {
    ans.push_back(negatives[j++]);
  }

  return ans;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> rearrangedArray = rearrangeArray(nums);

    cout << "Rearranged Array: [ ";
    for (auto i : rearrangedArray) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> rearrangedArrayFollowUp = rearrangeArrayFollowUp(nums);

    cout << "Rearranged Array: [ ";
    for (auto i : rearrangedArrayFollowUp) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}
