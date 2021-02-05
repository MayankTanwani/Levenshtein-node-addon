var addon = require('bindings')('addon.node')

console.log('This should be eight:', addon.editDistance("intention", "execution"))
