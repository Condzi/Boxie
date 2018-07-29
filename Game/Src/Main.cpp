/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "GameScene.hpp"

int main()
{
	con::Global.SceneStack.registerScene<GameScene>( static_cast<int16_t>( SceneID::Game ) );

	con::Global.SceneStack.push( static_cast<int16_t>( SceneID::Game ) );

	con::Global.Game.run();
}