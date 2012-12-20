c-embedded
================

A lightweight MQTT client example for embedded devices running C.  Forked from the menudoproblema/libemqtt library (https://github.com/menudoproblema/libemqtt.git).

libemqtt was chosen as a base for this repository because of its relative ease of porting to various embedded environments / RTOSes.  libemqtt is single threaded which lends itself to an easier port to an embedded application / RTOS.

Handling the interface to the TCP/IP library is the only porting required to get this library to work on a particular embedded platform.  The following functions in example.c will need to be ported:

	* init_socket
	* close_socket
	* send_packet
	* read_packet

The example.c file includes code to provision a device on the m2m.io platform as well as publish sensor data.  The function readTemperatureSensor is included to illustrate a loop of reading a sensor value and publishing it to the m2m.io platform.

At the top of example.c are some constant parameters which need to be updated.  The values to use pertain to your m2m.io portal account and can be found on the Account tab after logging in.  The portal can be found at http://apps.m2m.io.

Usage:  This library will compile and run with gcc.  It can be built and ran as a test on a host Mac/PC/Linux machine.  using the -p flag when running will cause the provisioning message to be sent before publishing sensor values in a continous loop.  The provisioning only needs to be done once and can be skipped for subsequent runs of the program.

Note:  This client does not fully implement the MQTT 3.1 spec.  More specifically, QoS 2.  If a more complete C client is desired, please see the Paho C client: http://git.eclipse.org/c/paho/org.eclipse.paho.mqtt.c.git/.  The Paho C client will be a more difficult port to most embedded environments. 
