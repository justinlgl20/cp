n = int(input())

digits = 0
numbers = 1
prev = 1
for i in range(2, 10000):
    prev = numbers
    numbers += 9*(10**(i//2-1))
    digits += 1
    if (numbers >= n):
        break

# prev is number of stuff before reaching that amount of digits
n -= prev
# we want the nth digits digit number
spots = [-1 for i in range(digits)]
no = digits//2+digits%2
#print("NO:",no, n)
combs = 10**(no-1)
for i in range(no):
    #print(i, combs)
    #starts at 0
    spots[i] = (n//combs)-(n%combs==0)+(i==0);
    spots[digits-i-1] = spots[i]
    n %= combs
    combs //=10
#print(n, combs, spots)
print("".join([str(i) for i in spots]))
