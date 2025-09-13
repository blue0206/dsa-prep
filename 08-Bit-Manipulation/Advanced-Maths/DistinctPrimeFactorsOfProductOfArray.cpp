/*
 * Problem: Distinct Prime Factors of Product of Array (LeetCode #2521)
 * Link:
 * https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/description/
 *
 * Approach: This problem is solved by first finding all prime factors for each
 *           number in the input array and then counting the number of unique
 *           prime factors. A highly efficient way to find prime factors is by
 *           pre-computing the Smallest Prime Factor (SPF) for all numbers up to
 *           the maximum value in the array.
 *
 *           1.  **Pre-computation (Sieve for SPF):**
 *               - Find the maximum number (`maxNum`) in the input array.
 *               - Create an array `spf` of size `maxNum + 1`. `spf[i]` will
 *                 store the smallest prime factor of `i`.
 *               - Initialize `spf[i] = i` for all `i`.
 *               - Use a sieve to populate the `spf` array. For each prime `p`,
 *                 iterate through its multiples `j` and set `spf[j] = p` if
 *                 `spf[j]` is still `j`.
 *           2.  **Factorization and Collection:**
 *               - Initialize an empty hash set, `factors`, to store unique
 *                 prime factors.
 *               - For each number `num` in the input array, find its prime
 *                 factors by repeatedly dividing `num` by `spf[num]` and
 *                 inserting `spf[num]` into the set, until `num` becomes 1.
 *           3.  **Result:** The size of the `factors` set is the answer.
 *
 * Time Complexity: O(N * log(M) + M * log(log M)), where N is the number of
 *                  elements in `nums` and M is the maximum value in `nums`.
 * Space Complexity: O(M)
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

using namespace std;

int distinctPrimeFactors(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Distinct Prime Factors Count: " << distinctPrimeFactors(nums)
         << endl;

    cout << endl;
  }

  return 0;
}

int distinctPrimeFactors(vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }
  // Find the maximum number in the array to determine the sieve size.
  int maxNum = *max_element(nums.begin(), nums.end());

  // Pre-compute Smallest Prime Factor (SPF) using a sieve.
  vector<int> spf(maxNum + 1);
  iota(spf.begin(), spf.end(), 0);  // Fills spf with 0, 1, 2, 3, ...

  for (int i = 2; i * i <= maxNum; i++) {
    // If i is prime (its smallest prime factor is itself)
    if (spf[i] == i) {
      // Mark all multiples of i
      for (long long j = 1LL * i * i; j <= maxNum; j += i) {
        // If j's SPF hasn't been set yet, set it to i
        if (spf[j] == j) {
          spf[j] = i;
        }
      }
    }
  }

  // Use a set to store the distinct prime factors.
  unordered_set<int> factors;
  for (int num : nums) {
    // Decompose each number into its prime factors using the SPF array.
    while (num > 1) {
      factors.insert(spf[num]);
      num /= spf[num];
    }
  }

  return factors.size();
}
