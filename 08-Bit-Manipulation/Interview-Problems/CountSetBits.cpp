/*
 * Problem: Count the Number of Set Bits
 *
 * Statement: Given an integer 'n', count the number of set bits (1s) in its
 *            binary representation.
 *
 * Link: https://www.geeksforgeeks.org/problems/set-bits0143/1
 */
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * Approach: This method iterates through the number while it's greater than
 *           zero. In each step, it checks if the least significant bit (LSB)
 *           is a 1 using the bitwise AND operator (`n & 1`). It then
 *           right-shifts the number (`n >>= 1`) to process the next bit.
 *
 * Time Complexity: O(log N) - The loop runs as many times as there are bits.
 * Space Complexity: O(1)
 */
int bruteForceApproach(int n);

/**
 * Approach: This is Brian Kernighan's algorithm. The expression `n & (n - 1)`
 *           has the effect of turning off the rightmost set bit of `n`. The
 *           loop continues until `n` becomes 0. The number of iterations is
 *           equal to the number of set bits.
 *
 * Time Complexity: O(K), where K is the number of set bits.
 * Space Complexity: O(1)
 */
int brianKernighanApproach(int n);

/**
 * Approach: This uses a built-in function provided by GCC and Clang compilers.
 *           It is highly optimized and often maps directly to a hardware
 *           instruction (like `POPCNT`), making it the fastest method.
 *
 * Time Complexity: O(1) (practically)
 * Space Complexity: O(1)
 */
int gccApproach(int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    cout << "n: " << n << endl;

    cout << "Set Bits (Brute-Force Approach): " << bruteForceApproach(n)
         << endl;
    cout << "Set Bits (Brian Kernighan Approach): " << brianKernighanApproach(n)
         << endl;
    cout << "Set Bits (GCC __builtin_popcount() approach): " << gccApproach(n)
         << endl;

    cout << endl;
  }

  return 0;
}

int bruteForceApproach(int n) {
  int count = 0;
  while (n > 0) {
    count += (n & 1);
    n >>= 1;
  }

  return count;
}

int brianKernighanApproach(int n) {
  int count = 0;
  while (n > 0) {
    n &= (n - 1);
    count++;
  }

  return count;
}

int gccApproach(int n) { return __builtin_popcount(n); }
