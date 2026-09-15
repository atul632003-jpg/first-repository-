#!/bin/bash

echo "========================================"
echo "CPU SCHEDULING BENCHMARK"
echo "========================================"

echo
echo "---- CPU 0 ----"
time taskset -c 0 ./fcfs

echo
echo "---- CPU 1 ----"
time taskset -c 1 ./fcfs

echo
echo "---- NUMA Node 0 ----"
time numactl --cpunodebind=0 --membind=0 ./fcfs

echo
echo "---- NUMA Hardware ----"
numactl --hardware
