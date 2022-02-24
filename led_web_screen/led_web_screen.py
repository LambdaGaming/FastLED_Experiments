# Python 3.8+ program that takes colors from the screen and applies it to the LED string

from PIL import ImageGrab
import requests
import time

WIDTH = 1920
HEIGHT = 1080

def GetPixels():
	params = ""
	count = 0
	curtime = time.perf_counter()
	for y in range( 0, WIDTH, 19 ):
		for x in range( 0, HEIGHT, 10 ):
			if count > 199: break
			color = pixel[x, y]
			finalcolor = "{:02x}{:02x}{:02x}".format( color[0], color[1], color[2] )
			finalcolor = str( int( finalcolor, 16 ) )
			params += "led{0}={1}&".format( count, finalcolor )
			count += 1
	requests.get( "http://192.168.1.208/state?" + params )
	print( "Applied colors in {0} seconds.".format( time.perf_counter() - curtime ) )

while True:
	print( "Initializing..." )
	pixel = ImageGrab.grab().load()
	print( "Ready!" )
	GetPixels()
	time.sleep( 10 )
