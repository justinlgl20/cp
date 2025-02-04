MOD = 998244353;

def powe(base, exp = MOD-2):
    res = 1
    y = base
    while (exp):
        if (exp&1):
            res = (res*y)%MOD;
        y = (y*y) % MOD;
        exp>>=1;
    return res;

def get_ans(p, q):
    return (p*powe(q))%MOD;

def MODFORME(x):
    return get_ans(x, 1);

n, k = map(int, input().split())
one = 1;
others = 0;
# bottom is n^2, n^k at end

for i in range(k):
    one = MODFORME(one * MODFORME(get_ans((n-1)**2, n*n)+get_ans(1, n*n)) + MODFORME(1-one)*(get_ans(2, n*n)));
    others = MODFORME(others * MODFORME(get_ans((n-1)**2, n*n)+get_ans(1, n*n)) + MODFORME(1-others)*(get_ans(2, n*n)));

print(MODFORME(MODFORME(((n*(n-1)//2)-1)*others)+one))
