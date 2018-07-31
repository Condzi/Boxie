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
	sf::Sprite Sprite;
	TileMap& LevelMap;

	Player( TileMap& LevelMap_, const Vec2f& position_ );

	void onSpawn() override;
	void onUpdate() override;

private:
	void updateSpritePositionAndViewCenter();
	void checkInput();

	void render( sf::RenderWindow& window ) override;
};