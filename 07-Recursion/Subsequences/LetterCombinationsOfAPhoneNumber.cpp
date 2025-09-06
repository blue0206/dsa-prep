/*
 * Problem: Letter Combinations of a Phone Number (LeetCode #17)
 * Link:
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * Approach: This problem is a classic backtracking problem. We can think of it
 *           as generating all possible paths in a conceptual tree where each
 *           level corresponds to a digit in the input string, and the branches
 *           at that level are the letters mapped to that digit.
 *
 *           1. A mapping from digits ('2'-'9') to letters is created.
 *           2. A recursive function `generateCombinations` is used. It takes
 *              the current index of the digits string to process.
 *           3. **Base Case:** If the index equals the length of the digits
 *              string, it means we have formed a complete combination. We add
 *              it to our answer and return.
 *           4. **Recursive Step:** For the digit at the current index, we get
 *              its corresponding letters. We then loop through each letter. For
 *              each letter, we append it to our current combination, make a
 *              recursive call for the next index, and then backtrack by
 *              removing the letter.
 *
 * Time Complexity: O(4^N * N), where N is the length of the digits string.
 * Space Complexity: O(N), for the recursion call stack depth.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vs = vector<string>;

vs letterCombinations(string digits);
void generateCombinations(vs& ans, vs& letterMap, string& digits,
                          string& combination, int index);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string digits;
    cin >> digits;

    cout << "Digits: " << digits << endl;

    vs ans = letterCombinations(digits);

    cout << "Letter Combinations: [ ";
    for (auto subset : ans) {
      cout << "[ " << subset << " ] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vs letterCombinations(string digits) {
  if (digits.empty()) {
    return {};
  }

  vs ans;
  vs letterMap = {"",    "",    "abc",  "def", "ghi",
                  "jkl", "mno", "pqrs", "tuv", "wxyz"};
  string combination = "";

  generateCombinations(ans, letterMap, digits, combination, 0);
  return ans;
}

void generateCombinations(vs& ans, vs& letterMap, string& digits,
                          string& combination, int index) {
  // Base Case: If all digits are processed, store combination.
  if (index == digits.length()) {
    ans.emplace_back(combination);
    return;
  }

  // Extract digit from given index.
  int digit = digits[index] - '0';
  for (int i = 0; i < letterMap[digit].length(); i++) {
    // Pick each letter mapped with digit and generate combinations.
    combination.push_back(letterMap[digit][i]);
    generateCombinations(ans, letterMap, digits, combination, index + 1);
    combination.pop_back();  // Backtrack to reset state and use next letter.
  }
}
