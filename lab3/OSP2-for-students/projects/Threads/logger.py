#!/usr/bin/python
import re

print "Writing appropriate log results from OSP.log to results.log..."
start_times = open("StartTimes.log", "w")
turnaround_times = open("TurnaroundTimes.log", "w");

# Gets the start times and turnaround times and logs them to their own files
with open("OSP.log", "r") as f_in:
	for line in f_in:
		if "Start time for Thread" in line:
			out = re.search(r'(?<=\):\s)(\d+)', line).group(0)
			start_times.write(out)
			start_times.write("\n")
			# start_times.write(line.lstrip())
		elif "Turnaround Time for Thread" in line:
			out = re.search(r'(?<=\):\s)(\d+)', line).group(0)
			turnaround_times.write(out)
			turnaround_times.write("\n")
			# turnaround_times.write(line.lstrip())

f_in.close()
start_times.close()
turnaround_times.close()

print "...Done!"