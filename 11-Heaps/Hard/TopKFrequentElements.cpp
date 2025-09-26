/*
 * Problem: Top K Frequent Elements (LeetCode #347)
 * Link: https://leetcode.com/problems/top-k-frequent-elements/description/
 *
 * Approach: This problem can be solved efficiently by combining a hash map and
 *           a min-heap.
 *
 *           1.  **Frequency Counting:** First, iterate through the input array
 *               `nums` and use a hash map to store the frequency of each
 *               number. This takes O(N) time.
 *           2.  **Min-Heap for Top K:** Create a min-priority queue that will
 *               store pairs of `{frequency, number}`. This heap will be kept
 *               at a maximum size of `k`.
 *           3.  **Populating the Heap:** Iterate through the frequency map. For
 *               each `{number, frequency}` pair, push `{frequency, number}`
 *               into the min-heap. If the heap's size exceeds `k`, pop the top
 *               element. Since it's a min-heap, this removes the element with
 *               the smallest frequency, ensuring the heap always contains the
 *               `k` most frequent elements seen so far.
 *
 * Time Complexity: O(N log k)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;
vector<int> topKFrequent(const vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "k: " << k << endl;
    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = topKFrequent(nums, k);

    cout << "Result: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<int> topKFrequent(const vector<int>& nums, int k) {
  // Min-heap to store pairs of {frequency, number}.
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      minheap;

  // Step 1: Count frequencies of each number.
  unordered_map<int, int> mp;
  for (int num : nums) mp[num]++;

  // Step 2: Push to min-heap and maintain size k.
  for (auto it : mp) {
    minheap.push({it.second, it.first});
    if (minheap.size() > k) minheap.pop();
  }

  vector<int> ans;
  // Step 3: Extract the k elements from the heap.
  while (!minheap.empty()) {
    ans.emplace_back(minheap.top().second);
    minheap.pop();
  }

  return ans;
}
