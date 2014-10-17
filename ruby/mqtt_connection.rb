# Ruby MQTT Connection Example

require 'rubygems'
require 'mqtt' 		# Using the mqtt gem
require 'digest'

# Define some constants.
# Change username and password to values found in Your Credentials.
USERNAME = ''
TOKEN = ''
TOKEN_HASH = Digest::MD5.hexdigest(TOKEN)
HOST = 'q.thingfabric.com'
PORT = 1883		# Use port 8883 for SSL.
TOPIC = '[domain]/test-stuff/test-thing'
PAYLOAD = '{"Hello":"World!"}'

# Connect to q.thingfabric.com using the following parameters.
MQTT::Client.connect(
	:client_id => "ruby-mqtt",
	:remote_host => HOST,
	:remote_port => PORT,
	:username => USERNAME,
	:password => TOKEN_HASH
	) do |client|
	# Confirm that the connection has been made.
	puts 'Connected to host.'

	# The publishing has to be done in a separate thread, as 
	# the subscription service locks up the current thread.
	Thread.new do
		# Publish a payload to a topic.
		client.publish(TOPIC, PAYLOAD)

		# Display a notice that the message was published.
		puts 'Published message.'
	end

	# This both subscribes to a topic and defines the callback function.
	client.get(TOPIC) do |topic, message|
		# Display the received message's topic and payload.
		puts "Received message on #{topic}: #{message}"
	end
end
