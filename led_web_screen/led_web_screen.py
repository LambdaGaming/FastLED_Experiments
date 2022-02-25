# Python 3.8+ program that takes colors from the screen and applies it to the LED string

from PIL import ImageGrab
import requests
import random
import time

WIDTH = 1920
HEIGHT = 1080

def GetPixels():
	params = ""
	curtime = time.perf_counter()
	for i in range( 199 ):
		color = pixel[random.randrange( 0, WIDTH ), random.randrange( 0, HEIGHT )]
		finalcolor = "{:02x}{:02x}{:02x}".format( color[0], color[1], color[2] )
		finalcolor = str( int( finalcolor, 16 ) )
		params += "led{0}={1}&".format( i, finalcolor )
	requests.get( "http://192.168.1.208/state?" + params )
	print( "Applied colors in {0} seconds.".format( time.perf_counter() - curtime ) )

while True:
	print( "Initializing..." )
	pixel = ImageGrab.grab().load()
	print( "Ready!" )
	GetPixels()
	time.sleep( 10 )
