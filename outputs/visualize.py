import csv
import sys

with open('./9/output/vegas_9-to-5.log') as csvfile:
	readCSV = csv.reader(csvfile, delimiter=" ", quotechar=None)
	for row in readCSV:
		try:
			print(row[1])
		except:
			f = 1