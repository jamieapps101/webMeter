**webMeter Project**
======================

Simple project polling an esp8266 for data so as to act
as a detached meter for physical readings. Using a web interface, a live readout shall be given as well as a plotted summary of the previous readings.


To Do Soon:
* Create JS to attach to controls section
* add websocket object
* Add sanity checks/validation to that
* Add some CSS to actually make the thing look useable
* Rearrange bottom inputs into a grid
* Add the graphing functionality using plotly.js
* create a repeat polling function/look into sockets with an interrupting function to allow refresh on update
* Build hardware
* write firmware
* test

To Do At Some Point:
* make it mobile friendly
* export graph
* add server style script for longer data logging
* add battery measurements/estimates to monitor hardware health
* add cookies to remember previous device IP, update rate and unit settings
