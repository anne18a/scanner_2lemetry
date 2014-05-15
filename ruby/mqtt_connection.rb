# Ruby MQTT Connection Example

require 'rubygems'
require 'mqtt' 		# Using the mqtt gem
require 'digest'

# Connect to q.m2m.io using the following parameters.
MQTT::Client.connect(
	:remote_host => 'q.m2m.io',
	:username => 'g3z559a6c1',
	:client_id => 'g3z559a6c1',
	:password => Digest::MD5.hexdigest('ex2vcx0vfznu')
	) do |client|
	# Confirm that the connection has been made.
	puts 'connected'

	# The publishing has to be done in a separate thread, as the 
	# subscription service locks up the current thread.
	Thread.new do
		# Publish a payload to a topic.
		client.publish('maaakihz/test-topic', '{"encoding":"json", "language":"ruby"}')

		# Display a notice that the message was published.
		puts 'Published message.'
	end

	# This both subscribes to a topic and defines the callback function.
	client.get('maaakihz/test-topic') do |topic, message|
		# Display the received message's topic and payload.
		puts "Received message on #{topic}: #{message}"
	end
end
