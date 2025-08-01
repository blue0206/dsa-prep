/*
 * Problem: Missing Number (LeetCode #268)
 * Link: https://leetcode.com/problems/missing-number/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: Calculate ideal sum using the formula for the sum of 'n' natural
 *           numbers, (n * (n+1))/2
 *           Then calculate the actual sum of all the numbers in array.
 *           Subtract the actual sum from ideal sum and the resultant is the
 *           missing number.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int sumApproach(vector<int>& nums1);

/**
 * Approach: XOR the elements of 'nums' array and store it in a variable named
 *           'actualXor'.
 *           XOR the first 'n' natural numbers and store in a variable named
 *           'idealXor'.
 *           Finally, XOR actualXor and idealXor to get the missing number.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int xorApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Sum Approach: " << sumApproach(nums) << endl;
    cout << "XOR Approach: " << xorApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

int sumApproach(vector<int>& nums) {
  // Calculate sum of all numbers.
  int sum = 0;
  for (auto i : nums) {
    sum += i;
  }

  // Calculate the sum of first n natural numbers
  // and subtract with sum of numbers in array.
  // The resultant is the missing value.
  int nSum = (nums.size() * (nums.size() + 1)) / 2;

  return nSum - sum;
}

int xorApproach(vector<int>& nums) {
  // This will store the xor of actual
  // elements present in nums.
  int actualXor = 0;

  // This will store the ideal xor that SHOULD BE
  // for the first 'n' natural numbers.
  int idealXor = 0;
  int num = 0;  // For xor-ing with idealXor.

  for (int i = 0; i < nums.size(); i++) {
    actualXor ^= nums[i];
    idealXor ^= num++;
  }
  idealXor ^= num;

  // Finally, xor-ing the actual and ideal xor gives us the
  // missing number.
  return (actualXor ^ idealXor);
}
