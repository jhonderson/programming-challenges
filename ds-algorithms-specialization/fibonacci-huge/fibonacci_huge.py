# Uses python3
import sys


def get_fibonacci_huge_naive(n, m):
    if n <= 1:
        return n

    previous = 0
    current  = 1

    for _ in range(n - 1):
        previous, current = current, previous + current

    return current % m


def is_a_period(numbers):
    size = len(numbers)
    half = int(size / 2)
    if size > 0 and size % 2 == 0:
        for i in range(half):
            if numbers[i] != numbers[i + half]:
                return False
    else:
        return False
    return True


def find_period(m):
    previous = 0
    current  = 1

    period = [previous % m, current % m]

    while True:
        previous, current = current, (previous + current) % m
        period.append(current)
        if is_a_period(period):
            period = period[int(len(period)/2):]
            break
    return period


def get_fibonacci_huge_fast(n, m):
    if n <= 1:
        return n

    period = find_period(m)
    size = len(period)

    return period[n % size]


if __name__ == '__main__':
    input = sys.stdin.read()
    n, m = map(int, input.split())
    print(get_fibonacci_huge_fast(n, m))
