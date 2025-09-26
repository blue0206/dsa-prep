/*
 * Problem: Task Scheduler (LeetCode #621)
 * Link: https://leetcode.com/problems/task-scheduler/description/
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: This approach simulates the CPU scheduling process time unit by
 *           time unit.
 *           1. A max-priority queue (`readyQueue`) stores the tasks that are
 *              ready to be executed, prioritized by their remaining frequency.
 *           2. A regular queue (`cooldownQueue`) stores tasks that have been
 *              recently executed and are in their cooldown period. It stores
 *              the remaining count and the time at which the task will be
 *              available again.
 *           3. In each time unit, we check the `cooldownQueue` to see if any
 *              tasks are ready to be moved back to the `readyQueue`.
 *           4. We then execute the highest-frequency task from the
 *              `readyQueue`. If a task is executed, its count is decremented,
 *              and if it still needs to be run, it's placed in the
 *              `cooldownQueue`.
 *           5. If the `readyQueue` is empty, the CPU is idle for that time
 *              unit.
 *
 * Time Complexity: O(T * log K), where T is the total time and K is the number
 *                  of unique tasks (at most 26).
 * Space Complexity: O(K)
 */
int simulationApproach(const vector<char>& tasks, int n);

/**
 * Approach: This is a more efficient approach that calculates the result
 *           directly. The length of the schedule is determined by the most
 *           frequent task.
 *
 * Time Complexity: O(N) to count frequencies.
 * Space Complexity: O(K) for the frequency map.
 */
int mathApproach(const vector<char>& tasks, int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    int k;
    cin >> n >> k;

    vector<char> tasks(n);
    for (int i = 0; i < n; i++) cin >> tasks[i];
    // The second input is the cooldown period `n`.

    cout << "Input Array: [ ";
    for (int i : tasks) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Least Interval (Simulation): " << simulationApproach(tasks, k)
         << endl;
    cout << "Least Interval (Mathematical): " << mathApproach(tasks, k) << endl;

    cout << endl;
  }

  return 0;
}

int simulationApproach(const vector<char>& tasks, int n) {
  unordered_map<char, int> counts;
  for (char c : tasks) {
    counts[c]++;
  }

  // Max-heap stores remaining counts of ready tasks.
  priority_queue<int> readyQueue;
  for (auto const& [task, count] : counts) {
    readyQueue.push(count);
  }

  // Cooldown queue stores {remaining_count, available_time}.
  queue<pair<int, int>> cooldownQueue;

  int time = 0;
  while (!readyQueue.empty() || !cooldownQueue.empty()) {
    time++;
    // Check if any task in cooldown is ready to be moved to the ready queue.
    if (!cooldownQueue.empty() && cooldownQueue.front().second == time) {
      readyQueue.push(cooldownQueue.front().first);
      cooldownQueue.pop();
    }

    // If there are ready tasks, execute one.
    if (!readyQueue.empty()) {
      int remaining = readyQueue.top() - 1;
      readyQueue.pop();

      // If the task still needs to be run, put it on cooldown.
      if (remaining > 0) {
        cooldownQueue.push({remaining, time + n});
      }
    }
    // If readyQueue is empty, the CPU is idle for this time unit.
  }

  return time;
}

int mathApproach(const vector<char>& tasks, int n) {
  if (n == 0) return tasks.size();

  vector<int> counts(26, 0);
  for (char task : tasks) {
    counts[task - 'A']++;
  }
  sort(counts.begin(), counts.end());

  int maxFreq = counts[25];
  int idleTime = (maxFreq - 1) * n;

  for (int i = 24; i >= 0 && counts[i] > 0; i--) {
    idleTime -= min(counts[i], maxFreq - 1);
  }

  idleTime = max(0, idleTime);
  return tasks.size() + idleTime;
}
