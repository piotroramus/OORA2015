__author__ = 'piotr'


import matplotlib.pyplot as plt
import matplotlib.pylab as pl


plt.ylabel('Event Value')
plt.xlabel('Algorithm Version')


algorithms = [1, 2, 3, 4, 5, 6, 7, 8, 9]
event1 = {"n": 0, "sn": "PAPI_STL_ICY", "title": "PAPI_STL_ICY: Cycles with no instruction issue", "values": []}
event2 = {"n": 1, "sn": "PAPI_L2_DCM", "title": "PAPI_L2_DCM: L2 data cache misses", "values": []}
event3 = {"n": 2, "sn": "PAPI_L2_DCH", "title": "PAPI_L2_DCH: L2 data cache hits", "values": []}
event4 = {"n": 3, "sn": "PAPI_FP_OPS", "title": "PAPI_FP_OPS: Floating point operations", "values": []}


events = [event1, event2, event3, event4]
for event in events:
    for algo in algorithms:
        with open("results/single_events/event"+str(event["n"])+"_algo" + str(algo) + ".txt") as f:
            e1 = f.next().strip()
            event["values"].append(int(e1.strip()))


for event in events:
	plt.bar(algorithms, event["values"], 0.3)
	plt.title(event["title"])
	pl.savefig('plots/single_events/' + event["sn"])