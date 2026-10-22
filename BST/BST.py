"""Unbalanced binary search tree of distinct keys with iterative operations."""

from collections.abc import Iterable, Iterator
from typing import Any, Generic, Optional, Protocol, TypeVar


class Comparable(Protocol):
    def __lt__(self, other: Any, /) -> bool: ...


T = TypeVar("T", bound=Comparable)


class Node(Generic[T]):
    def __init__(self, key: T) -> None:
        self.key = key
        self.left: Optional[Node[T]] = None
        self.right: Optional[Node[T]] = None


class BST(Generic[T]):
    def __init__(self, keys: Iterable[T] = ()) -> None:
        self.root: Optional[Node[T]] = None
        self._size = 0
        for key in keys:
            self.insert(key)

    def insert(self, key: T) -> bool:
        """Insert key; return False if it was already present."""
        parent: Optional[Node[T]] = None
        node = self.root
        while node is not None:
            if not (key < node.key or node.key < key):
                return False
            parent = node
            node = node.left if key < node.key else node.right
        self._size += 1
        if parent is None:
            self.root = Node(key)
        elif key < parent.key:
            parent.left = Node(key)
        else:
            parent.right = Node(key)
        return True

    def __contains__(self, key: T) -> bool:
        node = self.root
        while node is not None:
            if key < node.key:
                node = node.left
            elif node.key < key:
                node = node.right
            else:
                return True
        return False

    def remove(self, key: T) -> bool:
        """Remove key; return False if it was absent."""
        parent: Optional[Node[T]] = None
        node = self.root
        while node is not None and (key < node.key or node.key < key):
            parent = node
            node = node.left if key < node.key else node.right
        if node is None:
            return False
        self._size -= 1
        if node.left is not None and node.right is not None:
            # Replace the key with its successor, then unlink the successor.
            parent, successor = node, node.right
            while successor.left is not None:
                parent, successor = successor, successor.left
            node.key = successor.key
            node = successor
        child = node.left if node.left is not None else node.right
        if parent is None:
            self.root = child
        elif parent.left is node:
            parent.left = child
        else:
            parent.right = child
        return True

    def min(self) -> T:
        """Smallest key; requires a nonempty tree."""
        if self.root is None:
            raise ValueError("empty tree")
        node = self.root
        while node.left is not None:
            node = node.left
        return node.key

    def max(self) -> T:
        """Largest key; requires a nonempty tree."""
        if self.root is None:
            raise ValueError("empty tree")
        node = self.root
        while node.right is not None:
            node = node.right
        return node.key

    def lower_bound(self, key: T) -> Optional[T]:
        """Smallest stored key not less than key, or None."""
        best: Optional[T] = None
        node = self.root
        while node is not None:
            if node.key < key:
                node = node.right
            else:
                best = node.key
                node = node.left
        return best

    def __iter__(self) -> Iterator[T]:
        """Keys in increasing order, using an explicit stack."""
        stack: list[Node[T]] = []
        node = self.root
        while stack or node is not None:
            while node is not None:
                stack.append(node)
                node = node.left
            node = stack.pop()
            yield node.key
            node = node.right

    def __len__(self) -> int:
        return self._size
