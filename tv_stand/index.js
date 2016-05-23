var keypress = require('keypress')
var stand = require('./stand.js')

var speed = 2

stand.on('ready', () => {
  stand.setSpeed(speed)
})

keypress(process.stdin)
process.stdin.on('keypress', function (ch, key) {
  if (key && key.ctrl && key.name == 'c') {
    process.exit()
  }

  if (key && key.name === 'left') {
    stand.rotateLeft()
  }

  if (key && key.name === 'right') {
    stand.rotateRight()
  }

  if (key && key.name === 'up') {
    speed++
    stand.setSpeed(speed)
  }

  if (key && key.name === 'down') {
    speed--
    stand.setSpeed(speed)
  }
  if (key && key.name === 's') {
    stand.stop()
  }
})

process.stdin.setRawMode(true)
process.stdin.resume()
