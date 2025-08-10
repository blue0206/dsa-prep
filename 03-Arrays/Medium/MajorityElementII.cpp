/*
 * Problem: Majority Element II (LeetCode #229)
 * Link: https://leetcode.com/problems/majority-element-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: This is a single-pass approach using a hash map. We iterate
 *           through the array, counting the frequency of each element on the
 *           fly.
 *
 *           An element is added to the result list at the exact moment its
 *           frequency becomes `floor(n/3) + 1`, which is the minimum count
 *           required to be a majority element.
 *           The check for strict equality (`==`) is a clever optimization that
 *           ensures an element is added only once, right when it crosses the
 *           threshold, thus preventing duplicates in the final answer.
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
vector<int> hashApproach(vector<int>& nums);

/**
 * Approach:  ---------Moore's Voting Algorithm (Modified for k > n/3)----------
 *            The key insight is that there can be at most two elements that
 *            appear more than n/3 times.
 *            1. First Pass: We find two potential candidates. We maintain two
 *               counters and two candidate variables. We iterate through the
 *               array, updating the counts. If a number matches a candidate,
 *               its count is incremented. If not, and a counter is zero, it
 *               becomes the new candidate. If both candidates are different
 *               and their counts are non-zero, both counts are decremented.
 *            2. Second Pass: The first pass gives us two candidates, but they
 *               are not guaranteed to be majority elements. We must verify
 *               by counting their actual occurrences in a second pass.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
vector<int> modifiedMooreVotingApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<int> hashApproachAns = hashApproach(nums);
    vector<int> modifiedMooreVotingApproachAns =
        modifiedMooreVotingApproach(nums);

    cout << "Majority Elements (Hash-Map Approach): [ ";
    for (auto i : hashApproachAns) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Majority Element (Moore's Voting Algorithm Approach): [ ";
    for (auto i : modifiedMooreVotingApproachAns) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> hashApproach(vector<int>& nums) {
  unordered_map<int, int> fq;
  vector<int> ans;

  for (auto i : nums) {
    fq[i]++;

    // We check for equality with n/3 + 1 instead of > n/3 because
    // an element might occur more than n/3 + 1 times and hence we may end up
    // with duplicates in our answer.
    if (fq[i] == (nums.size() / 3) + 1) {
      ans.push_back(i);
    }
  }
  return ans;
}

vector<int> modifiedMooreVotingApproach(vector<int>& nums) {
  int count1 = 0;
  int element1 = nums[0];
  int count2 = 0;
  // Initialize different from element1 to deal with an edge case
  // where nums[0] or any initial value is the same for element1 and element2,
  // hence, preventing both from getting updated on 0 count.
  int element2 = nums[0] - 1;

  for (int i = 0; i < nums.size(); i++) {
    if (count1 == 0 && nums[i] != element2) {
      element1 = nums[i];
    } else if (count2 == 0 && nums[i] != element1) {
      element2 = nums[i];
    }

    if (nums[i] == element1) {
      count1++;
    } else if (nums[i] == element2) {
      count2++;
    } else {
      count1--;
      count2--;
    }
  }

  // Reset counters to verify if the two candidates appear
  // more than n/3 times.
  count1 = 0;
  count2 = 0;
  for (auto i : nums) {
    if (i == element1) count1++;
    if (i == element2) count2++;
  }

  vector<int> ans;
  if (count1 > (nums.size() / 3)) {
    ans.push_back(element1);
  }
  if (count2 > (nums.size() / 3)) {
    ans.push_back(element2);
  }

  return ans;
}
