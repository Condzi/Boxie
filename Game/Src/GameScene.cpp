/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "GameScene.hpp"

void GameScene::onPush()
{
	Map.TilesTexture = &con::Global.Assets.Texture.get( "tiles_texture" );

	Map.TileData.reset( { 50, 50 } );
	Tile t;
	t.TextureIndex = 1;
	Map.TileData[1][1] = t;


	Map.TileData[3][1].OnIntersectionBegin = [&]( Tile&, con::Entity& e ) {
		Messenger.writeNew().setDisplaySpeed( MessageWriter::WriteSpeed::Normal ).setSound( "letter_normal" ).setText(
			"HEY |(255 0 0){BOXIE}!||COME CLOSER!" );
	};

	Map.TileData[2][1].OnIntersectionEnd = [&]( Tile&, con::Entity& e ) {
		Messenger.writeNew().setDisplaySpeed( MessageWriter::WriteSpeed::Fast ).setSound( "letter_fast" ).setText(
			"WANT |(0 255 255){DIAMONDS}?||GO TO |(255 0 0){WENDY}." );
	};

	Map.TileData[3][2].TextureIndex = 1;

	Map.updateVertices();

	sf::View view( { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT } );
	con::Global.GameWindow.setView( view );

	addSystem<MovementDispatcher>( 0 );
	spawn<Player>( Map, Vec2f{ 3,3 } );
}

void GameScene::onUpdate()
{
	con::Global.GameWindow.setTitle( con::ConvertTo<std::string>( 1 / con::Global.FrameTime.asSeconds() ) );

	auto& input = con::Global.Input;

	if ( input.isDown( con::KeyboardKey::Space ) ) {
		if ( !Messenger.isDoneDisplayingLine() )
			Messenger.displayAll();
		else
			Messenger.skip();
	}
}
