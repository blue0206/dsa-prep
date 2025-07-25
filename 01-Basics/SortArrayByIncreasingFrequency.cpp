/*
 * Problem: Sort Array by Increasing Frequency (LeetCode #1636)
 * Link:
 * https://leetcode.com/problems/sort-array-by-increasing-frequency/description/
 *
 * Approach: Use unordered_map to hash the frequency of each number and then
 * sort the vector accordingly using a custom lambda comparator.
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> frequencySort(vector<int> &nums) {
  unordered_map<int, int> freq;
  for (auto i : nums) {
    freq[i]++;
  }

  if (freq.size() == 1) return nums;

  sort(nums.begin(), nums.end(), [&](int a, int b) {
    // Sort in increasing order based on the frequency of the values.
    if (freq[a] < freq[b]) return true;
    if (freq[a] > freq[b]) return false;

    // Sort in decreasing order (number) in case of same frequency.
    if (a > b) return true;
    return false;
  });

  return nums;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    vector<int> nums;
    int n;
    cin >> n;
    nums.reserve(n);

    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    frequencySort(nums);
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << endl;
  }

  return 0;
}
