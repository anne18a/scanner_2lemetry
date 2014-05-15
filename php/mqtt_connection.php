<?php
// PHP MQTT Connection Example

// Define constants
$_CLIENT_ID = 'g3z559a6c1';
$_TOKEN_HASH = md5('ex2vcx0vfznu');

// Using the PHP Mosquitto extension (https://github.com/mgdm/Mosquitto-PHP)
$client = new Mosquitto\Client($_CLIENT_ID);

// Bind callbacks
$client->onConnect('on_connect');
$client->onDisconnect('on_disconnect');
$client->onSubscribe('on_subscribe');
$client->onMessage('on_message');

// Set client credentials.
$client->setCredentials($_CLIENT_ID, $_TOKEN_HASH);

// Connect to q.m2m.io:1883.
$client->connect('q.m2m.io', 1883);

// Subscribe to a topic.
$client->subscribe('maaakihz/test-topic', 0);

// Publish to a topic.
$client->publish('maaakihz/test-topic', '{"encoding":"json", "from":"php"}');

// Loop forever to maintain a connection with the host.
for(;;){
	$client->loop();
}

// Define callback functions.
function on_connect($rc, $message) {
	// Display the connection's result code and explanation message.
	echo 'Code: ' . $rc . ' (' . $message . ')' . PHP_EOL;
}
function on_disconnect() {
	// Display notice/confirmation of being disconnected.
	echo 'Client disconnected.' . PHP_EOL;
}
function on_subscribe() {
	// Confirm that the subscription has been made.
	echo 'Subscription confirmed.' . PHP_EOL;
}
function on_message($message) {
	// Display the received message's topic and payload.
	echo 'Message received on ' . $message->topic . ': ' . $message->payload . PHP_EOL;
}

?>