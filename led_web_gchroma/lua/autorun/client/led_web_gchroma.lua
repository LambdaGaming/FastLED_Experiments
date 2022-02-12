--Gmod addon for controlling LED light strips with GChroma and an Arduino web server

local CurrentColor
local function ToDecimal( vec )
	local r = bit.tohex( vec.x, 2 )
	local g = bit.tohex( vec.y, 2 )
	local b = bit.tohex( vec.z, 2 )
	local finalstr = "0x"..r..g..b
	return tonumber( finalstr )
end

local function GChromaColorSet( device, color, row, col )
	if device == 0 then
		CurrentColor = color
	end
end
hook.Add( "GChromaColorSet", "LEDWebGChromaColorSet", GChromaColorSet )

local function GChromaCreateEffect()
	if CurrentColor then
		--Stupid hack because http.Fetch doesn't allow local IPs
		sound.PlayURL( "http://192.168.1.208/state?color="..ToDecimal( CurrentColor ), "noplay", function() end )
	end
end
hook.Add( "GChromaCreateEffect", "LEDWebGChromaCreateEffect", GChromaCreateEffect )
