/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "LoaderScene.hpp"

void LoaderScene::onPush()
{
	validateSettings();
	loadTextures();
	loadFont();
	loadSound();

	con::Global.SceneStack.pop();
	con::Global.SceneStack.push( "Game" );
}

void LoaderScene::validateSettings()
{
	auto& settings = con::Global.Assets.Settings;

	settings.setValue( "WINDOW", "WIDTH", "1024" );
	settings.setValue( "WINDOW", "HEIGHT", "768" );
	updateWindow();

	// Other settings here...
}

void LoaderScene::updateWindow()
{
	auto& settings = con::Global.Assets.Settings;
	auto prevSize = con::Global.GameWindow.getSize();
	// Resize window, because it's created in wrong size by default.
	Vec2u winSize{ con::ConvertTo<uint32_t>( settings.getValue( "WINDOW", "WIDTH" ).value() ), con::ConvertTo<uint32_t>( settings.getValue( "WINDOW", "HEIGHT" ).value() ) };
	con::Global.GameWindow.setSize( winSize );
	// Fix position after resizing.
	if ( prevSize != winSize ) {
		auto winPos = con::Global.GameWindow.getPosition();
		con::Global.GameWindow.setPosition( Vec2i( winPos.x + prevSize.x * 0.5 - winSize.x * 0.5, winPos.y ) );
	}
}

void LoaderScene::loadTextures()
{
	auto& textures = con::Global.Assets.Texture;

	textures.load( "data/tiles_texture.png", "tiles_texture" );
	textures.load( "data/entities_texture.png", "entities_texture" );
}

void LoaderScene::loadFont()
{
	auto& bitmapFonts = con::Global.Assets.BitmapFonts;

	// Nasty way of setting the default font.
	con::BitmapFont font;
	font.loadFromFile( "data/vincent.png" );
	font.setGlyphSize( { 8,8 } );
	bitmapFonts._setDefault( std::move( font ) );
}

void LoaderScene::loadSound()
{
	auto& sounds = con::Global.Assets.Sound;
	sounds.load( "data/letter_fast.wav", "letter_fast" );
	sounds.load( "data/letter_normal.wav", "letter_normal" );
}
