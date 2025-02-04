def max_uncovered_positions(N, ranges):
    positions = []  # List to store positions and tags
    for l, r in ranges:
        positions.append((l, 'start'))
        positions.append((r + 1, 'end'))

    # Sort positions. Openings come before closings. If positions have the same value, openings are processed first.
    positions.sort()

    max_uncovered = 0
    active_ranges = 0
    last_position = None

    for pos, tag in positions:
        if tag == 'start':
            active_ranges += 1
            if active_ranges == 1:
                last_position = pos
        else:
            active_ranges -= 1
            if active_ranges == 0:
                max_uncovered = max(max_uncovered, pos - last_position)

    return max_uncovered

# Read input
N, M, K = map(int, input().split())
ranges = []
for _ in range(M):
    l, r = map(int, input().split())
    ranges.append((l, r))

result = max_uncovered_positions(N, ranges)
print("Maximum Uncovered Positions:", result)

