N, X = map(int, input().split())
K = [int(i) for i in input().split()]
print(sum([i for i in K if i <= X]))
