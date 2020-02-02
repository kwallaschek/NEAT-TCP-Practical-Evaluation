#!/bin/bash
sudo sysctl -w net.ipv4.tcp_congestion_control=vegas
iperf3 -c 10.2.1.5 -V -i 1 -t 300 --logfile /home/pi/Desktop/output/vegas_24-to-4.log