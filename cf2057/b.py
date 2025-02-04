t = int(input())
for _ in range(t):
	n, k = map(int, input().split())
	a = [int(i) for i in input().split()]
	l = {};
	q = []
	for i in a:
		l[i] = l.get(i, 0)+1;
	for i in l:
		q.append(l[i]);
	q = sorted(q);
	ans = len(l)
	for i in q:
		if (k-i >= 0):
			k-= i;
			ans-=1;
	print(max(1, ans))
