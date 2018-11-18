import sys, time, subprocess, random
from fractions import gcd

total = 100
success = 0
max = 100000

for i in range(total):
	a = random.randrange(1, max)
	b = random.randrange(1, max)
	proc = subprocess.Popen(['./stress', str(a), 'g', str(b)], stdout=subprocess.PIPE)
	c = int(proc.stdout.readline())
	if c == gcd(a, b):
		success = success + 1
	else:
		print(str(a) + "/" + str(b))

print(str(success) + "/" + str(total));