{Utils} = require '../utils.coffee'

errors = { }

class Test extends Utils
	
test = new Test()

test.buildKey(['myClass', 'myMethod'])
test.formatDate(new Date())
test.trace('myClass', 'myMethod')
test.debug('myClass', 'myMethod', 'debug test')
test.info('myClass', 'myMethod', 'info test')
test.warn('myClass', 'myMethod', 'warn test')
test.error('myClass', 'myMethod', 'error test')

console.log 'deps to ignore: ' + JSON.stringify test.getIgnoredDeps()

console.log 'errors: ' + JSON.stringify test.getErrors()
console.log 'error 0: ' + test.getErrors()[0]