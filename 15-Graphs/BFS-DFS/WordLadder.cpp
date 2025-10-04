/*
 * Problem: Word Ladder (LeetCode #127)
 * Link: https://leetcode.com/problems/word-ladder/description/
 *
 * Approach: This problem can be modeled as finding the shortest path in an
 *           unweighted graph, which is a perfect use case for Breadth-First
 *           Search (BFS).
 *           1.  **Graph Representation:** The words are the nodes of the
 *               graph. An edge exists between two words if they differ by
 *               exactly one character.
 *           2.  **BFS Traversal:** We start a BFS from the `beginWord`. The
 *               search proceeds in levels, where each level corresponds to one
 *               step in the transformation sequence.
 *           3.  **Generating Neighbors:** For each word in the current level,
 *               we generate all possible one-character transformations. We
 *               check if each new word exists in the `wordList`.
 *           4.  **Visited Set:** An `unordered_set` is used for O(1) lookups
 *               of valid words. When a valid transformed word is found and
 *               added to the queue, it's removed from the set to prevent
 *               cycles and redundant processing.
 *
 * Time Complexity: O(N * L^2), where N is the number of words and L is the
 *                  length of each word.
 * Space Complexity: O(N * L) for the set and queue.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int ladderLength(string beginWord, string endWord, vector<string>& wordList);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string beginWord, endWord;
    cin >> beginWord >> endWord;

    int n;
    cin >> n;

    vector<string> wordList(n);
    for (int i = 0; i < n; i++) {
      cin >> wordList[i];
    }

    cout << "Begin Word: " << beginWord << endl;
    cout << "End Word: " << endWord << endl;
    cout << "Word List: [ ";
    for (auto val : wordList) {
      cout << val << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Ladder Length: "
         << ladderLength(beginWord, endWord, wordList) << endl;
  }

  return 0;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
  unordered_set<string> st;
  for (int i = 0; i < wordList.size(); i++) {
    st.insert(wordList[i]);
  }

  if (st.find(endWord) == st.end()) return 0;

  queue<string> q;
  q.push(beginWord);

  int distance = 1;
  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      string currentWord = q.front();
      q.pop();

      for (int j = 0; j < currentWord.length(); j++) {
        string nextWord = currentWord;
        for (int k = 0; k < 26; k++) {
          nextWord[j] = 'a' + k;
          if (nextWord == endWord) {
            return distance + 1;
          } else if (nextWord != currentWord) {
            if (st.find(nextWord) != st.end()) {
              q.push(nextWord);
              st.erase(nextWord);
            }
          }
        }
      }
    }
    distance++;
  }

  return 0;
}
