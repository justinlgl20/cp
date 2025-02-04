S = input()
N = len(S)+"000000"
removed = [0 for i in range(N)]
prev = [i-1 for i in range(N)]
nex = [i+1 for i in range(N)]
first, second, third = 0, 0, 0;
for i in range(N-2):
    if S[i] == "A" and S[i+1] == "B" and S[i+2] == "C":
        first, second, third = i, i+1, i+2
while (S[first] != 
