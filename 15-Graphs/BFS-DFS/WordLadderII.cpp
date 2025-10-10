/*
 * Problem: Word Ladder II (LeetCode #126)
 * Link: https://leetcode.com/problems/word-ladder-ii/description/
 *
 * Approach: This problem requires finding all shortest paths, which suggests a
 *           two-phase approach: first find the length of the shortest path
 *           and the path structure using BFS, then reconstruct the paths
 *           using DFS.
 *
 *           1.  **BFS to Build Parent Graph:**
 *               -   Perform a level-by-level BFS starting from `beginWord`.
 *               -   Use a map `parents` to store the predecessors of each
 *                   word. For a given word, `parents[word]` will be a vector
 *                   of all words that can lead to it in a shortest path.
 *               -   To ensure we only find shortest paths, we process the BFS
 *                   in strict levels. Words used in the current level are
 *                   erased from the main word set only after the entire level
 *                   is processed. This allows multiple shortest paths to
 *                   converge on the same word.
 *
 *           2.  **DFS to Reconstruct Paths:**
 *               -   Once the `endWord` is found, start a recursive DFS from
 *                   `endWord` backwards to `beginWord` using the `parents` map.
 *               -   Each successful traversal from `endWord` to `beginWord`
 *                   reconstructs one shortest path, which is then reversed and
 *                   added to the final answer.
 *
 * Time Complexity: Difficult to determine precisely, but it's roughly
 *                  O(N * L^2 * 26), where N is the number of words and L is the
 *                  word length. The DFS part can also be exponential in the
 *                  worst case depending on the number of paths.
 * Space Complexity: O(N * L) for the parent map and queue.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

vector<vector<string>> findLadders(string beginWord, string endWord,
                                   vector<string>& wordList);
void dfs(vector<vector<string>>& ans, vector<string>& seq,
         unordered_map<string, vector<string>>& parents, string& beginWord,
         string word);

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

    vector<vector<string>> ans = findLadders(beginWord, endWord, wordList);

    cout << "Shortest Sequences:" << endl;
    for (auto seq : ans) {
      cout << "[ ";
      for (auto word : seq) {
        cout << word << " ";
      }
      cout << "]" << endl;
    }
  }

  return 0;
}

vector<vector<string>> findLadders(string beginWord, string endWord,
                                   vector<string>& wordList) {
  unordered_set<string> wordSet(wordList.begin(), wordList.end());
  if (!wordSet.count(endWord)) return {};

  unordered_map<string, vector<string>> parents;
  queue<string> q;
  q.push(beginWord);

  bool found = false;
  while (!q.empty() && !found) {
    int size = q.size();
    unordered_set<string> usedWords;

    for (int i = 0; i < size; i++) {
      string currentWord = q.front();
      q.pop();

      for (int j = 0; j < currentWord.length(); j++) {
        string nextWord = currentWord;

        for (char c = 'a'; c <= 'z'; c++) {
          nextWord[j] = c;

          if (nextWord == currentWord) continue;

          if (nextWord == endWord) {
            parents[nextWord].emplace_back(currentWord);
            found = true;
          } else if (wordSet.count(nextWord)) {
            parents[nextWord].emplace_back(currentWord);

            // Add the next word to queue ONLY if it wasn't previously added.
            // Else, we only update its parents.
            if (!usedWords.count(nextWord)) {
              usedWords.insert(nextWord);
              q.push(nextWord);
            }
          }
        }
      }
    }

    for (string s : usedWords) {
      wordSet.erase(s);
    }
  }

  vector<vector<string>> ans;
  vector<string> seq;
  dfs(ans, seq, parents, beginWord, endWord);

  return ans;
}

void dfs(vector<vector<string>>& ans, vector<string>& seq,
         unordered_map<string, vector<string>>& parents, string& beginWord,
         string word) {
  seq.emplace_back(word);

  if (word == beginWord) {
    vector<string> temp(seq.rbegin(), seq.rend());
    ans.emplace_back(temp);
    seq.pop_back();
    return;
  }

  for (string next : parents[word]) {
    dfs(ans, seq, parents, beginWord, next);
  }

  seq.pop_back();
}
