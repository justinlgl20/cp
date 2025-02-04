s = [i for i in input().strip()]
r_loc = s.index("R")
s_loc = s.index("M")
if (r_loc < s_loc):
    print("Yes")
else:
    print("No")
