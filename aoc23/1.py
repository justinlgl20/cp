l = [i.strip() for i in open("in.txt", "r").readlines()]
nums = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine", '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
d = {
        "one":1, "two":2, "three":3, "four":4, "five":5, "six":6, "seven":7, "eight":8, "nine":9, '0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9
        }
vals = []
for i in l:
    g = min([(i.find(j), j) for j in nums if i.find(j) != -1])
    k = max([(len(i) - 1 - i[::-1].find(j[::-1]), j) for j in nums if i[::-1].find(j[::-1]) != -1])
    vals.append(d[g[1]]*10+d[k[1]]);
print(sum(vals))
