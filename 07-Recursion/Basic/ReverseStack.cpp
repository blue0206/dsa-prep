/*
 * Problem: Reverse Stack
 * Link:
 * https://www.naukri.com/code360/problems/reverse-stack-using-recursion_631875?leftPanelTabValue=SUBMISSION
 *
 * Approach: This problem is solved using a recursive approach. The main idea is
 *           to hold all elements of the stack in the function call stack until
 *           the stack becomes empty. When the stack is empty, we start
 *           inserting elements one by one at the bottom of the stack.
 *
 *           1. The `reverseStack` function recursively pops the top element and
 *              holds it in the call stack until the base case (empty stack) is
 *              reached.
 *           2. Once the stack is empty, the recursion unwinds. In each step,
 *              the held element is inserted at the bottom of the stack using a
 *              helper function, `insertAtBottom`.
 *           3. The `insertAtBottom` function also works recursively. It pops
 *              all elements until the stack is empty, then pushes the new
 *              element, and finally pushes back all the popped elements.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

void reverseStack(stack<int>& st);
void insertAtBottom(stack<int>& st, int element);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    stack<int> st;
    cout << "Input Stack: [ ";
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      st.push(x);

      cout << x << " ";
    }
    cout << "]" << endl;

    reverseStack(st);

    cout << "Reversed Stack: [ ";
    while (!st.empty()) {
      cout << st.top() << " ";
      st.pop();
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

void reverseStack(stack<int>& st) {
  if (st.empty()) {
    return;
  }

  // Hold the top element in the call stack.
  int num = st.top();
  st.pop();

  // Recursively reverse the rest of the stack.
  reverseStack(st);

  // Insert the held element at the bottom of the reversed stack.
  insertAtBottom(st, num);
}

void insertAtBottom(stack<int>& st, int element) {
  // Base case: If the stack is empty, the element can be placed at the bottom.
  if (st.empty()) {
    st.push(element);
    return;
  }

  // Hold the current top element and pop it.
  int num = st.top();
  st.pop();

  // Recurse until the stack is empty.
  insertAtBottom(st, element);

  // Push back the held element as the recursion unwinds.
  st.push(num);
}
