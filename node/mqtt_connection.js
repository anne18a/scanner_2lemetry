// Load required packages (node, npm)
var mqtt = require('mqtt'),
    md5 = require('md5');

// Set object with these connection options
var options = {
	protocolVersion: 3,
	username: 'g3z559a6c1',
	password: md5('ex2vcx0vfznu'),
	keepalive: 30,
	clientId: 'g3z559a6c1'
}

// By creating a client, a connection will automatically be established
var client = mqtt.createClient(1883, 'q.m2m.io', options);

// Bind the 'connect' event to this function
client.on('connect', function(){
	console.log('Client connected.');
});

// Bind the 'message' event to this function
client.on('message', function(topic, payload){
	console.log(payload);
});

// Subscribe to a topic
client.subscribe('maaakihz/test-topic');

// Publish a payload to a topic
client.publish('maaakihz/test-topic', '{"Hello": "World!"}');