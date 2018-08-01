/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "TileMap.hpp"
#include "MovementDispatcher.hpp"
#include "MessageViewer.hpp"
#include "Player.hpp"

class GameScene final :
	public con::Scene
{
public:
	TileMap Map;
	MessageViewer Messenger;

	void onPush() override;
	void onUpdate() override;
};