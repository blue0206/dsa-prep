/*
 * Problem: Remove K Digits (LeetCode #402)
 * Link: https://leetcode.com/problems/remove-k-digits/description/
 *
 * Approach: This is a greedy problem that can be solved using a monotonic
 *           stack. The goal is to build the smallest possible number by keeping
 *           the digits in the result as small as possible from left to right.
 *
 *           1.  **Monotonic Stack:** We use a string (`ans`) to build our
 *               result, treating it like a stack. We iterate through each
 *               digit of the input number `num`.
 *           2.  **Greedy Removal:** For each digit `d`, we check the last digit
 *               in our result (`ans.back()`). If `ans.back() > d` and we still
 *               have removals left (`k > 0`), we pop from `ans` and decrement
 *               `k`. This is because removing a larger digit from a more
 *               significant position and replacing it with a smaller one
 *               yields a smaller overall number.
 *           3.  **Append Digit:** After the removal loop, we append the current
 *               digit `d` to `ans`.
 *           4.  **Handle Remaining `k`:** If `k > 0` after the main loop (which
 *               happens with non-decreasing sequences like "12345"), we remove
 *               the remaining digits from the end of `ans`, as these are the
 *               largest digits.
 *           5.  **Format Output:** The resulting string might have leading
 *               zeros, which need to be removed. If the result is empty, we
 *               return "0".
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

string removeKdigits(string num, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    string num;
    cin >> num;

    int k;
    cin >> k;

    cout << "Input Number (num): " << num << endl;
    cout << "k: " << k << endl;

    cout << "Result: " << removeKdigits(num, k) << endl;

    cout << endl;
  }

  return 0;
}

string removeKdigits(string num, int k) {
  string ans = "";
  for (int i = 0; i < num.length(); i++) {
    // While the result string is not empty, its last digit is greater than the
    // current digit, and we still have removals left...
    while (!ans.empty() && ans.back() > num[i] && k > 0) {
      // ...remove the larger last digit.
      ans.pop_back();
      k--;
    }
    ans.push_back(num[i]);
  }

  // If k is still > 0, it means the sequence was non-decreasing (e.g., "123").
  // Remove the largest digits from the end.
  while (k > 0) {
    ans.pop_back();
    k--;
  }

  // Remove leading zeros.
  int index = 0;
  while (index < ans.length() && ans[index] == '0') index++;

  // If the result is empty (e.g., all digits were removed or were all zeros),
  // return "0".
  if (index == ans.length()) return "0";

  return ans.substr(index);
}
