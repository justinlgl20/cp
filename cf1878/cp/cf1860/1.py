t = int(input())
for i in range(t):
    s = input();
    b = len(s);
    if s == "()":
        print("NO")
    elif "))" in s or "((" in s:
        print("YES\n"+"()"*b)
    else:
        print("YES\n"+"("*b+")"*b)
