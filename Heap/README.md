# Binary min and max heaps

Keep the smallest or largest value accessible while supporting insertion and root removal.

## My solution

Use a one-based binary heap. Insertions sift upward; removal or root replacement sifts downward. MinHeap and MaxHeap reverse the comparison direction.

## Complexity

O(log n) insert/remove/replace, O(1) top, O(n log n) construction by repeated insertion, and O(n) space.

## Usage and assumptions

`MinHeap(values)` and `MaxHeap(values)` provide `insert`, `top`, `remove`, `replace`, `size`, and `empty`. Python remove/replace return the old root; C++ methods are void. Root operations require a nonempty heap; Python raises IndexError and C++ out_of_range otherwise. C++ heapify replaces all existing contents.

```python
from Heap.Heap import MinHeap, MaxHeap

heap = MinHeap([3, 1, 2])
assert [heap.remove() for _ in range(3)] == [1, 2, 3]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ heapify now clears existing contents, and empty root operations raise instead of accessing invalid memory.

## Tests

[`test_Heap.py`](test_Heap.py) checks the Python implementation; [`test_Heap.cpp`](test_Heap.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Heap -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
