/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

class GameScene final :
	public con::Scene
{
public:
	con::BitmapText text;
	con::RectangleShape testShape;

	void onPush() override
	{
		tag = "Game";
		text = con::BitmapText( "HELLO, I'M BOXIE", con::Global.Assets.BitmapFonts.getDefault(), { 0,0 }, sf::Color( 200,200,200 ) );
		testShape.setPosition( 1, 8 );
		testShape.setSize( { 2+2, 2+2 } );
		testShape.setFillColor( sf::Color( 175, 50, 50 ) );

		sf::View view = con::Global.GameWindow.getDefaultView();
		view.setCenter( 64, 48 );
		view.zoom( 1/8.f);
		con::Global.GameWindow.setView( view );
	}
};