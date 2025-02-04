def trip(arr, target):
    d = dict()
    n = len(arr)
    for i in arr:
        d[i] = 1

    i = 0
    j = n - 1
    while i<j:
        s = arr[i] + arr[j] 
        diff = target - s
        if arr[i] != diff and arr[j] != diff and diff in d:
            return [arr[i], arr[j], diff]
        else:
            if s > target:
                j -= 1
            elif s == target:
                if arr[i+1] + arr[j] < target:
                    i+=1
                else:
                    j-=1
            else:
                i += 1

    return [None]

n, x = map(int, input().split())
a = [int(i) for i in input().split()]

print(trip(a, x))
