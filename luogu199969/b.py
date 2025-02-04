n = int(input())
is_not_prime = [0] * (n + 1)
primes = []
cntp = 0
counter = 0

l = {}
x = 0
for i in range(2, n + 1):
    if is_not_prime[i] == 0:  
        cntp += 1
        primes.append(i)
        l[i] = 1;
    c = 0;
    for j in range(cntp): 
        if i * primes[j] > n:
            break
        is_not_prime[i * primes[j]] = 1 
        if i % primes[j] > 0:  
            break
        c+=1
    l[c] = l.get(c, 0)+1;
    counter += c;
for i in range(20):
    print(i, l.get(i, 0));
print(cntp, counter)
