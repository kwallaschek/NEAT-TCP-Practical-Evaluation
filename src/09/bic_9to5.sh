#!/bin/bash
sudo sysctl -w net.ipv4.tcp_congestion_control=bic
iperf3 -c 10.2.1.6 -V -i 1 -t 300 --logfile /home/pi/Desktop/output/bic_9-to-5.log