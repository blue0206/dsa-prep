/*
 * Problem:  Fibonacci Number (LeetCode #509)
 * Link: https://leetcode.com/problems/fibonacci-number/description/
 *
 * Note: Only recursive approach is used as I'm learning basic recursion. More
 * optimized solutions will be implemented later.
 *
 * Approach: Using functional recursion with fibonacci formula (f(n) = f(n-1) + f(n-2))
 * to arrive at the Nth fibonacci number.
 * Time Complexity: O(2^N); Exponential
 * Space Complexity: O(N)
 */

#include <iostream>
using namespace std;

int fib(int n)
{
    if (n <= 1)
        return n;
    return (fib(n - 1) + fib(n - 2));
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        cout << fib(n) << endl;
    }

    return 0;
}
