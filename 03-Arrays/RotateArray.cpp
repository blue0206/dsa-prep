/*
 * Problem: Rotate Array (LeetCode #189)
 * Link: https://leetcode.com/problems/rotate-array/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void printArr(vector<int>& nums) {
  cout << "[ ";
  for (auto i : nums) {
    cout << i << " ";
  }
  cout << "]" << endl;
}

/**
 * Approach: Create a temporary array and store the rotated-out elements inside
 *           it. Then, loop through the main array and fill in the elements to
 *           be rotated-in (from the back). Lastly, fill the space vacated by
 *           rotated-in elements with the rotated-out elements extracted inside
 *           the temp array.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
void rotateApproachOne(vector<int>& nums, int k);

/**
 * Approach: Consider an array [1, 2, 3, 4, 5] and k=3.
 *           We first reverse the entire array: [5, 4, 3, 2, 1]
 *           Then, we reverse the elements that are rotated-in from back in
 *           initial array: [3, 4, 5, 2, 1].
 *           Finally, we reverse the rest of the elements (rotated-out
 *           elements). Final array: [3, 4, 5, 1, 2].
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
void rotateApproachTwo(vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    rotateApproachOne(nums, k);
    cout << "Rotated Array (Approach 1): ";
    printArr(nums);

    sort(nums.begin(), nums.end());
    rotateApproachTwo(nums, k);
    cout << "Rotated Array (Approach 2): ";
    printArr(nums);

    cout << endl;
  }

  return 0;
}

void rotateApproachOne(vector<int>& nums, int k) {
  if (nums.size() <= 1 || nums.size() == k ||
      nums.size() == (k % nums.size()) || k == 0) {
    return;
  }

  int resolvedK = k % nums.size();

  vector<int> temp;
  for (int i = 0; i < nums.size() - resolvedK; i++) {
    temp.push_back(nums[i]);
  }

  int replacementIndex = 0;
  int index = nums.size() - resolvedK;
  while (replacementIndex < resolvedK) {
    nums[replacementIndex++] = nums[index++];
  }

  for (int i = 0; i < temp.size(); i++) {
    nums[replacementIndex++] = temp[i];
  }
}

void rotateApproachTwo(vector<int>& nums, int k) {
  if (nums.size() <= 1 || nums.size() == k ||
      nums.size() == (k % nums.size()) || k == 0) {
    return;
  }

  int resolvedK = k % nums.size();
  reverse(nums.begin(), nums.end());
  reverse(nums.begin(), nums.begin() + resolvedK);
  reverse(nums.begin() + resolvedK, nums.end());
}
