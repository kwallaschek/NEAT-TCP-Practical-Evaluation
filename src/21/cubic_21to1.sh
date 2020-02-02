#!/bin/bash
sudo sysctl -w net.ipv4.tcp_congestion_control=cubic
iperf3 -c 10.2.1.2 -V -i 1 -t 300 --logfile /home/pi/Desktop/output/cubic_21-to-1.log