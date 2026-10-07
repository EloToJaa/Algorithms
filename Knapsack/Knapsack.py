"""Zero-one knapsack with a descending, one-dimensional DP."""


def knapsack(items, capacity):
    """Best value at or below capacity; items are (nonnegative weight, value)."""
    best = [0] * (capacity + 1)
    for weight, value in items:
        for available in range(capacity, weight - 1, -1):
            best[available] = max(best[available], best[available - weight] + value)
    return best[capacity]
