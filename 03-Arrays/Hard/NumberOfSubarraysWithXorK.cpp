/*
 * Problem: Number of Subarrays with XOR k
 *
 * Statement: For a given array of size 'n' and a number 'k', find all subarrays
 *            that have a XOR of 'k'.
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach generates every possible subarray using two nested
 *           loops. The outer loop fixes the starting index `i`, and the inner
 *           loop iterates from `i` to the end of the array, defining the
 *           ending index `j`. For each subarray, it calculates the XOR sum and
 *           increments a counter if the sum equals `k`.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
int bruteForceApproach(vector<int>& arr, int k);

/**
 * Approach: This optimal approach uses a hash map and the properties of XOR.
 *           The key insight is that if the prefix XOR up to index `i` is
 *           `pXor`, and the prefix XOR up to a previous index `j` was `y`, then
 *           the XOR sum of the subarray between them is `pXor ^ y`. We want
 *           this to be `k`, so `pXor ^ y = k`, which implies `y = pXor ^ k`.
 *           We iterate through the array, calculating the current `pXor`. For
 *           each `pXor`, we check the hash map for the count of the required
 *           previous prefix XOR (`pXor ^ k`) and add it to our total. We then
 *           update the map with the frequency of the current `pXor`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int optimalApproach(vector<int>& arr, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Subarrays with XOR " << k << ": " << bruteForceApproach(arr, k)
         << endl;

    cout << "Subarrays with XOR " << k << ": " << optimalApproach(arr, k)
         << endl;

    cout << endl;
  }

  return 0;
}

int bruteForceApproach(vector<int>& arr, int k) {
  int count = 0;

  for (int i = 0; i < arr.size(); i++) {
    int pXor = 0;
    for (int j = i; j < arr.size(); j++) {
      pXor ^= arr[j];
      if (pXor == k) count++;
    }
  }

  return count;
}

int optimalApproach(vector<int>& arr, int k) {
  int count = 0;
  // This map stores the frequency of each prefix XOR value encountered.
  unordered_map<int, int> xorHash;

  int pXor = 0;
  xorHash[pXor]++;
  for (int i = 0; i < arr.size(); i++) {
    pXor ^= arr[i];
    count += xorHash[pXor ^ k];
    xorHash[pXor]++;
  }

  return count;
}