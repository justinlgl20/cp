t = int(input())
for i in range(t):
    m, k, a1, ak = [int(i) for i in input().split()]
    l = m
    m -= k*ak;
    m -= a1;
    if (m <= 0): 
        print(0)
    else:
        m = l
        used_ks = k*ak;
        used_ones = a1;
        m -= used_ks + used_ones;
        bad_ks = m // k;
        bad_ones = m%k;
        if (used_ones+bad_ones >= k and bad_ones >= 1):
            q = k
            q -= bad_ones;
            bad_ones = 0;
            used_ones = used_ones - q;
            bad_ks+=1
            

        print(bad_ks+bad_ones)
