/*
 * Problem: Minimum Multiplications To Reach End
 * Link:
 * https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1
 *
 * Approach: This problem can be modeled as finding the shortest path in a
 * graph. The nodes of the graph are the numbers from 0 to 99999. A directed
 * edge exists from a number `u` to `v` if `v = (u * arr[i]) % 100000` for some
 * multiplier in the `arr` array. Each multiplication is one step, so all edge
 * weights are 1.
 *
 * The goal is to find the minimum number of steps (multiplications) to get from
 * `start` to `end`. Since all edge weights are uniform (equal to 1), this is a
 * classic Breadth-First Search (BFS) problem. We can use a queue to explore
 * the numbers level by level, where each level corresponds to an additional
 * multiplication. A `steps` array is used to keep track of the minimum steps to
 * reach each number and to avoid cycles and redundant computations.
 *
 * Time Complexity: O(N * M), where N is the number of multipliers and M is the
 *                  modulo (100000).
 * Space Complexity: O(M) for the steps array and the queue.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int minimumMultiplications(vector<int>& arr, int start, int end);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, start, end;
    cin >> n >> start >> end;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Start: " << start << endl;
    cout << "End: " << end << endl;
    cout << "Multipliers: [ ";
    for (int i : arr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Multiplications: "
         << minimumMultiplications(arr, start, end) << endl;

    cout << endl;
  }

  return 0;
}

int minimumMultiplications(vector<int>& arr, int start, int end) {
  const int m = 1e5;
  const int INF = 1e8;

  if (start == end) return 0;

  vector<int> steps(m, INF);
  queue<pii> q;  // {steps, node}

  q.push({0, start});
  steps[start] = 0;
  while (!q.empty()) {
    auto [step, node] = q.front();
    q.pop();

    for (int multiplier : arr) {
      int newNum = (node * multiplier) % m;

      if (step + 1 < steps[newNum]) {
        steps[newNum] = step + 1;
        if (newNum == end) return step + 1;
        q.push({step + 1, newNum});
      }
    }
  }

  return -1;
}
