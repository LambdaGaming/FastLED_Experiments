#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <FastLED.h>
#include <SPIFFS.h>
#include <WiFi.h>

#define NUM_LEDS 200
#define DATA_PIN 5
#define IR_PIN 25
#define CHIPSET WS2812
#define RGB_ORDER RGB

CRGB leds[NUM_LEDS];
const char *ssid = "";
const char *password = "";
AsyncWebServer server( 80 );

void setup()
{
	Serial.begin( 115200 );
	delay( 10 );
	Serial.println();
	Serial.print( "Connecting to " );
	Serial.println( ssid );
	WiFi.begin( ssid, password );
	MDNS.begin( "colorselector" );
	
	if ( !SPIFFS.begin( true ) ) return;

	while ( WiFi.status() != WL_CONNECTED )
	{
		delay( 500 );
		Serial.print( "." );
	}

	FastLED.addLeds<CHIPSET, DATA_PIN, RGB_ORDER>( leds, NUM_LEDS );
	FastLED.clear( true );
	FastLED.setBrightness( 50 );
	FastLED.setCorrection( TypicalPixelString );

	Serial.println();
	Serial.println( "WiFi connected." );
	Serial.print( "IP address: " );
	Serial.println( WiFi.localIP() );

	server.on( "/", HTTP_GET, []( AsyncWebServerRequest *request ) {
		request->send( SPIFFS, "/index.html", String(), false );
	} );

	server.on( "/state", HTTP_POST, []( AsyncWebServerRequest *request ) {
		if ( request->hasParam( "color" ) )
		{
			int color = request->getParam( "color" )->value().toInt();
			for ( int i = 0; i < NUM_LEDS; i++ )
			{
				leds[i] = color;
			}
			FastLED.show();
		}
		else
		{
			size_t numParams = request->params();
			for ( int i = 0; i < numParams; i++ )
			{
				AsyncWebParameter *param = request->getParam( i );
				int color = param->value().toInt();
				String name = param->name();
				if ( name.startsWith( "led" ) )
				{
					name.remove( 0, 3 );
					int ledNum = name.toInt();
					leds[ledNum] = color;
				}
			}
			FastLED.show();
		}
		request->send( 200, "text/plain", "OK" );
	} );

	server.on( "/settings", HTTP_POST, []( AsyncWebServerRequest * request ) {
		if ( request->hasParam( "brightness" ) )
		{
			int brightness = request->getParam( "brightness" )->value().toInt();
			FastLED.setBrightness( brightness );
		}
		request->send( 200, "text/plain", "OK" );
	} );

	server.on( "/input.js", HTTP_GET, []( AsyncWebServerRequest *request ) {
		request->send( SPIFFS, "/input.js", "text/javascript" );
	} );

	server.on( "/style.css", HTTP_GET, []( AsyncWebServerRequest *request ) {
		request->send( SPIFFS, "/style.css", "text/css" );
	} );

	server.begin();
}

void loop() {}
