# Disjoint-set union

Maintain a partition into connected components and efficiently merge components.

## My solution

Follow parent pointers with path compression and attach the smaller component to the larger one. Ignore a union when both vertices already share a representative.

## Complexity

O(alpha(n)) amortized time per operation and O(n) space.

## Usage and assumptions

`DisjointSet(n)` provides `find(v)` and `union(a, b)`; union returns whether a merge happened. `size[find(v)]` is the component size. C++ uses vertices 1..n, `Init(n)`, `Find(v)`, `Union(a, b)`, and `Ile`.

```python
from FindAndUnion.FindAndUnion import DisjointSet

sets = DisjointSet(3)
sets.union(0, 1)
assert sets.find(0) == sets.find(1)
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

C++ repeated unions no longer double a component size.

## Tests

[`test_FindAndUnion.py`](test_FindAndUnion.py) checks the Python implementation; [`test_FindAndUnion.cpp`](test_FindAndUnion.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s FindAndUnion -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
