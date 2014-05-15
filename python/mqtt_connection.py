# Python MQTT Connection Example

import paho.mqtt.client as mqtt     # Using the Paho MQTT client
import hashlib
import time

# Define some constants.
# Change the username and token to those found in Your Credentials.
USERNAME = 'g3z559a6c1'
TOKEN_HASH = hashlib.md5('ex2vcx0vfznu').hexdigest()
HOST = 'q.m2m.io'
PORT = 1883
TOPIC = 'maaakihz/test-topic'
PAYLOAD = '{"Hello":"World!"}'
QOS = 0

# Result codes and their explanations for connection failure debugging.
RESULT_CODES = {
    0: 'Connection successful',
    1: 'Incorrect protocol version',
    2: 'Invalid client identifier',
    3: 'Server unavailable',
    4: 'Bad username or password',
    5: 'Not authorized'
}

def on_connect(client, userdata, rc):
    if rc == 0:
        print("Connection successful! (Result code 0)")

        test_publish()
        test_subscribe()

    else:
        print("Connection unsuccessful! (Result code " + str(rc) + ": " + RESULT_CODES[rc] + ")")

        # Stop the loop from trying to connect again if unsuccessful.
        client.disconnect()

# The following are functions bound to callbacks.
def on_disconnect(client, userdata, rc):
    print("Connection has been terminated.")

    # This will automatically reconnect if connection is lost.

def on_publish(client, userdata, mid):
    print("Message " + str(mid) + " has been published.")

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscription confirmed.")

def on_unsubscribe(client, userdata, mid):
    print("Unsubscribe confirmed.")

def on_message(client, userdata, message):
    print("Received message on topic " + str(message.topic) + " (QOS " + str(message.qos) + "): " + str(message.payload))

# These functions test the publishing and subscription functionality.
def test_publish():
    print("Publishing to " + TOPIC + " (QOS " + str(QOS) + "): " + PAYLOAD)
    client.publish(TOPIC, PAYLOAD, QOS)

def test_subscribe():
    print("Subscribing to " + TOPIC)
    client.subscribe(TOPIC, QOS)

# Create client object -- use USERNAME as client ID to prevent
# a random ID from being generated for each connection.
client = mqtt.Client(USERNAME)

# Bind callbacks to the relevant functions.
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_publish = on_publish
client.on_subscribe = on_subscribe
client.on_unsubscribe = on_unsubscribe
client.on_message = on_message

# Set client username and token information.
client.username_pw_set(USERNAME, TOKEN_HASH)

# Establish the connection.
client.connect(HOST, PORT)

# Maintain a connection with the server.
client.loop_forever()