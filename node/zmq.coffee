{Utils} = require './utils.coffee'

class ZMQ extends Utils
	
  constructor: () ->
	
    method = 'constructor'
    @trace @.getName(), method

    if @ignoreDeps['zmq']
      @error @.getName(), 'dependency not found: zmq, exiting'
      process.exit 1

  connectAsProducer: () ->

    method = 'connectAsProducer'
    @trace @.getName(), method

    @sock = @zmq.socket 'push'
    @sock.bindSync 'tcp://q.m2m.io:3000'

    @info 'producer bound to port 3000'

  worker: (callback) ->

    method = 'worker'
    @trace @.getName(), method

    @sock = zmq.socket 'pull'
    @sock.connect 'tcp://q.m2m.io:3000'

    @info @.getName(), 'worker connected to port 3000'
    
    @sock.on 'message', (msg) =>
      callback msg.toString()

  send: (message) ->

    @sock.send message