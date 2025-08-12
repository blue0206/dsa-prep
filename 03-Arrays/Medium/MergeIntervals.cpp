/*
 * Problem: Merge Intervals (LeetCode #56)
 * Link: https://leetcode.com/problems/merge-intervals/description/
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: First, sort the intervals based on their starting points. Then,
 *           iterate through the sorted intervals. For each interval, iterate
 *           through the subsequent intervals to find all that can be merged.
 *           Keep track of the merged interval's start and end. Once all
 *           possible merges for the current interval are found, add the new
 *           merged interval to the answer list. A check is included to skip
 *           intervals that have already been absorbed by a previous merge.
 *
 * Time Complexity: O(N^2) due to the nested loops. O(N log N) for sorting.
 * Space Complexity: O(N) for storing the answer.
 */
vector<vector<int>> bruteForceApproach(vector<vector<int>> intervals);

/**
 * Approach: This is a more efficient single-pass approach.
 *           1. Sort the intervals based on their starting points.
 *           2. Initialize an answer list with the first interval.
 *           3. Iterate through the rest of the sorted intervals. For each
 *              interval, compare it with the last interval in the answer list.
 *           4. If they overlap, merge them by updating the end of the last
 *              interval in the answer list. If they don't overlap, add the
 *              current interval to the answer list.
 *
 * Time Complexity: O(N log N) due to sorting. The merging pass is O(N).
 * Space Complexity: O(N) for storing the answer.
 */
vector<vector<int>> optimalApproach(vector<vector<int>> intervals);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<vector<int>> intervals(n, vector<int>(2));

    for (int i = 0; i < n; i++) {
      cin >> intervals[i][0] >> intervals[i][1];
    }

    vector<vector<int>> bruteForceApproachResult =
        bruteForceApproach(intervals);
    vector<vector<int>> optimalApproachResult = optimalApproach(intervals);

    cout << "Brute-Force Approach: [ ";
    for (auto i : bruteForceApproachResult) {
      cout << "[ ";
      for (auto j : i) {
        cout << j << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Optimal Approach: [ ";
    for (auto i : optimalApproachResult) {
      cout << "[ ";
      for (auto j : i) {
        cout << j << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<vector<int>> bruteForceApproach(vector<vector<int>> intervals) {
  // Sort in ascending order of 0th index (start).
  sort(intervals.begin(), intervals.end());
  vector<vector<int>> ans;

  for (int i = 0; i < intervals.size(); i++) {
    int start = intervals[i][0];
    int end = intervals[i][1];

    if (!ans.empty() && end <= ans.back()[1]) continue;

    for (int j = i + 1; j < intervals.size(); j++) {
      if (intervals[j][0] <= end) {
        end = max(end, intervals[j][1]);
      } else {
        break;
      }
    }

    ans.push_back({start, end});
  }

  return ans;
}

vector<vector<int>> optimalApproach(vector<vector<int>> intervals) {
  // Sort in ascending order of 0th index (start).
  sort(intervals.begin(), intervals.end());
  vector<vector<int>> ans;

  for (int i = 0; i < intervals.size(); i++) {
    if (ans.empty() || ans.back()[1] < intervals[i][0]) {
      ans.push_back(intervals[i]);
    } else {
      ans.back()[1] = max(ans.back()[1], intervals[i][1]);
    }
  }

  return ans;
}