/*
 * Problem: Longest Consecutive Sequence (LeetCode #128)
 * Link: https://leetcode.com/problems/longest-consecutive-sequence/description/
 */

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Approach:Sort the array. Initialize variables for storing current length
 *          and max length.
 *          Iterate through the array, if the current element is equal to
 *          next element + 1, increment the length.
 *          If current element is equal to next, skip iteration.
 *          If current element is not equal to next element + 1, then update
 *          max length and reset current length counter.
 *          At the end of iteration, return the max of current and max length
 *          vars (as maxLength is only updated in else condition).
 *
 * Time Complexity: O(N logN)
 * Space Complexity: O(1)
 */
int sortApproach(vector<int> nums);

/**
 * Approach:Initialize an unordered_set and store all elements of array inside.
 *          In order to find consecutive elements, we must first have a criteria
 *          to identify the first of those consecutive elements.
 *          The criteria for that is: there is no element 1 lesser than the
 *          element present.
 *
 *          Therefore, we iterate through the set and for each element, check if
 *          it is the first element of probably consecutive sequence of elements
 *          and if it is, simply check if its next consecutive elements exist
 *          in the set with a find() through a loop while incrementing the
 *          length counter for each successful find. Finally, update the max
 *          length variable after the iteration for finding the next sequences
 *          is over. Each number is visited at most twice.
 *
 * Time Complexity: O(N) on average. The outer loop runs N times, and the inner
 *                  while loop runs only for the start of a sequence.
 * Space Complexity: O(N)
 */
int setApproach(const vector<int>& nums);

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

    cout << "Sort Approach: " << sortApproach(nums) << endl;
    cout << "Unordered-Set Approach: " << setApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

int sortApproach(vector<int> nums) {  // Pass by value to sort a local copy
  if (nums.size() == 0) return 0;

  sort(nums.begin(), nums.end());
  int maxLength = 1;
  int length = 1;

  for (int i = 0; i < nums.size() - 1; i++) {
    if (nums[i] == nums[i + 1]) continue;
    if (nums[i] + 1 == nums[i + 1]) {
      length++;
    } else {
      maxLength = max(length, maxLength);
      length = 1;
    }
  }
  return max(maxLength, length);
}

int setApproach(const vector<int>& nums) {
  if (nums.size() == 0) return 0;

  unordered_set<int> st;
  for (auto i : nums) {
    st.insert(i);
  }

  int maxLength = 0;
  for (auto i : st) {
    if (st.find(i - 1) == st.end()) {
      int length = 1;
      int j = i;
      while (st.find(j + 1) != st.end()) {
        length++;
        j++;
      }
      maxLength = max(length, maxLength);
    }
  }

  return maxLength;
}
