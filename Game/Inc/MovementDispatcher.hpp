/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "MovableEntity.hpp"

class MovementDispatcher final :
	public con::System
{
public:
	void onUpdate() override;

private:
	class GameScene* gameScene = nullptr;
	class TileMap* tileMap = nullptr;

	void trySetGameScene();
	void updateByVelocity( MovableEntity& entity );
	void tryStartMoving( MovableEntity& entity );
	void calcVelocity( MovableEntity& entity );
	bool checkIfArrived( MovableEntity& entity );
	void handleArrivingOnTile( MovableEntity& entity );
};