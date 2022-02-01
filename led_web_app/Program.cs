// Simple .NET 6 console program to show how the led_web Arduino program can be interacted with outside of a browser

HttpClient client = new HttpClient();
string input = "";
bool formatted = false;

Console.WriteLine( "Enter a hex number:" );
while ( ( input = Console.ReadLine() ) != null && input != "exit" )
{
	if ( input.StartsWith( "0x" ) )
		formatted = true;

	try
	{
		Console.WriteLine( "Attempting to parse and apply color..." );

		int color;
		if ( formatted )
			color = Convert.ToInt32( input, 16 );
		else
			color = int.Parse( input );

		await client.GetAsync( "http://192.168.1.208/state?color=" + color );
		Console.WriteLine( "Successfully changed the color to " + input + "\n" );
	}
	catch ( Exception e )
	{
		Console.WriteLine( "\nAn error occured while attempting to change the color:\n" + e.Message + "\n" );
	}

	Console.WriteLine( "Enter a hex number:" );
}
