import sys, time, subprocess, random
from fractions import Fraction

total = 100
success = 0
max = 100000

for i in range(total):
	a = random.randrange(-max, max)
	b = random.randrange(1, max)
	p = random.randrange(-max, max)
	q = random.randrange(1, max)
	proc = subprocess.Popen(['./stress3', str(a), str(b), '/', str(p), str(q)], stdout=subprocess.PIPE)
	c = Fraction(proc.stdout.readline())
	if c == Fraction(a, b) / Fraction(p, q):
		success = success + 1
	else:
		print(c)
		print(str(a) + "/" + str(b) + " and " + str(p) + "/" + str(q))

print(str(success) + "/" + str(total));