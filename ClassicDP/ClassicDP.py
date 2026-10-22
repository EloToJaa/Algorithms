"""Classic 1D/2D DPs: house robber, coin change, grid paths, and word break."""

from collections.abc import Iterable, Sequence


def rob(nums: Sequence[int]) -> int:
    """Max sum of non-adjacent nonnegative values in a line."""
    take, skip = 0, 0  # best ending with / without the previous house
    for value in nums:
        take, skip = skip + value, max(take, skip)
    return max(take, skip)


def rob_circular(nums: Sequence[int]) -> int:
    """House robber where the first and last houses are adjacent."""
    if len(nums) == 1:
        return nums[0]
    return max(rob(nums[1:]), rob(nums[:-1]))


def coin_change(coins: Sequence[int], amount: int) -> int:
    """Fewest positive coins (unlimited supply) summing to amount, or -1."""
    unreachable = amount + 1
    best = [0] + [unreachable] * amount
    for total in range(1, amount + 1):
        for coin in coins:
            if coin <= total:
                best[total] = min(best[total], best[total - coin] + 1)
    return best[amount] if best[amount] != unreachable else -1


def coin_change_ways(coins: Sequence[int], amount: int) -> int:
    """Number of coin multisets (order ignored) summing to amount."""
    ways = [1] + [0] * amount
    # Coins outer: each combination is built in coin order, so it is counted once.
    for coin in coins:
        for total in range(coin, amount + 1):
            ways[total] += ways[total - coin]
    return ways[amount]


def coin_change_ordered_ways(coins: Sequence[int], amount: int) -> int:
    """Number of coin sequences (order matters) summing to amount (LeetCode 377)."""
    ways = [1] + [0] * amount
    # Totals outer: any coin may be the last one, so every ordering is counted.
    for total in range(1, amount + 1):
        ways[total] = sum(ways[total - coin] for coin in coins if coin <= total)
    return ways[amount]


def unique_paths_with_obstacles(grid: Sequence[Sequence[int]]) -> int:
    """Right/down paths from top-left to bottom-right avoiding cells equal to 1."""
    if not grid or not grid[0]:
        return 0
    paths = [0] * len(grid[0])
    paths[0] = 1
    for row in grid:
        for j, cell in enumerate(row):
            if cell == 1:
                paths[j] = 0
            elif j > 0:
                paths[j] += paths[j - 1]  # from above (old value) + from left
    return paths[-1]


def min_path_sum(grid: Sequence[Sequence[int]]) -> int:
    """Minimum right/down path sum from top-left to bottom-right of a nonempty grid."""
    inf = float("inf")
    best: list[float] = [inf] * len(grid[0])
    best[0] = 0
    for row in grid:
        for j, cell in enumerate(row):
            left = best[j - 1] if j > 0 else inf
            best[j] = min(best[j], left) + cell
    return int(best[-1])


def word_break(text: str, words: Iterable[str]) -> bool:
    """Whether text splits into a sequence of (reusable) dictionary words."""
    dictionary = set(words)
    lengths = {len(word) for word in dictionary}
    # ok[i] tells whether text[:i] can be segmented.
    ok = [True] + [False] * len(text)
    for i in range(1, len(text) + 1):
        ok[i] = any(
            size <= i and ok[i - size] and text[i - size : i] in dictionary
            for size in lengths
        )
    return ok[len(text)]
