{Utils} = require './utils.coffee'

class m2mIO extends Utils
	
  @url = 'api.m2m.io/1/'
  @ACCOUNT = 'account'
	
  constructor: (@username, @password) ->
	
    method = 'constructor'
    @trace @.getName(), method

    @validate @username, @password

  validate: (username, password) ->
	
    method = 'validate'
    @trace @.getName(), method
	
    @debug @.getName(), method, 'username: ' + username
    @debug @.getName(), method, 'password: ' + password
   
    @error(@.getName(),method,@getErrors()[0]) unless username and password

  signup: (cb) ->
	
    method = 'signup'
    @trace @.getName(), method

    Utils.restler.post('http://api.m2m.io/1/account',
      data:
        email: @username
        password: @password
    ).on 'complete', (data, response) =>
	
      @info @.getName(), method, 'response: ' + JSON.stringify data

      if response.statusCode is 201
        cb response

  getAccount: () ->
	
    method = 'getAccount'
    @trace @.getName(), method

  connect: (protocol) ->
	
    method = 'connect'
    @trace @.getName(), method
	
    switch PROTOCOL
      when 'mqtt'

        console.log 'mqtt conn'

      when 'zmq'

        console.log 'zmq conn'

exports.m2mIO = m2mIO