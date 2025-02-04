def solve(N, jobs):
    jobs = sorted(jobs, key=lambda x: x[0])
    ans = 0;
    time = 0;

    for s, t in jobs:
        fin = s+t;
        if (s >= time):
            ans+=1;
            time = time+t;
    return ans

t = int(input())
for _ in range(t):
    n = int(input())
    l = []
    for i in range(n):
        s, t = map(int, input().split())
        l.append([s, t])
    print(solve(n, l));
