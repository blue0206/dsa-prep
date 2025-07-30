# Quick Sort

Quick Sort is a highly efficient, in-place, comparison-based sorting algorithm. It follows the **Divide and Conquer** paradigm.

---

## Core Concept

The algorithm works by selecting an element from the array as a **pivot** and partitioning the other elements into two sub-arrays according to whether they are less than or greater than the pivot. The sub-arrays are then sorted recursively.

The three main steps are:

1.  **Divide:** Pick an element (the pivot) and rearrange the array so that all elements smaller than the pivot are placed before it, and all elements greater are placed after it. After this partitioning, the pivot is in its final, sorted position. This process is called **partitioning**.
2.  **Conquer:** Recursively apply the Quick Sort algorithm to the sub-array of elements with smaller values and the sub-array of elements with greater values.
3.  **Combine:** No work is needed to combine the sub-arrays, as the sorting is done in-place.

---

## The Partition Function

The `partition()` function is the heart of Quick Sort. Its goal is to place a chosen pivot element into its correct, final sorted position, returning that position's index.

### Lomuto Partition Scheme

It typically uses the **last element** as the pivot. Can also be implemented with **first element**.

**Logic:**
1.  Select the last element (`arr[high]`) as the pivot.
2.  Initialize a "boundary" index `partitionIndex` at one position before the start (`low - 1`).
3.  Iterate with a pointer `i` from `low` to `high - 1`.
4.  If the element `arr[i]` is less than or equal to the pivot, increment the boundary `partitionIndex` and swap `arr[partitionIndex]` with `arr[i]`. This expands the "smaller-than-pivot" section.
5.  After the loop finishes, swap the pivot element (`arr[high]`) with the element at `arr[partitionIndex + 1]`. The pivot is now in its final place.
6.  Return the pivot's new index, `partitionIndex + 1`.

*Note: The implementation `partitionWithLastElement` in the C++ code uses this approach.*

### Hoare Partition Scheme

It's slightly more efficient than Lomuto because it does fewer swaps on average.
Can be used on both first and last element as pivot.

**Logic:**
1.  Select a pivot (often the first element).
2.  Initialize two pointers, `low` at the start and `high` at the end of the partition.
3.  Move `low` forward until you find an element greater than or equal to the pivot.
4.  Move `high` backward until you find an element less than or equal to the pivot.
5.  If `low` is still less than `high`, swap `arr[low]` and `arr[high]`.
6.  Repeat steps 3-5 until `low` and `high` pointers cross.
7.  The point where they cross is the partition point. Unlike Lomuto, the pivot is not necessarily in its final sorted position, but the array is correctly partitioned around that point.

*Note: The implementation `partitionWithFirstElement` in the C++ code uses this approach.*

---

## Pivot Selection Strategies

The choice of pivot is critical to the algorithm's performance. A poor pivot choice can lead to the worst-case time complexity.

| Strategy                  | Advantages                                                                                                                                                                                         | Disadvantages                                                                                                    | Worst-Case Trigger                                          |
| :------------------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :--------------------------------------------------------------------------------------------------------------- | :---------------------------------------------------------- |
| **First or Last Element** | Simplest to implement.                                                                                                                                                                             | **Unreliable.** Leads to the worst-case O(n²) performance if the input array is already sorted or nearly sorted. | Sorted or Reverse-Sorted Data                               |
| **Random Element**        | **Robust.** By randomly selecting a pivot, the probability of consistently picking a bad pivot becomes astronomically low. This effectively guarantees average-case performance.                   | Incurs minor overhead from the random number generator.                                                          | Extremely unlikely in practice.                             |
| **Median-of-Three**       | **Best Overall.** Deterministically avoids the worst-case for sorted data by picking the median of the first, middle, and last elements. Often leads to more balanced partitions than pure random. | <center>-</center>                                                                                               | Can still be triggered by specific, complex input patterns. |

---

## Complexity Analysis

| Complexity | Best Case    | Average Case | Worst Case |
| :--------- | :----------- | :----------- | :--------- |
| **Time**   | `O(n log n)` | `O(n log n)` | `O(n²)`    |
| **Space**  | `O(log n)`   | `O(log n)`   | `O(n)`     |

### Time Complexity Explained

-   **Best/Average Case `O(n log n)`:** Occurs when the pivot selection consistently creates reasonably balanced partitions. The problem is divided in half at each step, leading to a recursion depth of `log n`. Since each level of recursion involves roughly `n` comparisons in the `partition` step, the total work is `n * log n`.
-   **Worst Case `O(n²)`:** Occurs when the pivot selection consistently produces extremely unbalanced partitions (e.g., one sub-array of size `n-1` and one of size 0). This happens with the First/Last element pivot strategy on sorted data. The recursion depth becomes `n`, and the total work becomes a sum of `n + (n-1) + (n-2) + ...`, which is `O(n²)`.

### Space Complexity Explained

-   The space complexity is determined by the **depth of the recursion call stack**.
-   **Best/Average Case `O(log n)`:** With balanced partitions, the maximum depth of recursive calls is `log n`.
-   **Worst Case `O(n)`:** With unbalanced partitions, the recursion can go `n` levels deep, leading to a call stack of size `O(n)`. This can be a problem for very large arrays.

---

## Key Takeaways & When to Use

-   Quick Sort is an **in-place** algorithm, meaning it requires minimal extra memory (besides the recursive stack).
-   It is generally **faster in practice** than other `O(n log n)` algorithms like Merge Sort or Heap Sort due to its smaller constant factor and cache-friendly nature.
-   The choice of a **good pivot strategy (Random or Median-of-Three) is essential** to avoid the `O(n²)` worst-case scenario.
-   Quick Sort is **not a stable sort**, meaning that the relative order of equal elements is not guaranteed to be preserved.

Use Quick Sort when you need a fast, in-place sort and the potential for instability is not a concern. It is the default sorting algorithm in the standard libraries of many programming languages.
