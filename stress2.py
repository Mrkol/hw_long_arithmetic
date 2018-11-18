import sys, time, subprocess, random
from fractions import Fraction
from decimal import *

total = 1
success = 0
max = 1000

for i in range(total):
	a = random.randrange(-max, max)
	b = random.randrange(1, max)
	prec = random.randrange(0, 100);
	proc = subprocess.Popen(['./stress2', str(a), str(b), str(prec)], stdout=subprocess.PIPE)
	c = str(proc.stdout.readline())
	if (abs(float(c) - float(a)/float(b)) < 10**(-prec + 1)):
		success = success + 1
	else:
		print(str(a) + "/" + str(b))
		print("Expected:" + str(float(a)/float(b)))
		print("Got:" + c)

print(str(success) + "/" + str(total));
