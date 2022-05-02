function ValidNumber( num ) {
	return num >= 0 && num < 200
}

function SendColor() {
	var colorstring = document.getElementById( "colorinput" ).value
	var hexstring = document.getElementById( "hexinput" ).value
	var lednum = document.getElementById( "ledinput" ).value
	var color = "0x" + colorstring.substring( 1 )

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

	color = Number( color )
	var url = "/state?"
	if ( lednum.length > 0 ) {
		if ( lednum.includes( "," ) ) {
			var split = lednum.split( "," )
			split.forEach( e => {
				if ( !ValidNumber( e ) ) {
					alert( "Invalid number detected." )
					return
				}
				url += "led" + e + "=" + color + "&"
			} );
		}
		else if ( lednum.includes( ":" ) ) {
			var split = lednum.split( ":" )
			var min = Number( split[0] )
			var max = Number( split[1] )
			var add = Number( split[2] ) || 1
			if ( min > max ) {
				alert( "The first number of the range must be smaller than the second number." )
				return
			}
			if ( !ValidNumber( min ) || !ValidNumber( max ) ) {
				alert( "Invalid number detected." )
				return
			}
			for ( var i = min; i <= max; i += add ) {
				url += "led" + i + "=" + color + "&"
			}
		}
		else if ( lednum.match( /^[0-9]+$/ ) != null ) {
			if ( !ValidNumber( lednum ) ) {
				alert( "Invalid number detected." )
				return
			}
			url += "led" + lednum + "=" + color
		}
		else {
			alert( "Invalid characters detected." )
			return
		}
	}
	else {
		url += "color=" + Number( color )
	}

	var connect = new XMLHttpRequest()
	connect.open( "POST", url, true )
	connect.send()
}
