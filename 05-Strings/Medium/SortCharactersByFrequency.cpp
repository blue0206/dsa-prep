/*
 * Problem: Sort Characters By Frequency (LeetCode #451)
 * Link: https://leetcode.com/problems/sort-characters-by-frequency/description/
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

/**
 * Approach: This approach uses a hash map to count character frequencies and
 *           then sorts based on those frequencies.
 *           1.  Create a hash map to store the frequency of each character in
 *               the string.
 *           2.  Transfer the map's contents to a vector of pairs, where each
 *               pair is `{frequency, character}`.
 *           3.  Sort this vector in descending order based on frequency.
 *           4.  Build the final string by iterating through the sorted vector
 *               and appending each character the required number of times.
 *
 * Time Complexity: O(N + K log K), where K is the number of unique characters.
 * Space Complexity: O(K) for the map and vector, plus O(N) for the result.
 */
string stdSortApproach(string s);

/**
 * Approach: This approach uses bucket sort, which is more efficient as it
 *           avoids a comparison-based sort.
 *           1.  Create a hash map to count character frequencies.
 *           2.  Create a vector of strings (the "buckets"), where the index
 *               corresponds to a frequency. The size of this vector is `N+1`.
 *           3.  Iterate through the frequency map and place each character into
 *               the appropriate bucket. Characters with the same frequency are
 *               appended to the same bucket string.
 *           4.  Build the result by iterating through the buckets from the
 *               highest frequency down to the lowest, appending the characters
 *               from each bucket.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the buckets, plus O(K) for the map.
 */
string bucketSortApproach(string s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "String: " << s << endl;

    cout << "Result (std::sort Approach): " << stdSortApproach(s) << endl;
    cout << "Result (Bucket-Sort Approach): " << bucketSortApproach(s) << endl;

    cout << endl;
  }

  return 0;
}

string stdSortApproach(string s) {
  unordered_map<char, int> fq;
  for (auto i : s) {
    fq[i]++;
  }

  vector<pair<int, char>> freq_vec;
  for (auto i : fq) {
    freq_vec.push_back({i.second, i.first});
  }
  // Sort in descending order of frequency
  sort(freq_vec.rbegin(), freq_vec.rend());

  string str = "";
  for (const auto &p : freq_vec) {
    str.append(p.first, p.second);
  }

  return str;
}

string bucketSortApproach(string s) {
  unordered_map<char, int> fq;
  for (auto i : s) {
    fq[i]++;
  }

  vector<string> bucket(s.length() + 1, "");
  for (auto i : fq) {
    bucket[i.second] += i.first;
  }

  string ans = "";
  for (int i = bucket.size() - 1; i > 0; i--) {
    for (char c : bucket[i]) {
      ans.append(i, c);
    }
  }

  return ans;
}
