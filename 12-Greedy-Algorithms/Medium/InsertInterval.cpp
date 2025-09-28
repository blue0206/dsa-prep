/*
 * Problem: Insert Interval (LeetCode #57)
 * Link: https://leetcode.com/problems/insert-interval/description/
 *
 * Approach: This solution follows a two-step process. First, it creates a new
 *           list of intervals by manually inserting the `newInterval` into the
 *           original sorted list, ensuring the new list remains sorted by
 *           start times. Then, it applies a standard "Merge Intervals"
 *           algorithm to this newly created list.
 *
 *           1.  **Insert:** Iterate through the original intervals and build a
 *               new list, finding the correct position to insert `newInterval`
 *               based on its start time.
 *           2.  **Merge:** Iterate through the combined and sorted list.
 *               Maintain a result list. If the current interval overlaps with
 *               the last interval in the result, merge them by updating the
 *               end time. Otherwise, add the current interval as a new entry.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> insert(const vector<vector<int>>& intervals,
                           vector<int> newInterval);

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

    vector<int> newInterval(2);
    cin >> newInterval[0] >> newInterval[1];

    cout << "Intervals: [ ";
    for (auto rows : intervals) {
      cout << "[ ";
      for (int i : rows) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "New Interval: [ " << newInterval[0] << ", " << newInterval[1]
         << " ]" << endl;

    vector<vector<int>> ans = insert(intervals, newInterval);

    cout << "Result: [ ";
    for (auto rows : ans) {
      cout << "[ ";
      for (int i : rows) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<vector<int>> insert(vector<vector<int>>& intervals,
                           vector<int>& newInterval) {
  // Step 1: Create a new sorted list by inserting newInterval.
  vector<vector<int>> newIntervals;
  bool placed = false;
  for (int i = 0; i < intervals.size(); i++) {
    if (!placed && intervals[i][0] > newInterval[0]) {
      newIntervals.push_back(newInterval);
      placed = true;
    } else if (!placed && intervals[i][0] == newInterval[0]) {
      if (intervals[i][1] >= newInterval[1]) {
        newIntervals.push_back(newInterval);
        placed = true;
      } else {
        newIntervals.push_back(intervals[i]);
        newIntervals.push_back(newInterval);
        placed = true;
        continue;
      }
    }

    newIntervals.push_back(intervals[i]);
  }

  // Handle case where newInterval is the last one to be inserted.
  if (!placed) {
    newIntervals.push_back(newInterval);
    placed = true;
  }

  // Step 2: Apply the standard merge intervals algorithm.
  vector<vector<int>> ans;
  for (int i = 0; i < newIntervals.size(); i++) {
    if (ans.empty() || ans.back()[1] < newIntervals[i][0]) {
      ans.push_back(newIntervals[i]);
    } else if (ans.back()[1] < newIntervals[i][1]) {
      ans[ans.size() - 1][1] = newIntervals[i][1];
    }
  }

  return ans;
}
