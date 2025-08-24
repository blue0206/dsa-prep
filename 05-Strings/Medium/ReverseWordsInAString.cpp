/*
 * Problem: Reverse Words in a String (LeetCode #151)
 * Link: https://leetcode.com/problems/reverse-words-in-a-string/description/
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

/**
 * Approach: This method uses a stack to reverse the order of words.
 *           1. Iterate through the input string, building up words character
 *              by character.
 *           2. When a space is encountered, if the current word is not empty,
 *              push it onto a stack.
 *           3. After the loop, push the last word if it exists.
 *           4. Pop words from the stack one by one and append them to a result
 *              string, adding a space after each word except the last.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
string bruteForceApproach(string s);

/**
 * Approach: This is an optimal in-place solution with three main steps.
 *           1.  **Clean up spaces:** Use two pointers, `read` and `write`, to
 *               iterate through the string. This pass removes leading/trailing
 *               spaces and reduces multiple spaces between words to a single
 *               space. The string is resized to its new, clean length.
 *           2.  **Reverse the entire string:** Reverse all characters in the
 *               cleaned-up string. For example, "the sky is blue" becomes
 *               "eulb si yks eht".
 *           3.  **Reverse each word:** Iterate through the string again.
 *               Whenever a word is identified (bounded by spaces or ends of
 *               the string), reverse the characters of just that word. This
 *               turns "eulb si yks eht" into "blue is sky the".
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
string optimalApproach(string s);
void reverse(string& s, int start, int end);

int main() {
  int t;
  cin >> t;
  cin.ignore();  // Consume the newline character left by cin

  while (t--) {
    string s;
    getline(cin, s);

    cout << "String: " << s << endl;

    cout << "Result (Brute Force Approach): " << bruteForceApproach(s) << endl;
    cout << "Result (Optimal Approach): " << optimalApproach(s) << endl;

    cout << endl;
  }

  return 0;
}

string bruteForceApproach(string s) {
  stack<string> words;
  string str = "";
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == ' ') {
      if (!str.empty()) {
        words.push(str);
        str = "";
      }
    } else {
      str += s[i];
    }
  }
  if (!str.empty()) {
    words.push(str);
    str = "";
  }

  while (!words.empty()) {
    str += words.top();
    words.pop();
    if (words.size() > 0) {
      str += " ";
    }
  }

  return str;
}

string optimalApproach(string s) {
  int read = 0;
  int write = 0;

  // 1. Clean up unnecessary whitespace.
  while (read < s.length() && write < s.length()) {
    // Escape all whitespaces.
    while (read < s.length() && s[read] == ' ') {
      read++;
    }
    if (read == s.length()) break;

    // If write pointer is not at 0, then add a single
    // whitespace to separate words.
    if (write > 0) {
      s[write++] = ' ';
    }

    // Copy the rest of the word.
    while (read < s.length() && s[read] != ' ') {
      s[write++] = s[read++];
    }
  }
  // write pointer points to the clean boundary of string.
  s.resize(write);

  // 2. Reverse the entire string.
  reverse(s, 0, s.length() - 1);

  int start = 0;
  int end = 0;

  // 3. Reverse each word of the string.
  while (end < s.length()) {
    if (s[end] == ' ') {
      reverse(s, start, end - 1);
      start = end + 1;
    }
    end++;
  }
  // Reverse the last word.
  reverse(s, start, end - 1);

  return s;
}

void reverse(string& s, int start, int end) {
  while (start < end) {
    swap(s[start++], s[end--]);
  }
}
