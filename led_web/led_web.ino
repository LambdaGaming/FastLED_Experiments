#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <FastLED.h>

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
	
	if ( !SPIFFS.begin( true ) ) return;

	while ( WiFi.status() != WL_CONNECTED )
	{
		delay( 500 );
		Serial.print( "." );
	}

  FastLED.addLeds<CHIPSET, DATA_PIN, RGB_ORDER>( leds, NUM_LEDS );
  FastLED.clear( true );

	Serial.println();
	Serial.println( "WiFi connected." );
	Serial.print( "IP address: " );
	Serial.println( WiFi.localIP() );

	server.on( "/", HTTP_GET, []( AsyncWebServerRequest *request ) {
    FastLED.showColor( CRGB::Green );
		request->send( SPIFFS, "/index.html", String(), false );
	} );

	server.on( "/style.css", HTTP_GET, []( AsyncWebServerRequest *request ) {
		request->send( SPIFFS, "/style.css", "text/css" );
	} );

	server.begin();
}

void loop() {}