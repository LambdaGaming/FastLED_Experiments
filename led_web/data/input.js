function SendColor() {
	var colorstring = document.getElementById( "colorinput" ).value
	var color = "0x" + colorstring.substring( 1 )
	var connect = new XMLHttpRequest()
	connect.open( "GET", "/state?color=" + Number( color ), true )
	connect.send()
}