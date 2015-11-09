__author__ = 'piotr'


import matplotlib.pyplot as plt
import matplotlib.pylab as pl


plt.ylabel('Event Value')
plt.xlabel('Algorithm Version')


algorithms = [1, 2, 3, 4, 5, 6, 7, 8, 9]
event1 = {"sn": "PAPI_STL_ICY", "title": "PAPI_STL_ICY: Cycles with no instruction issue", "values": []}
event2 = {"sn": "PAPI_L2_DCM", "title": "PAPI_L2_DCM: L2 data cache misses", "values": []}
event3 = {"sn": "PAPI_L2_ICH", "title": "PAPI_L2_ICH: L2 instruction cache hits", "values": []}
event4 = {"sn": "PAPI_TOT_INS", "title": "PAPI_TOT_INS: Instructions completed", "values": []}

for algo in algorithms:
    with open("results/multpile_events/algo" + str(algo) + ".txt") as f:
        (_, e1) = f.next().strip().split(':')
        (_, e2) = f.next().strip().split(':')
        (_, e3) = f.next().strip().split(':')
        (_, e4) = f.next().strip().split(':')
        event1["values"].append(int(e1.strip()))
        event2["values"].append(int(e2.strip()))
        event3["values"].append(int(e3.strip()))
        event4["values"].append(int(e4.strip()))

events = [event1, event2, event3, event4]

for event in events:
	plt.bar(algorithms, event["values"], 0.3)
	plt.title(event["title"])
	pl.savefig('plots/multiple_events/' + event["sn"])