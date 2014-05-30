import serial
import os
import glob
import time
import paho.mqtt.client as mqtt
import json
import urllib2
import hashlib

ser = serial.Serial(port = "/dev/ttyAMA0", baudrate=9600)
ser.close()

# Replace these values with those found under "Credentials" in your ThingFabric dashboard.
CLIENT_ID = # Your client_id
TOKEN = # Your token
TOKEN_HASH = hashlib.md5(TOKEN).hexdigest()
pub_topic = "maaakihz/test-stuff/test-thing"
sub_topic = "maaakihz/test-stuff/test-thing"
mqtt_server = "q.m2m.io"
mqtt_port = 1883
t_connect = 0
size = 32

def close():
	global ser
	ser.close()

def checkConnection():
	try:
		urllib2.urlopen("http://74.125.225.192", timeout=1)
		return True
	except urllib2.URLError as err: pass
	return False

def reconnect(clt, userdata, rc):
	global t_connect
	print "Client disconnected"
	
#	while checkConnection() == False:
#		time.sleep(30)
	lo()

def connect(clt, userdata, rc):
	global t_connect
	t_connect = 0
	print "Client connected"

def message(clt, userdata, message):
	global ser
	global size
	data = json.loads(message.payload)
	msg = data["Message"]
	ll = len(msg)
	ser.open()
	if ser.isOpen():
		for i in range(0,size):
			ser.write(" ")
		ser.write(msg)
	size = 32 - ll + 32
	ser.close()

def lo():
	global t_connect
	client = mqtt.Client()
	client.username_pw_set(CLIENT_ID, TOKEN)
	client.on_connect = connect
	client.on_disconnect = reconnect
	client.on_message = message

	while client.loop() > 0: 
		client.connect(mqtt_server, mqtt_port, 60)
	 	print "Loop: " + str(t_connect)
	 	time.sleep(10*t_connect*t_connect)
	 	t_connect += 1

	client.publish(pub_topic, "I'm alive", 0)
	client.subscribe(sub_topic)
	
	while client.loop() == 0:
		time.sleep(5)
		pass

try:
#	while checkConnection() == False:
#		time.sleep(30)
	lo()

except (KeyboardInterrupt):
	print "Interrupt received"
	close()