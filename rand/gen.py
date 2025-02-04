import random
from datetime import datetime
random.seed(datetime.now().timestamp())

n = random.randint(2, 10)
k = random.randint(2, 10)
print(n, k)
for i in range(1, n):
    print(random.randint(1, i))
for _ in range(k):
    print(random.randint(1, n), random.randint(1, n))
