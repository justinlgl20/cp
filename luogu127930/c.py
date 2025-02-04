from bisect import bisect_right

def solve(n, k, a):
    immovable_count = [0] * n
    current_a = a[:]
    
    while True:
        sorted_a = sorted((value, i) for i, value in enumerate(current_a))
        sorted_values = [x[0] for x in sorted_a]
        
        movable = [True] * n
        new_a = current_a[:]
        
        for i in range(n):
            value, original_index = sorted_a[i]
            rank = n - i - 1  # How many elements are strictly greater than value
            new_rank = n - bisect_right(sorted_values, value + k)
            
            if new_rank != rank:
                movable[original_index] = False
                immovable_count[original_index] += 1
            else:
                new_a[original_index] += k
        
        if all(movable):
            break
        current_a = new_a
    
    # Step 7: Output the result
    print(" ".join(map(str, immovable_count)))

    
n, k = map(int, input().split())
a = [int(i) for i in input().split()]
solve(n, k, a);
