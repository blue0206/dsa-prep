/*
 * Problem: Longest Valid Word with All Prefixes
 * Link:
 * https://www.geeksforgeeks.org/problems/longest-valid-word-with-all-prefixes/1
 *
 * Approach: This problem is efficiently solved using a Trie.
 *           1.  **Trie Construction:** First, all words from the input list are
 *               inserted into a Trie. Each node in the Trie has a flag
 *               `endOfWord` to mark the end of a valid word.
 *           2.  **Sorting:** The input `words` array is sorted by length in
 *               descending order. For words of the same length, they are sorted
 *               lexicographically. This ensures that the first valid word we
 *               find will be the longest and lexicographically smallest.
 *           3.  **Validation:** We iterate through the sorted words. For each
 *               word, we traverse the Trie and check if every prefix of that
 *               word is a valid word (i.e., the `endOfWord` flag is true for
 *               every node in the path). The first word that satisfies this
 *               condition is the answer.
 *
 * Time Complexity: O(N * L) + O(N log(N))
 * Space Complexity: O(N * L)
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

 public:
  Trie() { root = new TrieNode(); }

  void insert(string& s) {
    TrieNode* iter = root;

    for (char ch : s) {
      int letter = ch - 'a';
      if (iter->children[letter] == NULL) {
        iter->children[letter] = new TrieNode();
      }
      iter = iter->children[letter];
    }

    iter->endOfWord = true;
  }

  bool validWord(string& s) {
    TrieNode* iter = root;

    for (char ch : s) {
      int letter = ch - 'a';
      iter = iter->children[letter];

      if (!iter->endOfWord) return false;
    }

    return true;
  }
};

string longestValidWord(vector<string>& words);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; i++) cin >> words[i];

    cout << "Input Array: [ ";
    for (string i : words) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Longest Valid Word: " << longestValidWord(words) << endl;

    cout << endl;
  }

  return 0;
}

string longestValidWord(vector<string>& words) {
  int n = words.size();
  sort(words.begin(), words.end(), [](string& a, string& b) {
    if (a.length() != b.length()) {
      return a.length() > b.length();
    }
    return a < b;
  });

  Trie* dict = new Trie();
  for (int i = 0; i < n; i++) {
    dict->insert(words[i]);
  }

  for (int i = 0; i < n; i++) {
    if (dict->validWord(words[i])) {
      return words[i];
    }
  }

  return "";
}
