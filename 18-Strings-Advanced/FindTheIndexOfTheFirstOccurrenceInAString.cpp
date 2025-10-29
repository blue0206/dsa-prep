/*
 * Problem: Find the Index of the First Occurrence in a String (LeetCode #28)
 * Link:
 * https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

ll getPow(ll base, ll n, ll m) {
  ll res = 1;
  while (n > 0) {
    if (n & 1) {
      res = ((res % m) * (base % m)) % m;
    }
    base = ((base % m) * (base % m)) % m;
    n >>= 1;
  }

  return res;
}

ll modInverse(ll n, ll m) { return getPow(n, m - 2, m); }

int getCharCode(char x) { return x - 'a'; }

class RabinKarp {
 private:
  const int P1 = 31;
  const int P2 = 37;
  const int M1 = 1e9 + 7;
  const int M2 = 1e9 + 9;

  int n;
  vector<ll> powers1, powers2, hash1, hash2;
  vector<ll> powersInv1, powersInv2;

  void precomputePowers(int n) {
    powers1.resize(n);
    powers2.resize(n);
    powersInv1.resize(n);
    powersInv2.resize(n);

    ll pInv1 = modInverse(P1, M1);
    ll pInv2 = modInverse(P2, M2);
    powers1[0] = 1;
    powers2[0] = 1;
    powersInv1[0] = 1;
    powersInv2[0] = 1;
    for (int i = 1; i < n; i++) {
      powers1[i] = (powers1[i - 1] * P1) % M1;
      powers2[i] = (powers2[i - 1] * P2) % M2;
      powersInv1[i] = (powersInv1[i - 1] * pInv1) % M1;
      powersInv2[i] = (powersInv2[i - 1] * pInv2) % M2;
    }
  }

  void computeHash(string& s, int n) {
    if (n == 0) return;

    hash1.resize(n);
    hash2.resize(n);

    hash1[0] = getCharCode(s[0]);
    hash2[0] = getCharCode(s[0]);

    for (int i = 1; i < n; i++) {
      hash1[i] = (hash1[i - 1] + (getCharCode(s[i]) * powers1[i])) % M1;
      hash2[i] = (hash2[i - 1] + (getCharCode(s[i]) * powers2[i])) % M2;
    }
  }

 public:
  RabinKarp(string& s) {
    n = s.length();

    precomputePowers(n);
    computeHash(s, n);
  }

  int getHash1(int l, int r) {
    ll res = hash1[r];
    if (l > 0) {
      res = (res - hash1[l - 1] + M1) % M1;
    }
    res = (res * powersInv1[l]) % M1;
    return res;
  }

  int getHash2(int l, int r) {
    ll res = hash2[r];
    if (l > 0) {
      res = (res - hash2[l - 1] + M2) % M2;
    }
    res = (res * powersInv2[l]) % M2;
    return res;
  }
};

/**
 * Approach: The Z-algorithm computes a "Z-array" for a given string. `z[i]`
 *           is the length of the longest common prefix between the original
 *           string and the suffix starting at `i`. To find a pattern `P` in a
 *           text `T`, we create a new string `S = P + '$' + T`. In the Z-array
 *           for `S`, any index `i` where `z[i]` equals the length of `P`
 *           indicates an occurrence of `P` in `T`.
 *
 * Time Complexity: O(N + M), where N is haystack length and M is needle length.
 * Space Complexity: O(N + M) for the combined string and Z-array.
 */
int zApproach(string haystack, string needle);
vector<int> zFunction(string& s);

/**
 * Approach: The Knuth-Morris-Pratt (KMP) algorithm uses a pre-computed "LPS"
 *           (Longest Proper Prefix which is also Suffix) array for the
 *           pattern. This array allows the algorithm to avoid redundant
 *           comparisons after a mismatch. Instead of starting the search over,
 *           it uses the LPS value to intelligently shift the pattern forward,
 *           resuming the comparison from where it left off.
 *
 * Time Complexity: O(N + M), where N is haystack length and M is needle length.
 * Space Complexity: O(M) for the LPS array.
 */
int kmpApproach(string haystack, string needle);
vector<int> kmp(string& s);

/**
 * Approach: The Rabin-Karp algorithm is a rolling hash algorithm. It computes
 *           a hash value for the pattern and for each substring of the text
 *           that has the same length as the pattern. If the hashes match, it
 *           performs a character-by-character comparison to confirm the match
 *           (to handle hash collisions). The "rolling" aspect allows the hash
 *           of the next substring to be calculated in O(1) time from the
 *           previous one. Double hashing with two different prime moduli is
 *           used to further reduce the probability of collisions.
 *
 * Time Complexity: O(N + M) on average. O(N * M) in the worst case (many hash
 *                  collisions), though very unlikely with double hashing.
 * Space Complexity: O(N + M) for the pre-computed hash structures.
 */
int rabinKarpApproach(string haystack, string needle);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string haystack, needle;
    cin >> haystack >> needle;

    cout << "Text: " << haystack << endl;
    cout << "Pattern: " << needle << endl;

    cout << "Index (Z-Algorithm): " << zApproach(haystack, needle) << endl;
    cout << "Index (KMP): " << kmpApproach(haystack, needle) << endl;
    cout << "Index (Rabin-Karp): " << rabinKarpApproach(haystack, needle)
         << endl;

    cout << endl;
  }

  return 0;
}

//---------------------------------Z-ALGORITHM----------------------------------
int zApproach(string haystack, string needle) {
  string s = needle + '$' + haystack;
  vector<int> z = zFunction(s);

  int n = needle.size();
  for (int i = n + 1; i < z.size(); i++) {
    if (z[i] == n) return i - n - 1;
  }

  return -1;
}

vector<int> zFunction(string& s) {
  int n = s.length();
  vector<int> z(n, 0);

  int l = 0;
  int r = 0;
  for (int i = 1; i < n; i++) {
    if (i <= r) {
      int k = i - l;
      z[i] = min(z[k], r - i + 1);
    }

    while (i + z[i] < n && s[z[i]] == s[z[i] + i]) {
      z[i]++;
    }

    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }

  return z;
}

//-------------------------------KMP APPROACH-----------------------------------
int kmpApproach(string haystack, string needle) {
  vector<int> lps = kmp(needle);

  int i = 0;
  int j = 0;
  while (i < haystack.length() && j < needle.length()) {
    if (haystack[i] == needle[j]) {
      i++;
      j++;
    } else if (j > 0) {
      j = lps[j - 1];
    } else {
      i++;
    }
  }

  if (j == needle.length()) return i - needle.length();
  return -1;
}

vector<int> kmp(string& s) {
  int i = 1;
  int j = 0;
  vector<int> lps(s.length(), 0);

  while (i < s.length()) {
    if (s[i] == s[j]) {
      lps[i] = j + 1;
      i++;
      j++;
    } else if (j > 0) {
      j = lps[j - 1];
    } else {
      i++;
    }
  }

  return lps;
}

//------------------------------RABIN-KARP APPROACH-----------------------------
int rabinKarpApproach(string haystack, string needle) {
  RabinKarp text(haystack), pattern(needle);

  int len = needle.length();
  int patternHash1 = pattern.getHash1(0, len - 1);
  int patternHash2 = pattern.getHash2(0, len - 1);

  int low = 0;
  int high = len - 1;
  while (high < haystack.length()) {
    int textHash1 = text.getHash1(low, high);
    int textHash2 = text.getHash2(low, high);

    if (patternHash1 == textHash1 && patternHash2 == textHash2) {
      bool match = true;
      for (int i = 0; i < len; i++) {
        if (haystack[i + low] != needle[i]) {
          match = false;
          break;
        }
      }

      if (match) return low;
    }

    low++;
    high++;
  }

  return -1;
}
