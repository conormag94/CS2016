#!/usr/bin/python
import math

def meanAndVariance(f_name):
	
	if(f_name) == "StartTimes.log":
		print "\nStart Time -> Time between creation and first running"
	elif(f_name) == "TurnaroundTimes.log":
		print "\nTurnaround Time -> Time between creation and deletion"

	print "-------------------------"
	values = []
	total1 = 0;
	count = 0;

	# Calculate mean of results in log file
	with open(f_name, "r") as f_in:
		for line in f_in:
			s = line.strip("\n")
			values.append(int(s))
			total1 = total1 + int(s)
			count = count + 1
	f_in.close()

	mean = total1 / count

	# Calculate variance by subtracting each result from the mean,
	# squaring it and then getting the mean of those squared differences
	sq_diffs = []
	total2 = 0
	for x in values:
		result = (x-mean)**2
		sq_diffs.append(result)
		total2 += result

	variance = total2 / len(sq_diffs)

	print "Mean:\t\t", mean
	print "Variance:\t", variance

def main():
	print "** Times measured in ticks **"
	meanAndVariance("StartTimes.log")
	# meanAndVariance("ExecutionTimes.log")
	meanAndVariance("TurnaroundTimes.log")

if __name__ == '__main__':
	main()