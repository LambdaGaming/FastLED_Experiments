function SendColor() {
	var colorstring = document.getElementById( "colorinput" ).value
	var color = "0x" + colorstring.substring( 1 )
	location.href += "state?color=" + Number( color )
}