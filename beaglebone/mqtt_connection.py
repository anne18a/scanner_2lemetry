# This sample is suppose to show what is possible to do with the beaglebone black and some sensors
# 
# Sensors are EZ3 Maxsonar ultrasonic sensor, 3 axis accelerometer ADXL345 and a led
# 
# Pin connection
#
# ADLX345		Beaglebone
#
# GND			P9_01
# VCC			P9_03
# CS			P9_03
# SDA			P9_20
# SCL			P9_19
#
# EZ3			Beaglebone
# GND			P9_01
# +5			P9_07
# AN			P9_40
#
# LED			Beaglebone
# GND			P8_02
# VCC			P8_10

import Adafruit_BBIO.GPIO as GPIO
import Adafruit_BBIO.ADC as ADC
import paho.mqtt.client as mqtt
from Adafruit_I2C import Adafruit_I2C
import hashlib
import time

GPIO.setup("P8_10", GPIO.OUT)
ADC.setup()

# Replace these values with those found in your Credentials menu.
CLIENT_ID = ""
key = hashlib.md5("").hexdigest()

def si(us):
	si = us - 256 if us > 127 else us
	return si

def accelVals():
	accel_vals = i2c.readList(0x32, 6)
	return [si(accel_vals[1])*256 + si(accel_vals[0]), si(accel_vals[3])*256 + si(accel_vals[2]), si(accel_vals[5])*256 + si(accel_vals[4])]

def pub_msg(val, vals, led):
	ret = "{\"dist\":" + str(val) + ", \"accel\": [\"x\":" + str(vals[0]) + ", \"y\":" + str(vals[1]) + ", \"z\":" + str(vals[2]) + "], \"led\": " + str(led) + "}"
	return ret

def close():
	print "Disconnect"
	client.disconnect()

try:
	# create MQTT client
	print "Create client"
	client = mqtt.Client("beagle-" + CLIENT_ID + "-pub")
	client.loop()

	# connect to 2lemetry platform
	print "Connect"
	client.connect("q.mq.tt", 1883, 60)
	#client.loop()

	# publish a message
	print "Publish"
	#pub_topic = CLIENT_ID + "/things/" + CLIENT_ID
	pub_topic = "public/beagle/test"

	# accelerometer initialization
	i2c = Adafruit_I2C(0x53, 1, False)
	i2c.write8(0x31, 0x01)
	time.sleep(1)
	i2c.write8(0x2D, 0x08)
	time.sleep(1)

	# led init
	GPIO.output("P8_10", GPIO.LOW)
	led = False

	while client.loop() == 0:
		val = ADC.read("P9_40")
		# ADC value converted to voltage
		val *= 1.8
		# manufacturer value, 1 inch = 0.00699 V
		val /= 0.00699
		# get accelerometer values
		vals = accelVals()
		# manage the led
		if val < 20:
			GPIO.output("P8_10", GPIO.HIGH)
			led = True
		else:
			GPIO.output("P8_10", GPIO.LOW)
			led = False

		#print json formated message
		msg = pub_msg(val, vals, led)

		print msg
		client.publish(pub_topic, msg, 0)
		time.sleep(0.5)
		pass

except (KeyboardInterrupt):
	print "Interrupt received"
	close()