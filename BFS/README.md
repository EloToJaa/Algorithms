# Breadth-first search

Visit reachable graph vertices in increasing distance (number of edges) from a start vertex.

## My solution

A FIFO queue holds discovered vertices. Mark each vertex when it enters the queue so cycles and duplicate edges cannot enqueue it again.

## Complexity

O(V + E) time and O(V) auxiliary space for the reachable subgraph.

## Usage and assumptions

`bfs(graph, start)` returns visitation order. `graph[v]` contains neighboring integer vertices. C++ uses global `V`, `Vis`, and `bfs(v)`; reset `Vis` before an independent traversal.

```python
from BFS.BFS import bfs

bfs([[1, 2], [3], [3], []], 0) == [0, 1, 2, 3]
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ now marks vertices on enqueue instead of dequeue, avoiding redundant queue entries.

## Tests

[`test_BFS.py`](test_BFS.py) checks the Python implementation; [`test_BFS.cpp`](test_BFS.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s BFS -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
