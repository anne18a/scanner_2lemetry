// Javascript MQTT Connection Example

var mqtt = require('mqtt'),	// Using the "mqtt" package.
    md5 = require('MD5');

// Define some constants.
// Change username and password to values found in Your Credentials.
var CLIENT_ID = 'g3z559a6c1',
	TOKEN = 'ex2vcx0vfznu',
	TOKEN_HASH = md5(TOKEN),
	HOST = 'q.m2m.io',
	PORT = 1883,
	TOPIC = 'maaakihz/test-stuff/test-thing',
	PAYLOAD = '{"Hello":"World!"}';

// Set object with these connection options.
var options = {
	protocolVersion: 3,
	username: CLIENT_ID, 
	password: TOKEN_HASH,
	keepalive: 30
}

// By creating a client, a connection will automatically be established.
var client = mqtt.createClient(PORT, HOST, options);

// Bind the 'connect' event to this function.
client.on('connect', function(){
	console.log('Client connected.');
});

// Bind the 'message' event to this function.
client.on('message', function(topic, payload){
	console.log('Message received on ' + topic + ': ' + payload);
});

// Subscribe to a topic.
client.subscribe(TOPIC);

// Publish a payload to a topic.
client.publish(TOPIC, PAYLOAD);