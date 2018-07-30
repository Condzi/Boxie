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
	size_t charsAlreadyDisplayed = 0;

	MessageArea()
	{
		text.setFont( con::Global.Assets.BitmapFonts.getDefault() );
		text.setColor( { 200,200,200 } );
	}

	void display( const std::string& textToDisplay_, const sf::Time& displayingSpeed_ )
	{
		// Additional space is needed to clear after all characters ale displayed, otherwise
		// last one could be truncated
		textToDisplay = textToDisplay_ + " ";
		displayingSpeed = displayingSpeed_;
		timeSinceLastDisplay = displayingSpeed;
	}

	void displayAll()
	{
		charsAlreadyDisplayed = textToDisplay.size() - 1;
		text.setString( textToDisplay.substr( 0, charsAlreadyDisplayed - 1 ) );
	}

	void clear()
	{
		textToDisplay.clear();
		text.setString( "" );
		charsAlreadyDisplayed = 0;
	}

	bool isDoneDisplaying()
	{
		return charsAlreadyDisplayed == textToDisplay.size();
	}

private:
	void update() override
	{
		if ( isDoneDisplaying() )
			return;

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
		auto textView = currentView;
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