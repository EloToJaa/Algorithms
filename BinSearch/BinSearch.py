"""Binary searches over inclusive integer bounds and monotone predicates."""


def search_first(l, r, check):
    """First true in false...true; return original r + 1 if none."""
    r += 1  # r + 1 stands for "none"
    while l < r:
        mid = (l + r) // 2
        if check(mid):
            r = mid
        else:
            l = mid + 1
    return l


def search_last(l, r, check):
    """Last true in true...false; return original l - 1 if none."""
    l -= 1  # l - 1 stands for "none"
    while l < r:
        mid = (l + r + 1) // 2  # round up, or l = mid can get stuck
        if check(mid):
            l = mid
        else:
            r = mid - 1
    return l
