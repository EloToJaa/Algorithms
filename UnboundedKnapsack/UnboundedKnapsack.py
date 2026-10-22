"""Unbounded knapsack with an ascending, one-dimensional DP."""

from collections.abc import Iterable


def unbounded_knapsack(items: Iterable[tuple[int, int]], capacity: int) -> int:
    """Best value at or below capacity; items are reusable (weight > 0, value)."""
    best = [0] * (capacity + 1)
    for weight, value in items:
        for available in range(weight, capacity + 1):
            best[available] = max(best[available], best[available - weight] + value)
    return best[capacity]
