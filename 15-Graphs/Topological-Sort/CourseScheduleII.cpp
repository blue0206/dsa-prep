/*
 * Problem: Course Schedule II (LeetCode #210)
 * Link: https://leetcode.com/problems/course-schedule-ii/description/
 *
 * Approach: This problem is a direct extension of "Course Schedule I". Instead
 *           of just determining if a valid course order exists, we must return
 *           one such order. This is a classic topological sort problem.
 *           The solution uses Kahn's algorithm (a BFS-based approach).
 *           1.  Build an adjacency list and an in-degree array from the
 *               prerequisites.
 *           2.  Initialize a queue with all courses having an in-degree of 0.
 *           3.  While the queue is not empty, dequeue a course, add it to the
 *               resultant order (`ans`), and decrement the in-degree of all
 *               its neighbors.
 *           4.  If a neighbor's in-degree becomes 0, enqueue it.
 *           5.  Finally, if the number of courses in the result equals the
 *               total number of courses, a valid order was found. Otherwise, a
 *               cycle exists, and an empty list is returned.
 *
 * Time Complexity: O(V + E), where V is courses and E is prerequisites.
 * Space Complexity: O(V + E) for the adjacency list and queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);

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

    vector<int> ans = findOrder(numCourses, prerequisites);

    cout << "Course Order: [ ";
    for (int val : ans) {
      cout << val << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
  vector<vector<int>> adj(numCourses);
  for (int i = 0; i < prerequisites.size(); i++) {
    adj[prerequisites[i][1]].emplace_back(prerequisites[i][0]);
  }

  vector<int> inCount(numCourses, 0);
  for (int i = 0; i < numCourses; i++) {
    for (int course : adj[i]) {
      inCount[course]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < numCourses; i++) {
    if (inCount[i] == 0) q.push(i);
  }

  vector<int> ans;
  while (!q.empty()) {
    int course = q.front();
    q.pop();

    ans.emplace_back(course);
    for (int depCourse : adj[course]) {
      inCount[depCourse]--;
      if (inCount[depCourse] == 0) q.push(depCourse);
    }
  }

  if (ans.size() != numCourses) return {};
  return ans;
}
