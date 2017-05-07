#!/usr/bin/env python

import math
import multiprocessing
import subprocess
import json
import csv

results = []

sizes = []
for i in range(1, math.log(8192, 2) + 1):
	sizes.append(pow(2,i))
threads = []
for i in reversed(range(1, int(math.log(multiprocessing.cpu_count(), 2)) + 1)):
	threads.append(pow(2,i))

	for t in threads:
		for s in sizes:
			process = subprocess.Popen(['gaussian.exe', str(s), str(t)], stdout=subprocess.PIPE)
			out, err = process.communicate()
			exit_code = process.wait()
			if exit_code != 0:
				sys.exit(exit_code)
			print(out)
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