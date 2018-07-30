/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

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
};