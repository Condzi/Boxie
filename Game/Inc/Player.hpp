/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "MovableEntity.hpp"
// For view data
#include "TileMap.hpp"

class Player final :
	public MovableEntity,
	public con::IDrawable
{
public:
	sf::Sprite sprite;

	void onSpawn() override
	{
		tag = "Player";
		setDrawLayer( static_cast<int16_t>( DrawLayer::Entity ) );
		sprite.setTexture( con::Global.Assets.Texture.get( "entities_texture" ) );
		sprite.setTextureRect( { 0,0,4,4 } );
	}

	void onUpdate() override
	{
		auto& input = con::Global.Input;

		sprite.setPosition( position * static_cast<float32_t>( TileMap::TILE_SIZE ) );

		if ( MoveDirection != MovementDirection::None )
			return;

		if ( input.isDown( sf::Keyboard::A ) )
			MoveDirection = MovementDirection::Left;
		if ( input.isDown( sf::Keyboard::D ) )
			MoveDirection = MovementDirection::Right;
		if ( input.isDown( sf::Keyboard::W ) )
			MoveDirection = MovementDirection::Up;
		if ( input.isDown( sf::Keyboard::S ) )
			MoveDirection = MovementDirection::Down;
	}

private:
	void render( sf::RenderWindow& window )
	{
		sf::View v{ { 0,0, TileMap::VIEW_AREA.x, TileMap::VIEW_AREA.y } };
		v.setViewport( TileMap::VIEWPORT );

		auto defaultView = window.getView();
		window.setView( v );
		window.draw( sprite );
		window.setView( defaultView );
	}
};