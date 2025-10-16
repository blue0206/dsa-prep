/*
 * Problem: Ninja's Training
 * Link:
 * https://www.naukri.com/code360/problems/ninja-s-training_3621003?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This is a top-down DP approach (memoization). The state is defined
 *           by `dp[day][last_task]`, representing the maximum points achievable
 *           from day 0 up to `day`, given that `last_task` was performed on the
 *           previous day. The function explores all valid tasks for the current
 *           day and recursively calculates the max points from the previous
 *           day.
 *
 * Time Complexity: O(N * 4 * 3) ~ O(N)
 * Space Complexity: O(N * 4) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(int n, vector<vector<int>>& points);
int memoization(const vector<vector<int>>& points, vector<vector<int>>& dp,
                int day, int last_task);

/**
 * Approach: This is a bottom-up DP approach (tabulation). We create a DP table
 *           `dp[day][task]` which stores the maximum points up to `day`, with
 *           `task` being the activity performed on that day. We iterate from
 *           day 0 to N-1, and for each day, we calculate the max points for
 *           each possible task based on the results from the previous day.
 *
 * Time Complexity: O(N * 3 * 3) ~ O(N)
 * Space Complexity: O(N * 4) for the DP table.
 */
int tabulationApproach(int n, vector<vector<int>>& points);

/**
 * Approach: This is a space-optimized version of the tabulation approach.
 *           To calculate the results for the current day, we only need the
 *           results from the previous day. We can therefore use a single
 *           `prev` array to store the previous day's DP values, reducing the
 *           space complexity from O(N*4) to O(4).
 *
 * Time Complexity: O(N * 3 * 3) ~ O(N)
 * Space Complexity: O(4) ~ O(1)
 */
int optimalApproach(int n, vector<vector<int>>& points);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> points(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
      cin >> points[i][0] >> points[i][1] >> points[i][2];
    }

    cout << "Points: [ ";
    for (auto i : points) {
      cout << "[ " << i[0] << ", " << i[1] << ", " << i[2] << " ] ";
    }
    cout << "]" << endl;

    cout << "Maximum Points (Memoization): " << memoizationApproach(n, points)
         << endl;
    cout << "Maximum Points (Tabulation): " << tabulationApproach(n, points)
         << endl;
    cout << "Maximum Points (Optimal): " << optimalApproach(n, points) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(int n, vector<vector<int>>& points) {
  vector<vector<int>> dp(n, vector<int>(4, -1));
  return memoization(points, dp, n - 1, 3);
}

int memoization(const vector<vector<int>>& points, vector<vector<int>>& dp,
                int day, int last_task) {
  if (day == 0) {  // Base Case: first day
    int maxi = 0;
    for (int task = 0; task <= 2; ++task) {
      if (task != last_task) {
        maxi = max(maxi, points[0][task]);
      }
    }
    return maxi;
  }
  if (dp[day][last_task] != -1) return dp[day][last_task];

  int maxi = 0;
  // For the current day, try all possible tasks
  for (int task = 0; task <= 2; ++task) {
    if (task != last_task) {
      // Points for today + max points from previous days
      int current_points =
          points[day][task] + memoization(points, dp, day - 1, task);
      maxi = max(maxi, current_points);
    }
  }
  return dp[day][last_task] = maxi;
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(int n, vector<vector<int>>& points) {
  vector<vector<int>> dp(n, vector<int>(4, 0));

  // Base case for day 0
  dp[0][0] = points[0][0];
  dp[0][1] = points[0][1];
  dp[0][2] = points[0][2];
  dp[0][3] = max({points[0][0], points[0][1], points[0][2]});

  for (int day = 1; day < n; day++) {
    for (int last_task = 0; last_task < 4; last_task++) {
      for (int task = 0; task < 3; task++) {
        if (task != last_task) {
          int current_points = points[day][task] + dp[day - 1][task];
          dp[day][last_task] = max(dp[day][last_task], current_points);
        }
      }
    }
  }

  return dp[n - 1][3];
}

//-------------------------------OPTIMAL APPROACH-------------------------------
int optimalApproach(int n, vector<vector<int>>& points) {
  vector<int> prev(3);
  prev[0] = max(points[0][1], points[0][2]);
  prev[1] = max(points[0][0], points[0][2]);
  prev[2] = max(points[0][1], points[0][0]);
  for (int i = 1; i < n; i++) {
    int maxScore = 0;
    vector<int> newPrev(3, -1);
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        if (k != j) {
          int score = points[i][k] + prev[k];
          maxScore = max(maxScore, score);
          newPrev[j] = max(newPrev[j], score);
        }
      }
    }
    prev = newPrev;
  }

  return max(prev[0], max(prev[1], prev[2]));
}
