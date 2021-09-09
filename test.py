import sys
import time
import re

def escape_ansi(line):
    ansi_escape =re.compile(r'(\x9B|\x1B\[)[0-?]*[ -\/]*[@-~]')
    return ansi_escape.sub('', line)

def get_time_of_message(line):
	num = ""
	words = line.split()
	word = escape_ansi(words[0])
	for c in word:
		if c.isdigit():
			num = num + c
	return num

def get_philo(line):
	num = ""
	for word in line.split(' ', 1)[1]:
		for c in word:
			if c.isdigit():
				num = num + c
	return num

start = time.time()
stdin_list = []
countdown = 30
death_time = 710
eat = " is eating"
death = "died"

if sys.argv[1]:
	countdown = int(sys.argv[1])
if sys.argv[2]:
	death_time = int(sys.argv[2])

for line in sys.stdin:
	if time.time() >= start + countdown:
		break
	stdin_list.append(line)

if not death in stdin_list[-2]:
	print("no death")
	exit(0)
t = get_time_of_message(stdin_list[-2])
print(t)
print(get_philo(stdin_list[-2]))
for line in stdin_list:
	if 