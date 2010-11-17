#!/usr/bin/python

import csv

reader = csv.DictReader(open("november.csv", "rb"), delimiter=",")

for row in reader: 
        print row
