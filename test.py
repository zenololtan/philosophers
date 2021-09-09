import sys
import time
import re

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

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
philo = get_philo(stdin_list[-2]);
print("count down: " + str(countdown))
print("time to die: " + str(death_time))
print("time of death: " + t)
print("philo number: " + philo)
#print(stdin_list[-2])

last_val = 0
t_between = 0
for line in stdin_list:
	if philo + eat in line or death in line:
		print(bcolors.ENDC + "[" + line.strip('\n') + bcolors.ENDC + "]")
		t_between = int(get_time_of_message(line)) - last_val
		if t_between > death_time + 10:
			print(bcolors.WARNING + "time between eats: " + str(t_between) + bcolors.ENDC)
		else:
			print("time between eats: " + str(t_between))
		last_val = int(get_time_of_message(line))
