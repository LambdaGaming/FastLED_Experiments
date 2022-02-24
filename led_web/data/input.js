function SendColorSelector() {
	var colorstring = document.getElementById( "colorinput" ).value
	var color = "0x" + colorstring.substring( 1 )
	var connect = new XMLHttpRequest()
	connect.open( "GET", "/state?color=" + Number( color ), true )
	connect.send()
}

function SendHexColor() {
	var hexstring = document.getElementById( "hexinput" ).value
	var lednum = document.getElementById( "ledinput" ).value
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
	var connect = new XMLHttpRequest()
	var url
	if ( lednum >= 0 ) {
		url = "/state?led" + lednum + "=" + Number( color )
	}
	else {
		url = "/state?color=" + Number( color )
	}
	connect.open( "GET", url, true )
	connect.send()
}