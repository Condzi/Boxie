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

static Vec2f movementDirToVectorDir( MovableEntity::MovementDirection dir )
{
	switch ( dir ) {
	case MovableEntity::MovementDirection::Left: return{ -1,0 };
	case MovableEntity::MovementDirection::Right: return{ 1,0 };
	case MovableEntity::MovementDirection::Up: return{ 0,-1 };
	case MovableEntity::MovementDirection::Down: return{ 0,1 };
	}
	con::Global.Logger.log( con::LogPriority::Warning, "Somehow MovementDirection::None is here?" );
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

	gameScene->forEachEntityOfType<MovableEntity>( [&]( MovableEntity& e ) {
		if ( e.MoveDirection == MovableEntity::MovementDirection::None )
			return;

		updateByVelocity( e );
		tryStartMoving( e );

	} );
}

void MovementDispatcher::trySetGameScene()
{
	if ( !gameScene ) {
		gameScene = dynamic_cast<GameScene*>( parentScene );
		tileMap = &gameScene->Map;
	}
}

void MovementDispatcher::updateByVelocity( MovableEntity & entity )
{
	auto dt = con::Global.FrameTime.asSeconds();

	if ( entity.Velocity.x != 0 || entity.Velocity.y != 0 ) {
		entity.position += entity.Velocity * dt;
		if ( roundF( entity.position * 10.f ) / 10.f == roundF( entity.position ) ) {
			entity.Velocity.x = entity.Velocity.y = 0;
			entity.MoveDirection = MovableEntity::MovementDirection::None;
			entity.position = roundF( entity.position );
		}
	}
}

void MovementDispatcher::tryStartMoving( MovableEntity& entity )
{
	using Dir = MovableEntity::MovementDirection;
	auto& entityDir = entity.MoveDirection;
	auto& pos = entity.position;
	// @ToDo: Precalculate velocity? It's always the same value for same time.
	auto& vel = entity.Velocity;

	auto isObstacle = [&]( const Vec2f& point ) {
		auto begin = static_cast<uint8_t>( TileID::WALL_BEGIN );
		auto end = static_cast<uint8_t>( TileID::WALL_END );

		const auto& tile = tileMap->TileData.at( static_cast<Vec2u>( point ) );
		auto idx = tile.TextureIndex;

		return ( idx >= begin && idx < end ) || tile.EntityOnTop;
	};

	// If has movement dir and is standing => it requested movement in this frame
	if ( entityDir != Dir::None && vel.x == 0 && vel.y == 0 ) {
		Vec2f tileToCheckOffset = movementDirToVectorDir( entityDir );

		if ( isObstacle( pos  + tileToCheckOffset ) ) {
			entityDir = Dir::None;
			// @Debug only
			con::Global.Logger.log( con::LogPriority::Info, "Obstacle - can't move" );
			return;
		}

		calcVelocity( entity );
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
