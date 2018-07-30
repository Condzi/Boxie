/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TileMap.hpp"
#include "MessageArea.hpp"
#include "MovementDispatcher.hpp"
#include "Player.hpp"

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

		sf::View view( { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT } );
		con::Global.GameWindow.setView( view );

		MessageAr.display( "Hello, I'm Boxie", sf::seconds( 0.2f ) );

		addSystem<MovementDispatcher>( 0 );
		spawn<Player>().position = { 3,3 };
	}

	void onUpdate()
	{
		auto& input = con::Global.Input;

		if ( input.isDown( con::KeyboardKey::Space ) ) {
			if ( MessageAr.isDoneDisplaying() )
				MessageAr.clear();
			else
				MessageAr.displayAll();
		}
	}
};