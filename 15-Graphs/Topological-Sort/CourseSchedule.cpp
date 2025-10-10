/*
 * Problem: Course Schedule (LeetCode #207)
 * Link: https://leetcode.com/problems/course-schedule/description/
 *
 * Approach: This problem can be modeled as finding a cycle in a directed
 *           graph. If the course prerequisites form a cycle (e.g., A needs B,
 *           B needs C, and C needs A), it's impossible to finish all courses.
 *           This can be solved using a topological sort approach (Kahn's
 *           algorithm).
 *           1.  Build an adjacency list and an array to store the in-degree of
 *               each course.
 *           2.  Initialize a queue with all courses that have an in-degree of
 *               0.
 *           3.  Process the queue. For each course taken, decrement the
 *               in-degree of its dependent courses. If a dependent course's
 *               in-degree becomes 0, add it to the queue.
 *           4.  If the total number of courses taken equals the total number
 *               of courses, it means there were no cycles.
 *
 * Time Complexity: O(V + E), where V is courses and E is prerequisites.
 * Space Complexity: O(V + E) for the adjacency list and queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int numCourses, m;
    cin >> numCourses >> m;

    vector<vector<int>> prerequisites;
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      prerequisites.push_back({u, v});
    }

    cout << "Prerequisites: [";
    for (auto u : prerequisites) {
      cout << "[ ";
      for (int v : u) {
        cout << v << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Can Finish: "
         << (canFinish(numCourses, prerequisites) ? "True" : "False") << endl;
  }

  return 0;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
  vector<vector<int>> adj(numCourses);
  for (int i = 0; i < prerequisites.size(); i++) {
    adj[prerequisites[i][1]].emplace_back(prerequisites[i][0]);
  }

  vector<int> inCount(numCourses);
  for (int i = 0; i < numCourses; i++) {
    for (int node : adj[i]) {
      inCount[node]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < numCourses; i++) {
    if (inCount[i] == 0) q.push(i);
  }

  int coursesTaken = 0;
  while (!q.empty()) {
    int course = q.front();
    q.pop();

    coursesTaken++;
    for (int depCourse : adj[course]) {
      inCount[depCourse]--;
      if (inCount[depCourse] == 0) q.push(depCourse);
    }
  }

  return coursesTaken == numCourses;
}
