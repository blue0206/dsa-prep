/*
 * Problem: Intersection of Two Arrays (LeetCode #349)
 * Link: https://leetcode.com/problems/intersection-of-two-arrays/description/
 */

#include <algorithm>
#include <iostream>
#include <unordered_set>
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
 * Approach: Store the elements of one array in an unordered_set for O(1)
 *           lookups. Initialize another unordered_set for storing the
 *           intersecting elements by iterating through the other array.
 *           Finally, transfer the intersecting elements to a vector and return.
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
      // Only push to vector if element doesn't exist already in it.
      if (ans.size() == 0 || ans.back() != nums1[ptrOne]) {
        ans.push_back(nums1[ptrOne]);
      }
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

  unordered_set<int> hashedNums(nums1.begin(), nums1.end());
  vector<int> ans;

  // Remove intersecting elements from set and add to answer array.
  for (auto i : nums2) {
    if (hashedNums.erase(i)) {
      ans.push_back(i);
    }
  }

  return ans;
}
