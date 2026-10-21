# Monotone maximum queue

Maintain the maximum of a FIFO sequence, useful for sliding windows.

## My solution

Store decreasing candidate values with insertion indices. A new value removes no-larger candidates at the back; a pop expires the oldest logical input and removes it if still a candidate.

## Complexity

O(1) amortized push/pop/max and O(window_size) space.

## Usage and assumptions

`MonoQueue` provides `push(value)`, `pop()`, and `max()`. Only pop when the logical queue is nonempty. Empty maximum is `-math.inf` in Python and `numeric_limits<T>::lowest()` in C++. C++ insertion/removal counters are int.

```python
from MonoQueue.MonoQueue import MonoQueue

queue = MonoQueue()
queue.push(2)
queue.push(5)
queue.pop()
assert queue.max() == 5
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

The original C++ implementation was retained and tested against a plain FIFO queue.

## LeetCode problems

- [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- [1696. Jump Game VI](https://leetcode.com/problems/jump-game-vi/)
- [1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/) — max and min queues
- [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)

## Tests

[`test_MonoQueue.py`](test_MonoQueue.py) checks the Python implementation; [`test_MonoQueue.cpp`](test_MonoQueue.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s MonoQueue -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
