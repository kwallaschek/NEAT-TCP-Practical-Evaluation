#!/bin/bash
iperf3 -c 10.2.1.1 -V -i 1 -t 300 --logfile /home/pi/Desktop/output/neat_4-to-0.log -p 5204