#!/bin/bash
sudo sysctl -w net.ipv4.tcp_congestion_control=bic
iperf3 -c 10.2.1.16 -V -i 1 -t 300 --logfile /home/pi/Desktop/output/bic_19-to-15.log