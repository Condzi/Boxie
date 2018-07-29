/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TileMap.hpp"

class GameScene final :
	public con::Scene
{
public:
	TileMap Map;

	void onPush() override
	{
		tag = "Game";

		Map.TilesTexture = &con::Global.Assets.Texture.get( "tiles_texture" );

		Map.TileData.reset( { 32, 20 } );
		Tile t;
		t.TextureIndex = 1;
		Map.TileData[0][0] = t;
		Map.TileData[31][0] = t;
		Map.TileData[31][18] = t;
		Map.TileData[0][18] = t;

		Map.updateVertices();

		sf::View view( { 0,0,128,96 } );
		con::Global.GameWindow.setView( view );

		// @ToDo: Add message area on top for this code.
		/*
		text = con::BitmapText( "HELLO, I'M BOXIE", con::Global.Assets.BitmapFonts.getDefault(), { 0,0 }, sf::Color( 200,200,200 ) );
		testShape.setPosition( 1, 8 );
		testShape.setSize( { 4, 4 } );
		testShape.setFillColor( sf::Color( 175, 50, 50 ) );

		*/
	}
};