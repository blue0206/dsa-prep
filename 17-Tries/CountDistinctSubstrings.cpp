/*
 * Problem: Count Distinct Substrings using Trie
 * Link:
 * https://www.naukri.com/code360/problems/count-distinct-substrings_985292?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem can be solved efficiently using a Trie. The total
 *           number of distinct substrings is equal to the total number of
 *           unique nodes in the Trie built from all substrings, plus one for
 *           the empty substring.
 *           1.  Iterate through the input string `s` with a starting index `i`.
 *           2.  For each `i`, start another loop with index `j` from `i` to the
 *               end of the string. This `s[i...j]` represents a substring.
 *           3.  Insert each character `s[j]` into the Trie. If a new node is
 *               created for a character, it signifies a new, distinct
 *               substring. Increment a counter for each new node.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2) in the worst case (for a string with all unique
 * chars).
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
 public:
  vector<TrieNode*> children;
  bool endOfWord;

  TrieNode() {
    children.assign(26, NULL);
    endOfWord = false;
  }
};

class Trie {
 private:
  TrieNode* root;
  int count;

 public:
  Trie() {
    root = new TrieNode();
    count = 0;
  }

  void insert(string& s) {
    TrieNode* iter = root;

    for (char ch : s) {
      int letter = ch - 'a';
      if (iter->children[letter] == NULL) {
        iter->children[letter] = new TrieNode();
      }

      iter = iter->children[letter];
    }

    if (!iter->endOfWord) {
      count++;
      iter->endOfWord = true;
    }
  }

  int getCount() { return count; }
};

int countDistinctSubstrings(string& s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string s;
    cin >> s;

    cout << "Input String: " << s << endl;

    cout << "Number of Distinct Substrings: " << countDistinctSubstrings(s)
         << endl;

    cout << endl;
  }

  return 0;
}

int countDistinctSubstrings(string& s) {
  Trie* trie = new Trie();

  for (int i = 0; i < s.length(); i++) {
    string temp = "";
    for (int j = i; j <= s.length(); j++) {
      trie->insert(temp);
      temp.push_back(s[j]);
    }
  }

  return trie->getCount();
}
