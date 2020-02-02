#!/bin/bash
iperf3 -s -D -p 5220 --logfile /home/pi/Desktop/server00_5220.log
iperf3 -s -D -p 5204 --logfile /home/pi/Desktop/server00_5204.log

