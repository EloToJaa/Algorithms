# Algorithms

My library of competitive-programming algorithms, with C++ implementations and Python ports based on the same techniques.

Each algorithm has its own directory containing:

- `README.md`: algorithm, solution approach, complexity, usage, and C++ review notes.
- `<Algorithm>.cpp`: C++ implementation.
- `<Algorithm>.py`: Python implementation.
- `test_<Algorithm>.py` and `test_<Algorithm>.cpp`: reference checks and regression tests.

## Algorithms

| Directory | Algorithm |
| --- | --- |
| [BellmanFord](BellmanFord/README.md) | Bellman–Ford shortest paths and negative cycles |
| [BFS](BFS/README.md) | Breadth-first search |
| [BigNumbers](BigNumbers/README.md) | Unsigned big integers |
| [BinSearch](BinSearch/README.md) | Binary search on a predicate |
| [Bridges](Bridges/README.md) | Bridges and articulation points |
| [DFS](DFS/README.md) | Depth-first search |
| [Dijkstra](Dijkstra/README.md) | Dijkstra's shortest paths |
| [FindAndUnion](FindAndUnion/README.md) | Disjoint-set union |
| [GCD](GCD/README.md) | GCD and extended Euclid |
| [Hashing](Hashing/README.md) | Double polynomial hashing |
| [Heap](Heap/README.md) | Binary min and max heaps |
| [KMP](KMP/README.md) | Knuth-Morris-Pratt prefix function |
| [KMR](KMR/README.md) | Karp-Miller-Rosenberg ranks and suffix arrays |
| [Knapsack](Knapsack/README.md) | Zero-one knapsack |
| [Kruskal](Kruskal/README.md) | Kruskal's minimum spanning forest |
| [LCA](LCA/README.md) | Lowest common ancestor |
| [LIS](LIS/README.md) | Longest increasing subsequence |
| [Manacher](Manacher/README.md) | Manacher's palindrome radii |
| [MergeSort](MergeSort/README.md) | Merge sort |
| [Mo](Mo/README.md) | Mo's algorithm for distinct counts |
| [Modulo](Modulo/README.md) | Modular arithmetic |
| [MonoQueue](MonoQueue/README.md) | Monotone maximum queue |
| [QuickSort](QuickSort/README.md) | Quicksort |
| [SCC](SCC/README.md) | Strongly connected components (Kosaraju) |
| [Sieve](Sieve/README.md) | Linear sieve and smallest prime factors |
| [SparseTable](SparseTable/README.md) | Static range minimum sparse table |
| [TopologicalSort](TopologicalSort/README.md) | Topological sort with cycle detection |
| [TreePointSegment](TreePointSegment/README.md) | Point assignment / range maximum |
| [TreeSegmentPoint](TreeSegmentPoint/README.md) | Range addition / point lookup |
| [TreeSegmentSegment](TreeSegmentSegment/README.md) | Range addition / range sum |
| [Trie](Trie/README.md) | Trie / prefix tree |
| [ZeroOneBFS](ZeroOneBFS/README.md) | 0–1 BFS shortest paths |

## Running tests

Python 3.10+ and the standard library are sufficient; no third-party packages are required. Run from the repository root:

```sh
python3 run_tests.py
python3 run_tests.py --cpp
```

The second command also requires `g++` with C++17 support. It compiles all C++ implementations independently and runs all C++ tests with UndefinedBehaviorSanitizer, placing build products in a temporary directory. Python tests use deterministic randomized inputs and simple reference solutions where appropriate.

With Nix, obtain the tools without a global installation:

```sh
nix shell nixpkgs#python3 nixpkgs#gcc --command python3 run_tests.py --cpp
```

To run only one Python suite:

```sh
python3 -m unittest discover -s QuickSort -t . -p 'test_*.py'
```

## Conventions

Python graph vertices and array positions are zero-based. Range queries are inclusive for Mo and segment trees; string hash and KMR ranges are half-open. Each README explains the equivalent C++ indexing and initialization. The newer TopologicalSort, SCC, ZeroOneBFS, BellmanFord, and Bridges snippets also use zero-based C++ vertices and dynamic storage. SparseTable uses zero-based inclusive bounds in both languages. Algorithms expect inputs satisfying their documented assumptions.

C++ files retain their original competitive-programming interfaces and fixed-capacity arrays where applicable. Files with a demo/input `main` can be compiled as programs; other files are reusable snippets. C++ regressions include each snippet in its own translation unit to avoid collisions between global names.

Correctness fixes cover quicksort pivot placement, duplicate union sizes, LCA parent traversal, knapsack input/output, Mo query input and interval movement, substring hashing/comparison, and consistent segment-tree semantics. DFS, LCA, and quicksort avoid unbounded call-stack depth. See individual READMEs for details.
