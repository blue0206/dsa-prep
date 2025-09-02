/*
 * Problem: Sort Stack
 * Link:
 * https://www.naukri.com/code360/problems/sort-a-stack_985275?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem is solved using a recursive approach that mimics the
 *           insertion sort algorithm. The core idea is to hold all elements in
 *           the function call stack, and then one by one, insert them back into
 *           the stack in a sorted order.
 *
 *           1. The `sortStack` function recursively pops all elements from the
 *              stack. When the stack is empty, the recursion starts to unwind.
 *           2. In each unwinding step of `sortStack`, it calls a helper
 *              function, `insertAtCorrectPos`, to place the popped element
 *              back into the now-sorted smaller stack.
 *           3. The `insertAtCorrectPos` function inserts an element into a
 *              sorted stack while maintaining descending order (largest on
 *              top). If the stack is empty or the new element is larger than
 *              the top element, it's pushed directly. Otherwise, the top
 *              element is popped, the function calls itself recursively to
 *              insert the new element, and then the popped element is pushed
 *              back on top.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

void sortStack(stack<int>& st);
void insertAtCorrectPos(stack<int>& st, int element);

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

    sortStack(st);

    cout << "Sorted Stack: [ ";
    while (!st.empty()) {
      cout << st.top() << " ";
      st.pop();
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

void sortStack(stack<int>& st) {
  if (st.empty()) {
    return;
  }

  // Store the top element
  // and pop from stack.
  int element = st.top();
  st.pop();

  // Sort the rest of the stack.
  sortStack(st);

  // Insert the stored element at its correct
  // position in sorted stack.
  insertAtCorrectPos(st, element);
}

void insertAtCorrectPos(stack<int>& st, int element) {
  // Base case for insertion: If the stack is empty or the element to insert
  // is greater than the top element, push it. This ensures the stack
  // remains sorted in descending order (largest element at the top).
  if (st.empty() || element > st.top()) {
    st.push(element);
    return;
  }

  // If the top element is larger than the element to be inserted, pop it,
  // hold it in the call stack, and recurse.
  int num = st.top();
  st.pop();

  // Recurse to find the correct position for the element.
  insertAtCorrectPos(st, element);

  // Push back the stored num as the element has been placed at its correct
  // spot.
  st.push(num);
}
