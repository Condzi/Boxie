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

		Map.TileData.reset( {50, 50 } );
		Tile t;
		t.TextureIndex = 1;
		Map.TileData[1][1] = t;

		Map.TileData[3][1].OnIntersectionBegin = [&]( Tile&, con::Entity& e) {
			MessageAr.display( "Sixteen letters!", MessageArea::DisplaySpeed::Normal );
		};

		Map.TileData[2][1].OnIntersectionEnd = [&]( Tile&, con::Entity& e ) {
			MessageAr.display( "Sixteen letters!", MessageArea::DisplaySpeed::Fast );
		};

		Map.TileData[3][2].TextureIndex = 1;

		Map.updateVertices();

		sf::View view( { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT } );
		con::Global.GameWindow.setView( view );

		addSystem<MovementDispatcher>( 0 );
		auto& p = spawn<Player>();
		p.position = { 3,3 };
		p.tileMap = &Map;
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