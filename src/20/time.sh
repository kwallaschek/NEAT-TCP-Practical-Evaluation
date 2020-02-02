#!/bin/bash
sudo date -s "Mon May 24 12:04:00 UTC 2018"



@reboot /home/pi/Desktop/startscript.sh
@reboot /home/pi/Desktop/insert_modules.sh
@reboot /home/pi/Desktop/09/time.sh

15 12 * * * /home/pi/Desktop/21/neat_21to1.sh
21 12 * * * /home/pi/Desktop/21/neat_21to1.sh
27 12 * * * /home/pi/Desktop/21/neat_21to1.sh
33 12 * * * /home/pi/Desktop/21/bic_21to1.sh
39 12 * * * /home/pi/Desktop/21/bic_21to1.sh
45 12 * * * /home/pi/Desktop/21/bic_21to1.sh
51 12 * * * /home/pi/Desktop/21/cubic_21to1.sh
57 12 * * * /home/pi/Desktop/21/cubic_21to1.sh
3 13 * * * /home/pi/Desktop/21/cubic_21to1.sh
9 13 * * * /home/pi/Desktop/21/hybla_21to1.sh
15 13 * * * /home/pi/Desktop/21/hybla_21to1.sh
21 13 * * * /home/pi/Desktop/21/hybla_21to1.sh
27 13 * * * /home/pi/Desktop/21/reno_21to1.sh
33 13 * * * /home/pi/Desktop/21/reno_21to1.sh
39 13 * * * /home/pi/Desktop/21/reno_21to1.sh
45 13 * * * /home/pi/Desktop/21/vegas_21to1.sh
51 13 * * * /home/pi/Desktop/21/vegas_21to1.sh
57 13 * * * /home/pi/Desktop/21/vegas_21to1.sh
03 12 * * * /bin/sh /home/pi/Desktop/21/test.sh
