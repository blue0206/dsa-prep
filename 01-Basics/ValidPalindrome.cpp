/*
 * Problem: Valid Palindrome (LeetCode #125)
 * Link: https://leetcode.com/problems/valid-palindrome/description/
 *
 * Note: Only recursive approach is used as I'm learning basic recursion. More
 * optimized solutions will be implemented later.
 *
 * Approach: Sanitize the input string by making it lowercase and removing
 * all non-alphanumeric characters. Then, recursively check equality of
 * first and last character of string and so on.
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <iostream>
#include <string>

using namespace std;

bool validPalindrome(string &s, int index = 0)
{
    if (index >= s.length() / 2)
        return true;
    if (s[index] != s[s.length() - index - 1])
        return false;
    return validPalindrome(s, index + 1);
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (t--)
    {
        string s;
        getline(cin, s);
        string sanitizedStr = "";
        for (auto i : s)
        {
            // Alternatively, we can also use `isalnum()` to check alphanumeric.
            if (
                (i >= 'a' && i <= 'z') ||
                (i >= 'A' && i <= 'Z') ||
                (i >= '0' && i <= '9'))
            {
                sanitizedStr += tolower(i);
            }
        }
        cout << validPalindrome(sanitizedStr) << endl;
    }

    return 0;
}
