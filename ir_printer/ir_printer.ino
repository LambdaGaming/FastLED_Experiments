// Simple program to print IR reciever input as hex

#include "IRremote.h"

#define IR_PIN 8

void setup()
{
	Serial.begin( 9600 );
	pinMode( IR_PIN, INPUT );
	IrReceiver.begin( IR_PIN );
}

void loop()
{
	if ( IrReceiver.decode() )
	{
		Serial.println( IrReceiver.decodedIRData.decodedRawData, HEX );
	}
	IrReceiver.resume();
}
