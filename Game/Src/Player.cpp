/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "Player.hpp"

Player::Player( TileMap & LevelMap_, const Vec2f & position_ ) :
	LevelMap( LevelMap_ )
{
	position = position_;
	OccupiedTile = &LevelMap.TileData.at( static_cast<Vec2u>( position ) );
}

void Player::onSpawn()
{
	tag = "Player";
	setDrawLayer( static_cast<int16_t>( DrawLayer::Entity ) );
	Sprite.setTexture( con::Global.Assets.Texture.get( "entities_texture" ) );
	Sprite.setTextureRect( { 0,0,4,4 } );
}

void Player::onUpdate()
{
	updateSpritePositionAndViewCenter();
	checkInput();
}

void Player::updateSpritePositionAndViewCenter()
{
	const auto TILE_SIZE = static_cast<float32_t>( TileMap::TILE_SIZE );
	auto pixelPos = position * TILE_SIZE;
	Sprite.setPosition( pixelPos );

	// Center of sprite 
	auto center = pixelPos + Vec2f{ TILE_SIZE/2, TILE_SIZE/2 };
	auto viewAreaHalfX = TileMap::VIEW_AREA.x / 2;
	auto viewAreaHalfY = TileMap::VIEW_AREA.y / 2;

	auto mapSizeX = LevelMap.TileData.size2D().x * TileMap::TILE_SIZE;
	auto mapSizeY = LevelMap.TileData.size2D().y * TileMap::TILE_SIZE;

	if ( center.x - viewAreaHalfX < 0 )
		center.x = viewAreaHalfX;
	if ( center.x + viewAreaHalfX > mapSizeX )
		center.x = mapSizeX - viewAreaHalfX;
	if ( center.y - viewAreaHalfY < 0 )
		center.y = viewAreaHalfY;
	if ( center.y + viewAreaHalfY > mapSizeY )
		center.y = mapSizeY - viewAreaHalfY;

	LevelMap.View.setCenter( center );
}

void Player::checkInput()
{
	if ( MoveDirection != Direction::None )
		return;

	auto& input = con::Global.Input;

	if ( input.isHeld( sf::Keyboard::A ) )
		MoveDirection = Direction::Left;
	if ( input.isHeld( sf::Keyboard::D ) )
		MoveDirection = Direction::Right;
	if ( input.isHeld( sf::Keyboard::W ) )
		MoveDirection = Direction::Up;
	if ( input.isHeld( sf::Keyboard::S ) )
		MoveDirection = Direction::Down;
}

void Player::render( sf::RenderWindow & window )
{
	auto defaultView = window.getView();
	window.setView( LevelMap.View );
	window.draw( Sprite );
	window.setView( defaultView );
}
