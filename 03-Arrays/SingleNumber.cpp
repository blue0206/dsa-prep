/*
 * Problem: Single Number (LeetCode #136)
 * Link: https://leetcode.com/problems/single-number/description/
 *
 * Approach: Xor all the elements of array. The ones that appear twice will
 *           cancel out and single occurring number will be left.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 *
 *
 * Some other (less optimal) approaches are as follows but not implemented:
 * 1. Check the count of each element of array and return the element appearing
 *    once using a double loop. TC: O(N^2) SC: O(1)
 * 2. Create a map and store the count of each unique number. The number with
 *    count of 1 is the answer. TC: O(N) SC: O(N)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int singleNumber(vector<int>& nums) {
  int num = 0;
  for (auto i : nums) {
    num ^= i;
  }
  return num;
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

    cout << "Single Number: " << singleNumber(nums) << endl;

    cout << endl;
  }

  return 0;
}
