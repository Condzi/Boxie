/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

class MessageArea final :
	public con::IDrawable,
	public con::IUpdatable
{
public:
	inline static const RectF VIEWPORT{ 0, 0, 1, 1 };
	con::BitmapText text;
	std::string textToDisplay;
	sf::Time displayingSpeed;
	sf::Time timeSinceLastDisplay;
	size_t charsAlreadyDisplayed = 1;

	MessageArea()
	{
		text.setFont( con::Global.Assets.BitmapFonts.getDefault() );
	}

	void display( const std::string& textToDisplay_, const sf::Time& displayingSpeed_ )
	{
		textToDisplay = textToDisplay_;
		displayingSpeed = displayingSpeed_;
		timeSinceLastDisplay = displayingSpeed;
	}

	void clear()
	{
		textToDisplay.clear();
		charsAlreadyDisplayed = 1;
	}

	bool isDisplayingSomething()
	{
		return !textToDisplay.empty();
	}

private:
	void update() override
	{
		timeSinceLastDisplay -= con::Global.FrameTime;
		if ( timeSinceLastDisplay.asSeconds() < 0 ) {
			if ( charsAlreadyDisplayed == textToDisplay.size() )
				return;
			timeSinceLastDisplay = displayingSpeed;
			charsAlreadyDisplayed++;
			text.setString( textToDisplay.substr( 0, charsAlreadyDisplayed ) );
		}
	}

	void render( sf::RenderWindow& window ) override
	{
		auto currentView = window.getView();
		sf::View textView( { 0,0,128,96 } );
		textView.setViewport( VIEWPORT );

		window.setView( textView );
		window.draw( text );
		window.setView( currentView );
	}

	int8_t getUpdatePriority() const override
	{
		return 1;
	}

};