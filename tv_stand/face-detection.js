'use strict'
const cv = require('opencv')
const stand = require('./stand.js')

const window = new cv.NamedWindow('Video', 1)

class FaceDetector {
  constructor() {
    this.camera = new cv.VideoCapture(0)
  }

  capture(callback) {
    this.camera.read((err, im) => {
      if (err) {
        callback(err)
      }
      if (im.width() < 1 || im.height() < 1) {
        callback(new Error('Image has no size'))
      }

      im.detectObject(cv.FACE_CASCADE, {}, function(err, faces) {
        for (let i=0; i < faces.length; i++) {
          let face = faces[i]
          im.rectangle([face.x, face.y], [face.width, face.height], [0, 255, 0], 2)
        }
        callback(null, {im, faces})
      })
    })
  }

}

stand.on('ready', () => {
  stand.setSpeed(10)
})


const faceDetector = new FaceDetector()
function frame() {
  faceDetector.capture((err, result) => {
    if (err) {
      throw err
    }


    checkPosition(result)

    window.show(result.im)
    window.blockingWaitKey(0, 1)

    process.nextTick(frame)
  })
}
frame()

let moving = false
let centerColor = [0, 255, 0]
function checkPosition(result) {
  if (result.faces.length <= 0) {
    if (moving) {
      stand.stop()
      centerColor = [0, 255, 0]
      moving = false
    }
    return
  }

  let face = result.faces.sort((a, b) => (b.width * b.height) - (a.width * a.height))[0]
  let center = { x: face.x + face.width / 2, y: face.y + face.height / 2 }
  let limits = [result.im.width() / 2 - face.width / 2, result.im.width() / 2 + face.width / 2]
  let stopLimits = [result.im.width() / 2 - 10, result.im.width() / 2 + 10]

  limits.forEach(limit => result.im.line([limit, 0], [limit, result.im.height()], [0, 255, 0], 3))
  stopLimits.forEach(limit => result.im.line([limit, 0], [limit, result.im.height()], [0, 255, 0], 1))

  if (moving) {
    if (center.x >= stopLimits[0] && center.x <= stopLimits[1]) {
      stand.stop()
      centerColor = [0, 255, 0]
      moving = false
    }
  } else {
    if (center.x < limits[0]) {
      centerColor = [0, 0, 255]
      stand.rotateRight()
      moving = true
    }
    if (center.x > limits[1]) {
      centerColor = [0, 0, 255]
      stand.rotateLeft()
      moving = true
    }
  }


  result.im.ellipse(center.x, center.y, 4, 4, centerColor, -1)
}
