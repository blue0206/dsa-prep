/*
 * Problem: Move Zeroes (LeetCode #283)
 * Link: https://leetcode.com/problems/move-zeroes/description/
 */

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
 * Approach: Use a "snowball" or "slow pointer" method. One pointer
 *           (index) keeps track of the position to place the next non-zero
 *           element. Iterate through the array, and when a non-zero element is
 *           found, place it at index and increment index.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
void moveZeroesApproachOne(vector<int>& nums);

/**
 * Approach: Create a temporary array and fill it with all non-0 elements.
 *           Then, iterate through the main array and place all the non-0
 *           elements first, followed by 0s for the rest.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
void moveZeroesApproachTwo(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    vector<int> numsTwo = nums;

    cout << "Initial Array: ";
    printArr(nums);

    moveZeroesApproachOne(nums);
    cout << "Final Array (Approach 1): ";
    printArr(nums);

    moveZeroesApproachTwo(numsTwo);
    cout << "Final Array (Approach 2): ";
    printArr(numsTwo);

    cout << endl;
  }

  return 0;
}

void moveZeroesApproachOne(vector<int>& nums) {
  int index = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != 0) {
      nums[index++] = nums[i];
    }
  }
  for (int i = index; i < nums.size(); i++) {
    nums[i] = 0;
  }
}

void moveZeroesApproachTwo(vector<int>& nums) {
  vector<int> temp;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != 0) {
      temp.push_back(nums[i]);
    }
  }
  for (int i = 0; i < nums.size(); i++) {
    if (i < temp.size()) {
      nums[i] = temp[i];
    } else {
      nums[i] = 0;
    }
  }
}
