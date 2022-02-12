# Python program that takes a color from the center of the screen every half second and applies it to the LED string

from PIL import ImageGrab
import requests
import time

# Helps bring out the dull colors so not everything appears to be a shade of white
def ColorCorrection( color ):
	newcolor = list( color )
	for i in range( 3 ):
		if newcolor[i] <= 100:
			newcolor[i] *= 2
	return newcolor

WIDTH = 1920
HEIGHT = 1080
previouscolor = 0
while True:
	pixel = ImageGrab.grab().load()
	color = pixel[WIDTH / 2, HEIGHT / 2]
	color = ColorCorrection( color )
	finalcolor = "{:02x}{:02x}{:02x}".format( color[0], color[1], color[2] )
	finalcolor = str( int( finalcolor, 16 ) )

	if finalcolor != previouscolor:
		# No need to send a request if the color isn't changing
		requests.get( "http://192.168.1.208/state?color=" + finalcolor )
		print( "New color: " + finalcolor )

	previouscolor = finalcolor
	time.sleep( 0.5 )
