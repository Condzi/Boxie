/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

class MovableEntity :
	public con::Entity
{
public:
	sf::Time TransisionTime = sf::seconds( 0.5f );
	enum class MovementDirection
	{
		None, Left, Right, Up, Down
	} MoveDirection;
	// Shouldn't be set manually. It determinates how fast should move entity to go to
	// the tile.
	Vec2f Velocity{};
	class Tile* OccupiedTile = nullptr;
};