/*
 * Problem: Intersection of Two Arrays II (LeetCode #350)
 * Link:
 * https://leetcode.com/problems/intersection-of-two-arrays-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: Sort the given arrays and initialize two pointers
 *           ('ptrOne' for 'nums1' and 'ptrTwo' for 'nums2'). Use the double
 *           pointer approach to push intersecting elements into vector.
 *
 * Time Complexity: O(N logN)
 * Space Complexity: O(N) only to return answer. O(1) used to solve.
 */
vector<int> intersectionApproachOne(vector<int>& nums1, vector<int>& nums2);

/**
 * Approach: Store the elements of one array in an unordered_map with their
 *           counts for O(1) lookups. Initialize a vector to store answer.
 *           Iterate through the other array and store the intersecting elements
 *           in vector and decrement their counts in the hash.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(min(N, M))
 */
vector<int> intersectionApproachTwo(vector<int>& nums1, vector<int>& nums2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> nums1(n);
    vector<int> nums2(m);
    for (int i = 0; i < n; i++) cin >> nums1[i];
    for (int i = 0; i < m; i++) cin >> nums2[i];

    vector<int> ans = intersectionApproachOne(nums1, nums2);

    cout << "Intersection (Approach 1): [ ";
    for (auto i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    ans.clear();
    ans = intersectionApproachTwo(nums1, nums2);

    cout << "Intersection (Approach 2): [ ";
    for (auto i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> intersectionApproachOne(vector<int>& nums1, vector<int>& nums2) {
  sort(nums1.begin(), nums1.end());
  sort(nums2.begin(), nums2.end());

  int ptrOne = 0;
  int ptrTwo = 0;
  vector<int> ans;

  while (ptrOne < nums1.size() && ptrTwo < nums2.size()) {
    if (nums1[ptrOne] == nums2[ptrTwo]) {
      ans.push_back(nums1[ptrOne]);
      ptrOne++;
      ptrTwo++;
    } else if (nums1[ptrOne] > nums2[ptrTwo]) {
      ptrTwo++;
    } else {
      ptrOne++;
    }
  }

  return ans;
}

vector<int> intersectionApproachTwo(vector<int>& nums1, vector<int>& nums2) {
  // Optimize by creating the set from the smaller array to save space.
  if (nums1.size() > nums2.size()) {
    return intersectionApproachTwo(nums2, nums1);
  }

  // Hash the elements of nums1, storing their counts.
  unordered_map<int, int> hashedNums;
  for (auto i : nums1) {
    hashedNums[i]++;
  }

  vector<int> ans;
  for (auto i : nums2) {
    if (hashedNums.find(i) != hashedNums.end() && hashedNums[i] >= 1) {
      ans.push_back(i);
      hashedNums[i]--;
    }
  }

  return ans;
}
