xml2js = require 'xml2js'
fs = require 'fs'
restler = require 'restler'
_ = require 'underscore'
crypto = require 'crypto'
mqtt = require 'mqttjs/lib/mqtt'

# Used to clarify client errors.
ignoreDeps = { }

try
  zmq = require 'zmq'
catch error
  ignoreDeps['zmq'] = true

xml2js = new xml2js.Parser()

# Used for TRACE, DEBUG, INFO, WARN, ERROR logging levels.
Object::getName = ->
  funcNameRegex = /function (.{1,})\(/
  results = (funcNameRegex).exec(@constructor.toString())
  if results?.length > 1 then results[1] else ''

class Utils
	
  @fs = fs
  @xml2js = @xml2js
  @restler = restler
  @_ = _
  @crypto = crypto
  @mqtt = mqtt
  @zmq = zmq

  getIgnoredDeps: () ->
    
    ignoreDeps

  getErrors: () ->
	
    errors = { }
    errors[0] = 'No credentials supplied.'
    
    errors

  # @args, [], A set of values to concat with :.	
  buildKey: (args) ->
	
    key = ''
    _.each args, (arg) =>
      key = key + ':' + arg
    key = key.substring 1, key.length
    key

  formatDate: (date) ->
	
    date.getUTCHours() + ':' + date.getUTCMinutes() + ':' + date.getUTCSeconds() + ' ' + date.getTime()

  trace: (className, method) ->
	
    console.log('----- ' + @formatDate(new Date()) + ' TRACE ' + @buildKey([className, method]) + ' -----')
   	
  debug: (className, method, msg) ->

    console.log('***** ' + @formatDate(new Date()) + ' DEBUG ' + @buildKey([className, method]) + ' ' + msg + ' *****')
	
  info: (className, method, msg) ->

    console.log('===== ' + @formatDate(new Date()) + ' INFO ' + @buildKey([className, method]) + ' ' + msg + ' =====')
	
  warn: (className, method, msg) ->
	
    console.log('????? ' + @formatDate(new Date()) + ' WARN ' + @buildKey([className, method]) + ' ' + msg + ' ?????')
	
  error: (className, method, msg) ->

    console.log('!!!!! ' + @formatDate(new Date()) + ' ERROR ' + @buildKey([className, method]) + ' ' + msg + ' !!!!!')

exports.Utils = Utils