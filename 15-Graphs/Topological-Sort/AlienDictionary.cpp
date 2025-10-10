/*
 * Problem: Alien Dictionary
 * Link: https://www.geeksforgeeks.org/problems/alien-dictionary/1
 *
 * Approach: The problem of finding an alien alphabet's order can be modeled as
 *           a topological sort of a directed graph.
 *
 *           1.  **Graph Construction:** The characters are the vertices of the
 *               graph. The directed edges represent precedence rules. We can
 *               derive these rules by comparing adjacent words in the sorted
 *               dictionary. For any two adjacent words, `word1` and `word2`,
 *               the first character at which they differ tells us an ordering.
 *               If `word1[i] != word2[i]`, it implies that `word1[i]` must
 *               come before `word2[i]` in the alien alphabet. We add a
 *               directed edge `word1[i] -> word2[i]`.
 *
 *           2.  **Topological Sort:** Once the graph is built, we perform a
 *               topological sort (using Kahn's BFS-based algorithm) to find a
 *               linear ordering of the characters. If the topological sort
 *               produces an ordering that includes all unique characters, we
 *               have found the valid alien alphabet. If not, the dictionary
 *               contains a contradiction (a cycle).
 *
 * Time Complexity: O(N * L + K), where N is the number of words, L is the
 *                  average length of a word, and K is the number of unique
 *                  characters.
 * Space Complexity: O(K) for the graph and in-degree array.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

string findOrder(vector<string>& words);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; i++) {
      cin >> words[i];
    }

    cout << "Words: [ ";
    for (string s : words) {
      cout << s << " ";
    }
    cout << "]" << endl;

    string ans = findOrder(words);

    cout << "Lexicographical Order: " << ans << endl;
  }

  return 0;
}

string findOrder(vector<string>& words) {
  unordered_set<char> chars;
  for (string s : words) {
    for (char ch : s) chars.insert(ch);
  }

  unordered_map<char, vector<char>> adj;
  vector<int> inCount(26, 0);

  for (int i = 0; i < words.size() - 1; i++) {
    string w1 = words[i];
    string w2 = words[i + 1];

    if (w1.length() > w2.length() && w1.find(w2) == 0) {
      return "";
    }

    for (int j = 0; j < min(w1.length(), w2.length()); j++) {
      if (w1[j] != w2[j]) {
        adj[w1[j]].emplace_back(w2[j]);
        inCount[w2[j] - 'a']++;
        break;
      }
    }
  }

  queue<char> q;
  for (char ch : chars) {
    if (inCount[ch - 'a'] == 0) q.push(ch);
  }

  string ans = "";
  while (!q.empty()) {
    char node = q.front();
    q.pop();

    ans += node;
    for (char next : adj[node]) {
      inCount[next - 'a']--;
      if (inCount[next - 'a'] == 0) q.push(next);
    }
  }

  if (ans.length() != chars.size()) return "";
  return ans;
}
