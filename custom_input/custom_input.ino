// Program that allows the user to input a raw hex value from a remote to change the color of an LED string.

#include "FastLED.h"
#include "IRremote.h"
#include <sstream>

#define NUM_LEDS 200
#define DATA_PIN 5
#define IR_PIN 25
#define CHIPSET WS2812
#define RGB_ORDER RGB

CRGB leds[NUM_LEDS];
std::string StringBuffer;

void setup()
{
	delay( 2000 );
	pinMode( IR_PIN, INPUT );
	FastLED.addLeds<CHIPSET, DATA_PIN, RGB_ORDER>( leds, NUM_LEDS );
	FastLED.clear( true );
	IrReceiver.begin( IR_PIN );
}

void loop()
{
	if ( IrReceiver.decode() )
	{
		auto data = IrReceiver.decodedIRData.decodedRawData;
		switch ( data )
		{
			case 0x43F: case 0x1043F: // Remote can send out either of these for one button; they alternate after every press
				StringBuffer += "A";
				break;
			case 0x113F: case 0x1113F:
				StringBuffer += "B";
				break;
			case 0x3F: case 0x1003F:
				StringBuffer += "C";
				break;
			case 0x442: case 0x10442:
				StringBuffer += "D";
				break;
			case 0x153F: case 0x1153F:
				StringBuffer += "E";
				break;
			case 0x1538: case 0x11538:
				StringBuffer += "F";
				break;
			case 0x401: case 0x10401:
				StringBuffer += "1";
				break;
			case 0x402: case 0x10402:
				StringBuffer += "2";
				break;
			case 0x403: case 0x10403:
				StringBuffer += "3";
				break;
			case 0x404: case 0x10404:
				StringBuffer += "4";
				break;
			case 0x405: case 0x10405:
				StringBuffer += "5";
				break;
			case 0x406: case 0x10406:
				StringBuffer += "6";
				break;
			case 0x407: case 0x10407:
				StringBuffer += "7";
				break;
			case 0x408: case 0x10408:
				StringBuffer += "8";
				break;
			case 0x409: case 0x10409:
				StringBuffer += "9";
				break;
			case 0x400: case 0x10400:
				StringBuffer += "0";
				break;
			case 0x45C: case 0x1045C:
				int hex;
				std::stringstream ss;
				ss << std::hex << StringBuffer;
				ss >> hex;
				FastLED.showColor( hex );
				StringBuffer.clear();
		}
		delay( 100 ); // Small delay so only the first button press is registered
	}
	IrReceiver.resume();
}
