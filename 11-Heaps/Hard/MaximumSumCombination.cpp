/*
 * Problem: Maximum Sum Combination
 * Link: https://www.geeksforgeeks.org/problems/maximum-sum-combination/1
 *
 * Approach: A brute-force approach of generating all N*N sums and sorting them
 *           would be too slow (O(N^2 log(N^2))). A more optimal approach uses
 *           a max-priority queue to find the `k` largest sums efficiently.
 *
 *           1.  **Sort:** Sort both input arrays `a` and `b` in descending
 *               order. This ensures that `a[0] + b[0]` is the largest possible
 *               sum.
 *           2.  **Initialization:** Push the largest sum (`a[0] + b[0]`) and
 *               its corresponding indices `(0, 0)` into a max-priority queue.
 *               Use a `set` to keep track of visited index pairs to avoid
 *               duplicates.
 *           3.  **Greedy Extraction:** Loop `k` times. In each iteration:
 *               a. Pop the top element from the priority queue (which is the
 *                  current largest sum). Add this sum to the result.
 *               b. From the popped indices `(i, j)`, generate the next two
 *                  potential candidates for large sums: `(i, j+1)` and
 *                  `(i+1, j)`.
 *               c. If these new index pairs are valid and have not been
 *                  visited, push their sums and indices into the priority
 *                  queue and mark them as visited.
 *
 * Time Complexity: O(N log N + k log k)
 * Space Complexity: O(k)
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    cout << "k: " << k << endl;
    cout << "Input Array A: [ ";
    for (int i : a) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "Input Array B: [ ";
    for (int i : b) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = topKSumPairs(a, b, k);

    cout << "Result: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
  sort(a.begin(), a.end(), greater<int>());
  sort(b.begin(), b.end(), greater<int>());

  int n = a.size();
  set<pii> visited;
  priority_queue<ppii> maxheap;
  maxheap.push({a[0] + b[0], {0, 0}});
  visited.insert({0, 0});

  vector<int> ans;
  while (!maxheap.empty() && ans.size() < k) {
    int sum = maxheap.top().first;
    auto [i, j] = maxheap.top().second;
    maxheap.pop();
    ans.emplace_back(sum);

    // Explore the next candidate from array `b`.
    if (visited.find({i, j + 1}) == visited.end() && j + 1 < n) {
      int newSum = a[i] + b[j + 1];
      pii newIndices = {i, j + 1};
      maxheap.push({newSum, newIndices});
      visited.insert({i, j + 1});
    }

    // Explore the next candidate from array `a`.
    if (visited.find({i + 1, j}) == visited.end() && i + 1 < n) {
      int newSum = a[i + 1] + b[j];
      pii newIndices = {i + 1, j};
      maxheap.push({newSum, newIndices});
      visited.insert({i + 1, j});
    }
  }

  return ans;
}
