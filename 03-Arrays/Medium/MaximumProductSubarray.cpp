/*
 * Problem: Maximum Product Subarray (LeetCode #152)
 * Link: https://leetcode.com/problems/maximum-product-subarray/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: Iterate through all possible subarrays using two nested loops. The
 *           outer loop fixes the starting index `i`, and the inner loop
 *           iterates from `i` to the end, defining the ending index `j`. For
 *           each subarray, calculate its product and update the maximum
 *           product found so far.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
int bruteForceApproach(const vector<int>& nums);

/**
 * Approach: This approach cleverly uses two variables, `prefixProduct` and
 *           `suffixProduct`, to find the maximum product in a single pass.
 *           The `prefixProduct` tracks the product of elements from the start
 *           of the array, while `suffixProduct` tracks the product from the
 *           end. The maximum product is updated at each step by comparing it
 *           with both the current prefix and suffix products.
 *
 *           If a zero is encountered, it acts as a delimiter for subarrays.
 *           The product calculation is reset to 1 to start a new subarray
 *           product calculation, effectively ignoring the zero and the
 *           elements before it for future products.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(const vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Brute-Force Approach: " << bruteForceApproach(nums) << endl;
    cout << "Optimal Approach: " << optimalApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

int bruteForceApproach(const vector<int>& nums) {
  int maxProduct = INT_MIN;

  for (int i = 0; i < nums.size(); i++) {
    int product = 1;
    for (int j = i; j < nums.size(); j++) {
      product *= nums[j];
      maxProduct = max(maxProduct, product);
    }
  }
  return maxProduct;
}

int optimalApproach(const vector<int>& nums) {
  int maxProduct = INT_MIN;
  int prefixProduct = 1;
  int suffixProduct = 1;
  int n = nums.size();

  for (int i = 0; i < n; i++) {
    if (prefixProduct == 0) {
      prefixProduct = 1;
    }
    if (suffixProduct == 0) {
      suffixProduct = 1;
    }
    prefixProduct *= nums[i];
    suffixProduct *= nums[n - i - 1];
    maxProduct = max({maxProduct, prefixProduct, suffixProduct});
  }

  return maxProduct;
}
