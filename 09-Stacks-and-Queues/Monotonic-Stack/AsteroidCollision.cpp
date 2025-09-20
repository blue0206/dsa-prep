/*
 * Problem: Asteroid Collision (LeetCode #735)
 * Link: https://leetcode.com/problems/asteroid-collision/description/
 *
 * Approach: This problem can be solved by simulating the collisions using a
 *           stack. The stack will hold the asteroids that have survived so
 *           far. We iterate through the input asteroids and handle them based
 *           on their direction.
 *
 *           1.  **Right-moving Asteroid (> 0):** If an asteroid is moving to
 *               the right, it cannot collide with any previous asteroids in the
 *               stack (as they are to its left). We simply push it onto the
 *               stack.
 *           2.  **Left-moving Asteroid (< 0):** If an asteroid is moving left,
 *               it can collide with right-moving asteroids at the top of the
 *               stack.
 *               -   While the stack is not empty, its top is positive (moving
 *                   right), and the top's size is less than the current
 *                   asteroid's size, the top asteroid is destroyed. Pop it.
 *               -   After the loop, if the stack is empty or its top is
 *                   negative, the current asteroid survives. Push it.
 *               -   If the stack's top is positive and has the same size, both
 *                   are destroyed. Pop the stack's top.
 *               -   If the stack's top is positive and larger, the current
 *                   asteroid is destroyed. Do nothing.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> asteroidCollision(const vector<int>& asteroids);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Asteroids: [ ";
    for (int i : arr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> survivors = asteroidCollision(arr);

    cout << "Surviving Asteroids: [ ";
    for (int i : survivors) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> asteroidCollision(const vector<int>& asteroids) {
  vector<int> ans;
  for (int i = 0; i < asteroids.size(); i++) {
    if (asteroids[i] < 0) {  // A left-moving asteroid is encountered.
      // Destroy all smaller right-moving asteroids.
      while (!ans.empty() && ans.back() > 0 && ans.back() < abs(asteroids[i]))
        ans.pop_back();

      // If no right-moving asteroids are left, the new one survives.
      if (ans.empty() || ans.back() < 0) {
        ans.emplace_back(asteroids[i]);
      } else if (ans.back() == abs(asteroids[i])) {
        // If a same-sized right-moving asteroid is found, both are destroyed.
        ans.pop_back();
      }
      // If ans.back() > abs(asteroids[i]), the new asteroid is destroyed.
      // Do nothing.
    } else {  // A right-moving asteroid is always added.
      ans.emplace_back(asteroids[i]);
    }
  }

  return ans;
}
