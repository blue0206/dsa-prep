/*
 * Problem: Job Sequencing Problem
 * Link:
 * https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;

/**
 * Approach: This is a classic greedy problem. The intuition is to always try
 *           to complete the jobs with the highest profit first. To maximize
 *           the total profit, we should schedule each high-profit job as late
 *           as possible, right before its deadline, to leave earlier slots
 *           open for other jobs.
 *
 *           1.  **Sort:** Combine the jobs into a struct/pair and sort them in
 *               descending order of their profit.
 *           2.  **Track Time Slots:** Create a boolean array `slots` to keep
 *               track of which time slots are occupied.
 *           3.  **Greedy Scheduling:** Iterate through the sorted jobs. For
 *               each job, find the latest available time slot at or before its
 *               deadline. If a slot is found, schedule the job there, mark the
 *               slot as taken, and add the profit to the total.
 *
 * Time Complexity: O(N log N + N * M), where M is the max deadline.
 * Space Complexity: O(M)
 */
vector<int> jobSequencing(const vector<int>& deadline,
                          const vector<int>& profit);

/**
 * Note: Will be implemented after I learn DSU concept in Graphs section.
 *
 * Approach:
 *
 * Time Complexity:
 * Space Complexity:
 */
vector<int> dsuApproach(const vector<int>& deadline, const vector<int>& profit);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> deadline(n);
    for (int i = 0; i < n; i++) cin >> deadline[i];
    vector<int> profit(n);
    for (int i = 0; i < n; i++) cin >> profit[i];

    cout << "Deadlines: [ ";
    for (int i : deadline) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "Profits: [ ";
    for (int i : profit) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = jobSequencing(deadline, profit);
    vector<int> ans2 = dsuApproach(deadline, profit);

    cout << "Result (Basic Approach): " << endl;
    cout << "Taken Jobs: " << ans[0] << endl;
    cout << "Max Profit: " << ans[1] << endl;

    cout << "Result (DSU Approach): " << endl;
  }

  return 0;
}

vector<int> jobSequencing(vector<int>& deadline, vector<int>& profit) {
  vector<pii> jobs;
  int maxTime = 0;
  for (int i = 0; i < deadline.size(); i++) {
    jobs.push_back({profit[i], deadline[i]});
    maxTime = max(maxTime, deadline[i]);
  }
  sort(jobs.begin(), jobs.end(), [](pii& one, pii& two) {
    if (one.first != two.first) {
      return one.first > two.first;
    }
    return one.second < two.second;
  });

  vector<bool> times(maxTime + 1, false);
  int takenJobs = 0;
  int maxProfit = 0;
  for (int i = 0; i < jobs.size(); i++) {
    int jobDeadline = jobs[i].second;
    while (jobDeadline >= 1 && times[jobDeadline]) jobDeadline--;

    if (jobDeadline >= 1) {
      times[jobDeadline] = true;
      takenJobs++;
      maxProfit += jobs[i].first;
    }
  }

  return {takenJobs, maxProfit};
}

vector<int> dsuApproach(vector<int>& deadline, vector<int>& profit) {}
