/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TileMap.hpp"
#include "MessageArea.hpp"

class GameScene final :
	public con::Scene
{
public:
	TileMap Map;
	MessageArea MessageAr;

	void onPush() override
	{
		tag = "Game";

		Map.TilesTexture = &con::Global.Assets.Texture.get( "tiles_texture" );

		Map.TileData.reset( { 32, 20 } );
		Tile t;
		t.TextureIndex = 1;
		Map.TileData[0][1] = t;
		Map.TileData[31][0] = t;
		Map.TileData[31][19] = t;
		Map.TileData[0][19] = t;

		Map.updateVertices();

		sf::View view( { 0,0,128,96 } );
		con::Global.GameWindow.setView( view );

		MessageAr.display( "Hello, World!", sf::seconds( 0.2f ) );
	}

	void onUpdate()
	{
		auto& input = con::Global.Input;
		auto& v = Map.MapView;
		auto dt = con::Global.FrameTime.asSeconds();

		if ( input.isDown( con::KeyboardKey::A ) )
			v.move( 2, 0 );
		if ( input.isDown( con::KeyboardKey::D ) )
			v.move( -2, 0 );
		if ( input.isDown( con::KeyboardKey::S ) )
			v.move( 0, -2 );
		if ( input.isDown( con::KeyboardKey::W ) )
			v.move( 0, 2 );

	}
};