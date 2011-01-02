#!/usr/bin/python

import csv
import os

csv_filenames = []

for dirname, dirnames, filenames in os.walk('.'):
	for filename in filenames:
		if True == filename.endswith("csv"):
			print os.path.join(dirname, filename)
			csv_filenames.append(os.path.join(dirname, filename))	

dum = sorted(csv_filenames)

sunrise = []
sunset = []

for i in dum:
	print i
	reader = csv.DictReader(open(i, "rb"), delimiter=",")
	for row in reader: 
		print row
		sunrise.append(row['Sonnenaufgang'])
		sunset.append(row['Sonnenuntergang'])
print sunrise
