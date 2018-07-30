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
	TileMap* tileMap;

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

		updatePositions();

		if ( MoveDirection != Direction::None )
			return;

		if ( input.isHeld( sf::Keyboard::A ) )
			MoveDirection = Direction::Left;
		if ( input.isHeld( sf::Keyboard::D ) )
			MoveDirection = Direction::Right;
		if ( input.isHeld( sf::Keyboard::W ) )
			MoveDirection = Direction::Up;
		if ( input.isHeld( sf::Keyboard::S ) )
			MoveDirection = Direction::Down;
	}

private:
	void updatePositions()
	{
		auto pixelPos = position * static_cast<float32_t>( TileMap::TILE_SIZE );
		sprite.setPosition( pixelPos );

		auto center = pixelPos;
		auto viewAreaHalfX = TileMap::VIEW_AREA.x / 2;
		auto viewAreaHalfY = TileMap::VIEW_AREA.y / 2;

		auto mapSizeX = tileMap->TileData.size2D().x * TileMap::TILE_SIZE;
		auto mapSizeY = tileMap->TileData.size2D().y * TileMap::TILE_SIZE;

		if ( center.x - viewAreaHalfX <= 0 )
			center.x = viewAreaHalfX;
		if ( center.x + viewAreaHalfX >= mapSizeX )
			center.x = mapSizeX - viewAreaHalfX;
		if ( center.y - viewAreaHalfY <= 0 )
			center.y = viewAreaHalfY;
		if ( center.y + viewAreaHalfY >= mapSizeY )
			center.y = mapSizeY - viewAreaHalfY;

		tileMap->View.setCenter( center );
	}

	void render( sf::RenderWindow& window ) override
	{
		auto defaultView = window.getView();
		window.setView( tileMap->View );
		window.draw( sprite );
		window.setView( defaultView );
	}
};