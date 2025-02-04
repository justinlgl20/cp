import sys
sys.stdin = open("holesin.txt", "r")
sys.stdout = open("holesout.txt", "w")

L, W = map(int, input().split())
A, B = map(int, input().split())
print((L//A)*(W//B))
