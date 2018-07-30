/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "MovementDispatcher.hpp"
#include "GameScene.hpp"
#include "MovableEntity.hpp"

static Vec2f roundF( const Vec2f& p )
{
	return Vec2f( std::roundf( p.x ), std::roundf( p.y ) );
}

static Vec2f movementDirToVectorDir( MovableEntity::Direction dir )
{
	switch ( dir ) {
	case MovableEntity::Direction::Left: return{ -1,0 };
	case MovableEntity::Direction::Right: return{ 1,0 };
	case MovableEntity::Direction::Up: return{ 0,-1 };
	case MovableEntity::Direction::Down: return{ 0,1 };
	}
	con::Global.Logger.log( con::LogPriority::Warning, "Somehow Direction::None is here?" );
	DebugBreak();
}

void MovementDispatcher::onUpdate()
{
	trySetGameScene();
	if ( !gameScene ) {
		DebugBreak();
		return;
	}

	auto dt = con::Global.FrameTime.asSeconds();

	gameScene->forEachEntityOfType<MovableEntity>( [&]( MovableEntity& entity ) {
		if ( entity.MoveDirection == MovableEntity::Direction::None )
			return;

		updateByVelocity( entity );
		if ( checkIfArrived( entity ) )
			handleArrivingOnTile( entity );
		tryStartMoving( entity );
	} );
}

void MovementDispatcher::trySetGameScene()
{
	if ( !gameScene ) {
		gameScene = dynamic_cast<GameScene*>( parentScene );
		tileMap = &gameScene->Map;
	}
}

void MovementDispatcher::updateByVelocity( MovableEntity& entity )
{
	auto dt = con::Global.FrameTime.asSeconds();

	if ( entity.Velocity != Vec2f{ 0,0 } )
		entity.position += entity.Velocity * dt;
}

void MovementDispatcher::tryStartMoving( MovableEntity& entity )
{
	using Dir = MovableEntity::Direction;
	auto& entityDir = entity.MoveDirection;
	auto& pos = entity.position;
	// @ToDo: Precalculate velocity? It's always the same value for same time.
	auto& vel = entity.Velocity;

	auto getTile = [&]( const Vec2f& point ) -> Tile& {
		return tileMap->TileData.at( static_cast<Vec2u>( point ) );
	};

	auto isObstacle = [&]( const Vec2f& point ) {
		auto begin = static_cast<uint8_t>( TileID::WALL_BEGIN );
		auto end = static_cast<uint8_t>( TileID::WALL_END );

		const auto& tile = getTile( point );
		auto idx = tile.TextureIndex;

		return ( idx >= begin && idx < end );
	};

	// If has movement dir and is standing => it requested movement in this frame
	if ( entityDir != Dir::None && vel.x == 0 && vel.y == 0 ) {
		Vec2f tileToCheckOffset = movementDirToVectorDir( entityDir );

		if ( isObstacle( pos  + tileToCheckOffset ) ) {
			entityDir = Dir::None;
			return;
		}
		if ( auto entityOnTile = getTile( pos + tileToCheckOffset ).EntityOnTop; entityOnTile ) {
			if ( auto casted = dynamic_cast<MovableEntity*>( entityOnTile ); casted )
				casted->onEntityApproach( entity );
		} else {
			auto& tile = getTile( pos + tileToCheckOffset );
			tile.OnIntersectionBegin( tile, entity );
			calcVelocity( entity );
		}
	}
}

void MovementDispatcher::calcVelocity( MovableEntity& entity )
{
	auto& v = entity.Velocity;
	auto s = tileMap->TILE_SIZE;
	auto t = entity.TransisionTime.asSeconds();

	v = movementDirToVectorDir( entity.MoveDirection );
	if ( t == 0 ) {
		con::Global.Logger.log( con::LogPriority::Warning, "Transiion Time can't be 0" );
		DebugBreak();
	}

	// *= because there will be 0 in direction so it'll be skipped
	v *= s / t;
}

bool MovementDispatcher::checkIfArrived( MovableEntity& entity )
{
	auto occupiedTilePos = static_cast<Vec2f>( entity.OccupiedTile->PositionOnMap );
	auto desiredTilePos = movementDirToVectorDir( entity.MoveDirection ) + occupiedTilePos;
	auto desiredPos = desiredTilePos * static_cast<float32_t>( TileMap::TILE_SIZE );
	auto pos = entity.position * static_cast<float32_t>( TileMap::TILE_SIZE );

	switch ( entity.MoveDirection ) {
	case MovableEntity::Direction::Left: return pos.x <= desiredPos.x;
	case MovableEntity::Direction::Right: return pos.x >= desiredPos.x;
	case MovableEntity::Direction::Up: return pos.y <= desiredPos.y;
	case MovableEntity::Direction::Down: return pos.y >= desiredPos.y;
	}
}

void MovementDispatcher::handleArrivingOnTile( MovableEntity& entity )
{
	entity.Velocity = {};
	entity.MoveDirection = MovableEntity::Direction::None;
	entity.position = roundF( entity.position );

	auto& tile = tileMap->TileData.at( static_cast<Vec2u>( entity.position ) );
	entity.OccupiedTile->EntityOnTop = nullptr;
	entity.OccupiedTile = &tile;
	tile.EntityOnTop = &entity;

	tile.OnIntersectionEnd( tile, entity );
}
