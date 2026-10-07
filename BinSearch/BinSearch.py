"""Binary searches over inclusive integer bounds and monotone predicates."""


def search_first(left, right, check):
    """First true in false...true; return original right + 1 if none."""
    answer = right + 1
    while left <= right:
        mid = left + (right - left) // 2
        if check(mid):
            answer = mid
            right = mid - 1
        else:
            left = mid + 1
    return answer


def search_last(left, right, check):
    """Last true in true...false; return original left - 1 if none."""
    answer = left - 1
    while left <= right:
        mid = left + (right - left) // 2
        if check(mid):
            answer = mid
            left = mid + 1
        else:
            right = mid - 1
    return answer
