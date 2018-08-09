/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"

#include "LoaderScene.hpp"
#include "GameScene.hpp"

void registerScenes()
{
	con::Global.SceneStack.registerScene<GameScene>( "Game" );
	con::Global.SceneStack.registerScene<LoaderScene>( "Loader" );

	con::Global.SceneStack.push( "Loader" );
}

int main()
{
	registerScenes();

	con::Global.Game.run();
}