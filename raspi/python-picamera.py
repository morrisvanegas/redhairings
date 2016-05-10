import picamera
import time
import datetime

camera = picamera.PiCamera()

camera.sharpness = 0
camera.contrast = 44
camera.brightness = 60
camera.saturation = 0
camera.ISO = 10
camera.video_stabilization = True
camera.exposure_compensation = 10
camera.exposure_mode = 'auto'
camera.meter_mode = 'average'
camera.awb_mode = 'auto'
camera.image_effect = 'none'
camera.color_effects = None
camera.rotation = 0
camera.hflip = False
camera.vflip = True
camera.crop = (0.0, 0.0, 1.0, 1.0)

#date = datetime.datetime.now().strftime('%h%m%s')
camera.capture('test.jpg')
