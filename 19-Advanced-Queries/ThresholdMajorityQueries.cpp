/*
 * Problem: Threshold Majority Queries (LeetCode #3636)
 * Link: https://leetcode.com/problems/threshold-majority-queries/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

using pii = pair<int, int>;
struct Info {
  int l;
  int r;
  int t;
  int block;
  int idx;
};

/**
 * Approach: This approach uses Square Root Decomposition. The array is divided
 *           into `sqrt(N)` blocks.
 *           1.  **Preprocessing:** For each block, a frequency map of its
 *               elements is precomputed.
 *           2.  **Querying:** For a query `[l, r]`:
 *               - If `l` and `r` are in the same block, iterate from `l` to `r`
 *                 and find the majority element naively.
 *               - If they are in different blocks, handle the partial start
 *                 and end blocks naively. For the full blocks in between,
 *                 merge their precomputed frequency maps to get the counts for
 *                 the middle section.
 *               - Combine the counts from all parts to find the final answer.
 *
 * Time Complexity: O(N + Q * N) in the worst case, as merging block frequency
 *                  maps can take O(N) for each query.
 * Space Complexity: O(N) to store the precomputed block data.
 */
vector<int> sqrtDecomposition(vector<int>& nums, vector<vector<int>>& queries);

/**
 * Approach: This is an offline approach using Mo's Algorithm, which is highly
 *           efficient for range queries.
 *           1.  **Offline Processing:** Queries are reordered based on the
 *               block index of their left endpoint, which minimizes total
 *               pointer movement.
 *           2.  **Sliding Window:** A sliding window `[low, high]` is
 *               maintained. As we process the sorted queries, we `add` or
 *               `remove` elements from the window one by one to match the
 *               current query's range.
 *           3.  **Answering Queries:** After adjusting the window for a query,
 *               we use a frequency-tracking data structure (a map and an array
 *               of sets) to find the element with the highest frequency in
 *               O(1) time and check if it meets the threshold.
 *
 * Time Complexity: O((N + Q) * sqrt(N))
 * Space Complexity: O(N + Q)
 */
vector<int> moAlgorithm(vector<int>& nums, vector<vector<int>>& queries);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    vector<vector<int>> queries(q, vector<int>(3));
    for (int i = 0; i < q; i++) {
      cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
    }

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans1 = sqrtDecomposition(nums, queries);
    vector<int> ans2 = moAlgorithm(nums, queries);

    cout << "Result (Sqrt Decomposition):" << endl;
    for (int i = 0; i < q; i++) {
      cout << "l: " << queries[i][0] << " r: " << queries[i][1]
           << " threshold: " << queries[i][2] << "Result: " << ans1[i] << endl;
    }

    cout << "Result (Mo's Algorithm):" << endl;
    for (int i = 0; i < q; i++) {
      cout << "l: " << queries[i][0] << " r: " << queries[i][1]
           << " threshold: " << queries[i][2] << "Result: " << ans2[i] << endl;
    }
  }

  return 0;
}

//-------------------------SQRT DECOMPOSITION APPROACH--------------------------
vector<int> sqrtDecomposition(vector<int>& nums, vector<vector<int>>& queries) {
  int n = nums.size();
  int q = queries.size();

  int blockSize = ceil(sqrt(n));
  vector<unordered_map<int, int>> blocks(blockSize);
  for (int i = 0; i < n; i += blockSize) {
    unordered_map<int, int> counts;
    int maxCount = 0;
    int val = -1;
    for (int j = i; j < i + blockSize && j < n; j++) {
      counts[nums[j]]++;

      if (counts[nums[j]] > maxCount) {
        maxCount = counts[nums[j]];
        val = nums[j];
      } else if (counts[nums[j]] == maxCount) {
        val = min(val, nums[j]);
      }
    }

    blocks[i / blockSize] = counts;
  }

  vector<int> ans(q, -1);
  for (int i = 0; i < q; i++) {
    int l = queries[i][0];
    int r = queries[i][1];
    int t = queries[i][2];

    int startBlock = l / blockSize;
    int endBlock = r / blockSize;
    unordered_map<int, int> counts;
    int maxCount = 0;
    int val = 0;

    if (startBlock == endBlock) {
      for (int i = l; i <= r; i++) {
        counts[nums[i]]++;
        if (counts[nums[i]] > maxCount) {
          maxCount = counts[nums[i]];
          val = nums[i];
        } else if (counts[nums[i]] == maxCount) {
          val = min(val, nums[i]);
        }
      }
    } else {
      // Left Block.
      for (int i = l; i < (startBlock + 1) * blockSize; i++) {
        counts[nums[i]]++;
        if (counts[nums[i]] > maxCount) {
          maxCount = counts[nums[i]];
          val = nums[i];
        } else if (counts[nums[i]] == maxCount) {
          val = min(val, nums[i]);
        }
      }

      // Right Block.
      for (int i = r; i >= endBlock * blockSize; i--) {
        counts[nums[i]]++;
        if (counts[nums[i]] > maxCount) {
          maxCount = counts[nums[i]];
          val = nums[i];
        } else if (counts[nums[i]] == maxCount) {
          val = min(val, nums[i]);
        }
      }

      // Middle Blocks.
      for (int i = startBlock + 1; i < endBlock; i++) {
        for (auto [num, fq] : blocks[i]) {
          counts[num] += fq;
          if (counts[num] > maxCount) {
            maxCount = counts[num];
            val = num;
          } else if (counts[num] == maxCount) {
            val = min(val, num);
          }
        }
      }
    }

    if (maxCount >= t) {
      ans[i] = val;
    }
  }

  return ans;
}

//-------------------------------MO'S ALGORITHM---------------------------------
vector<int> moAlgorithm(vector<int>& nums, vector<vector<int>>& queries) {
  int n = nums.size();
  int q = queries.size();

  int blockSize = ceil(sqrt(n));
  vector<Info> pq;
  for (int i = 0; i < q; i++) {
    int l = queries[i][0];
    int r = queries[i][1];
    int t = queries[i][2];

    pq.push_back({l, r, t, l / blockSize, i});
  }

  sort(pq.begin(), pq.end(), [](Info& a, Info& b) {
    if (a.block != b.block) {
      return a.block < b.block;
    }
    if (a.block % 2) {
      return a.r < b.r;
    }
    return a.r > b.r;
  });

  vector<set<int>> fq(n + 1);
  unordered_map<int, int> counts;
  int maxFq = 0;
  vector<int> ans(q, -1);

  auto add = [&](int idx) {
    int num = nums[idx];

    fq[counts[num]].erase(num);
    counts[num]++;
    fq[counts[num]].insert(num);

    if (counts[num] > maxFq) {
      maxFq = counts[num];
    }
  };

  auto remove = [&](int idx) {
    int num = nums[idx];

    fq[counts[num]].erase(num);
    counts[num]--;
    if (counts[num] > 0) {
      fq[counts[num]].insert(num);
    }

    if (fq[maxFq].empty()) {
      while (maxFq > 0 && fq[maxFq].empty()) maxFq--;
    }
  };

  int low = 0;
  int high = -1;
  for (int i = 0; i < q; i++) {
    auto [l, r, t, block, idx] = pq[i];

    while (high < r) {
      high++;
      add(high);
    }
    while (low > l) {
      low--;
      add(low);
    }
    while (high > r) {
      remove(high);
      high--;
    }
    while (low < l) {
      remove(low);
      low++;
    }

    if (maxFq >= t && !fq[maxFq].empty()) {
      ans[idx] = *(fq[maxFq].begin());
    }
  }

  return ans;
}
