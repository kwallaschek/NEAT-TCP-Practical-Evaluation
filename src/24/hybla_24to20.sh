#!/bin/bash
sudo sysctl -w net.ipv4.tcp_congestion_control=hybla
iperf3 -c 10.2.1.21 -V -i 1 -t 300 --logfile /home/pi/Desktop/output/hybla_24-to-20.log