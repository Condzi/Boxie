/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

class GameScene final :
	public con::Scene
{
public:
	con::BitmapText text;
	void onPush() override
	{
		tag = "Game";
		con::Global.Assets.BitmapFonts.load( "data/vincent.png", "vincent" );
		// @ToDo: Fix this so we don't have to const_cast to set the glyph size.
		con::Global.Assets.BitmapFonts.get( "vincent" ).setGlyphSize( { 8,8 } );
		text = con::BitmapText( "Hello, World!", con::Global.Assets.BitmapFonts.get( "vincent" ) );
	}
};