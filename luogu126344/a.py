a, b, h, k = map(int, input().split())
a+=k;
b+=k;
h+=k;
ans = a*b % 988444333
ans = ans*h % 988444333
print(ans);
