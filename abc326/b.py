import sys
N = input()
for i in range(max(int(N), 100), 1000):
    if int(str(i)[0] )*int(str(i)[1]) == int(str(i)[2]):
        print(i);
        sys.exit();
