var serialport = require('serialport')
var EventEmitter = require('events').EventEmitter

var stand = new EventEmitter()

var serialPort = new serialport.SerialPort('/dev/ttyACM0', {
  baudrate: 9600,
  parser: serialport.parsers.readline('\n')
})

serialPort.on('open', () => {
  serialPort.on('data', data => {
    console.log('From stand: ', data.toString())
  })

  stand.emit('ready')
})

stand.rotateLeft = () => {
  serialPort.write('CCW\n')
}

stand.rotateRight = () => {
  serialPort.write('CW\n')
}

stand.setSpeed = (speed) => {
  serialPort.write('RPM ' + speed + '\n')
}

stand.stop = () => {
  serialPort.write('STOP\n')
}

module.exports = stand
