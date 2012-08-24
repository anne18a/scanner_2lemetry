{m2mIO} = require '../index.coffee'

m2m = new m2mIO( 'client.test.node.1@tests.com', 'mypas')

m2m.signup (cb) ->
  console.log 'returned'