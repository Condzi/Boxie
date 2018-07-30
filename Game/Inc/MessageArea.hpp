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
	enum class DisplaySpeed
	{
		Fast, Normal, Slow
	};

	inline static const RectF VIEWPORT{ 0, 0, 1, 1 };
	inline static constexpr float32_t SPEED_FAST = 0.029f;
	inline static constexpr float32_t SPEED_NORMAL = 0.06f;
	inline static constexpr float32_t SPEED_SLOW = 0.1f;

	con::BitmapText displayedText;
	std::string textString;
	sf::Time timeSinceLastDisplay;
	size_t charsAlreadyDisplayed = 0;

	MessageArea()
	{
		displayedText.setFont( con::Global.Assets.BitmapFonts.getDefault() );
		displayedText.setColor( { 200,200,200 } );
	}

	void display( const std::string& textToDisplay_, DisplaySpeed displaySpeed_ )
	{
		clear();
		// Additional space is needed to clear after all characters ale displayed, otherwise
		// last one could be truncated
		textString = textToDisplay_ + " ";
		displaySpeed = displaySpeed_;
		timeSinceLastDisplay = displaySpeedToTime( displaySpeed );
	}

	void displayAll()
	{
		charsAlreadyDisplayed = textString.size() - 1;
		displayedText.setString( textString.substr( 0, charsAlreadyDisplayed - 1 ) );
	}

	void clear()
	{
		textString.clear();
		displayedText.setString( "" );
		charsAlreadyDisplayed = 0;
	}

	bool isDoneDisplaying()
	{
		return charsAlreadyDisplayed == textString.size();
	}

private:
	DisplaySpeed displaySpeed;

	void update() override
	{
		if ( isDoneDisplaying() )
			return;

		timeSinceLastDisplay -= con::Global.FrameTime;
		if ( timeSinceLastDisplay.asSeconds() < 0 ) {
			if ( charsAlreadyDisplayed == textString.size() )
				return;
			timeSinceLastDisplay = displaySpeedToTime( displaySpeed );
			charsAlreadyDisplayed++;
			displayedText.setString( textString.substr( 0, charsAlreadyDisplayed ) );

			if ( displaySpeed == DisplaySpeed::Fast )
				con::Global.Assets.Sound.play( "letter_fast" );
			if ( displaySpeed == DisplaySpeed::Normal )
				con::Global.Assets.Sound.play( "letter_normal" );
			if ( displaySpeed == DisplaySpeed::Slow )
				con::Global.Assets.Sound.play( "letter_slow" );
		}
	}

	void render( sf::RenderWindow& window ) override
	{
		auto currentView = window.getView();
		auto textView = currentView;
		textView.setViewport( VIEWPORT );

		window.setView( textView );
		window.draw( displayedText );
		window.setView( currentView );
	}

	int8_t getUpdatePriority() const override
	{
		return 1;
	}

	sf::Time displaySpeedToTime( DisplaySpeed d )
	{
		switch ( d ) {
		case DisplaySpeed::Fast: return sf::seconds( SPEED_FAST );
		case DisplaySpeed::Normal: return sf::seconds( SPEED_NORMAL );
		case DisplaySpeed::Slow: return sf::seconds( SPEED_SLOW );
		}
	}

};