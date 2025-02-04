def solve():
	l, r = map(int, input().split());
	n = r.bit_length()-1;
	qw = [0 for i in range(n+4)];
	for i in reversed(range(0, n+1)):
		if (l&(1<<i) and r&(1<<i)):
			#shouldn't have it here
			qw[i] = 0;
		elif (l&(1<<i) or r&(1<<i)):
			# can have either here and its fine
			qw[i] = 2;
		else:
			qw[i] = 1;
	a = 0;
	w = 0;
	low = 0;
	high = 0;
	for i in reversed(range(0, n+1)):
		if (w and l&(1<<i) and r&(1<<i)):
			a += (1<<i);	
		else:
			if (qw[i] == 2):
				low += (0<<i);
				high += (1<<i);
			else:
				low += (1<<i);
				high += (0<<i);

	"""
	a, b, c = 0, 0, 0;
	for i in reversed(range(0, n+1)):
		qw = [a, b, c]
		a, b, c = sorted(qw)
		# a is now the smallest
		if (a+(1<<i) <= r):
			a += (1<<i);
	# now we can add one one in each col\
	#$print("DBG", a, b, c);
	#print(64|((1<<4)-1));
	for i in reversed(range(0, n+1)):
		qw = [a, b, c]
		a, b, c = sorted(qw)
		if (a&(1<<i)):
			a, c = c, a
		if (b&(1<<i)):
			c, b = b, c;
		# c is alreay a 1 here
		# we can optionally add a 1 to a and b
		# this is the max a if we dont set it
		qw = [a, b]
		a, b = sorted(qw);
		idk = a|((1<<i)-1)
		s = 0;
		if (idk < l):
			a += (1<<i);
			s = 1;
		idk = b|((1<<i)-1);
		if (idk < l):
			b += (1<<i);
			s = 1
		if (s == 0):
			if (a+(1<<i) <= r): a+= (1<<i);
			elif (b+(1<<i) <= r): b+= (1<<i);
	print(a, b, c)#, ((a^b)+(b^c)+(a^c)));
	"""
t = int(input())
for _ in range(t):
	solve();
