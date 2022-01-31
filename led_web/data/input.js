function SendColor() {
	var colorstring = document.getElementById( "colorinput" ).value
	var hexstring = document.getElementById( "hexinput" ).value
	var color

	if ( hexstring.length > 0 ) {
		if ( hexstring.startsWith( "0x" ) ) {
			color = hexstring
		}
		else if ( hexstring.startsWith( "#" ) ) {
			color = hexstring.substring( 1 )
			color = "0x" + color
		}
		else {
			color = "0x" + hexstring
		}
	}
	else {
		color = "0x" + colorstring.substring( 1 )
	}
	
	var connect = new XMLHttpRequest()
	connect.open( "GET", "/state?color=" + Number( color ), true )
	connect.send()
}