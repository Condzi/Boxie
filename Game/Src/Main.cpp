/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "LoaderScene.hpp"
#include "GameScene.hpp"

int main()
{
	con::Global.SceneStack.registerScene<GameScene>( static_cast<int16_t>( SceneID::Game ) );
	con::Global.SceneStack.registerScene<LoaderScene>( static_cast<int16_t>( SceneID::Loader ) );


	con::Global.SceneStack.push( static_cast<int16_t>( SceneID::Loader ) );

	con::Global.Game.run();
}