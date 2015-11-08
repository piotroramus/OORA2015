__author__ = 'piotr'


import matplotlib.pyplot as plt

algorithms = range(1, 10)
event1 = []
event2 = []
event3 = []
event4 = []

for algo in algorithms:
    with open("results/algo" + str(algo) + ".txt") as f:
        (_, e1) = f.next().strip().split(':')
        (_, e2) = f.next().strip().split(':')
        (_, e3) = f.next().strip().split(':')
        (_, e4) = f.next().strip().split(':')
        event1.append(int(e1.strip()))
        event2.append(int(e2.strip()))
        event3.append(int(e3.strip()))
        event4.append(int(e4.strip()))

events = [event1, event2, event3, event4]

print event1
plt.bar(range(1, 10), event1, 0.35)
 
plt.ylabel('Event Value')
plt.xlabel('Algorithm Version')
plt.legend()
plt.show()