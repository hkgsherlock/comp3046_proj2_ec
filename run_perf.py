#!/usr/bin/env python

import sys
import math
import multiprocessing
import subprocess
import json
import csv
import os

results = []

s_s = []
for i in range(1, int(math.log(8192, 2)) + 1):
	s_s.append(pow(2,i))
t_s = []
for i in list(reversed(range(1, int(math.log(multiprocessing.cpu_count(), 2)) + 1))):
	t_s.append(pow(2,i))

for t in t_s:
	for s in s_s:
		sys.stdout.write('running program with size_n=%d on threads=%d ... ' % (s, t))
		sys.stdout.flush()
		process = subprocess.Popen(['gaussian.exe', str(s), str(t)], stdout=subprocess.PIPE)
		out, err = process.communicate()
		exit_code = process.wait()
		if exit_code != 0:
			print('failed (%d)' % exit_code)
			sys.exit(exit_code)
		else:
			print('ok')
		# print(out)
		results.append(json.loads(out))

# {
# 	"n":..., 
# 	"threads":..., 
# 	"perf":{
# 		"serial":...,
# 		"omp":...
# 	},
# 	"err":{
# 		"serial":...,
# 		"omp":...
# 	}
# }

with open('report.csv', 'wb') as csvfile:
	fieldnames = ['n', 'threads', 'perf_serial', 'perf_omp', 'err_serial', 'err_omp']
	writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

	writer.writeheader()
	for r in results:
		writer.writerow({
			'n': r['n'], 
			'threads': r['threads'], 
			'perf_serial': r['perf']['serial'], 
			'perf_omp': r['perf']['omp'], 
			'err_serial': r['err']['serial'], 
			'err_omp': r['err']['omp']})

os.rename('report.csv', 'report_%s.csv' % datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S"))