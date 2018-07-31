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

	MessageArea()
	{
		displayedText.setFont( con::Global.Assets.BitmapFonts.getDefault() );
	}

	void display( const std::string& textToDisplay_, DisplaySpeed displaySpeed_ )
	{
		clear();
		displaySpeed = displaySpeed_;
		timeSinceLastDisplay = displaySpeedToTime( displaySpeed );
		displayedText.setString( textToDisplay_ );
		displayedText.setColors( sf::Color::Transparent );
		lettersColors.resize( textToDisplay_.size(), sf::Color( 200, 200, 200 ) );
	}

	void setLettersColors( sf::Color color, size_t pos, size_t count = 1 )
	{
		auto beg = lettersColors.begin() + pos;
		auto end = beg + count;;
		std::fill( beg, end, color );
	}

	void displayAll()
	{
		for ( size_t i = 0; i < lettersColors.size(); i++ )
			if ( displayedText.getColor( i ) != lettersColors.at( i ) )
				displayedText.setColor( lettersColors.at( i ), i );
	}

	void clear()
	{
		displayedText.setString( "" );
		lettersColors.clear();
	}

	bool isDoneDisplaying()
	{
		return lettersColors.empty() ||
			displayedText.getColor( displayedText.getString().size() - 1 ) == lettersColors.at( displayedText.getString().size() - 1 );
	}

private:
	std::vector<sf::Color> lettersColors;
	con::BitmapText displayedText;
	sf::Time timeSinceLastDisplay;
	DisplaySpeed displaySpeed;

	void update() override
	{
		if ( isDoneDisplaying() )
			return;

		timeSinceLastDisplay -= con::Global.FrameTime;
		if ( timeSinceLastDisplay.asSeconds() < 0 ) {
			timeSinceLastDisplay = displaySpeedToTime( displaySpeed );

			// Not the optimal way, but for 16 chars will do the job.
			// It may be overshoot with additional counting variable, that count how many chars are displayed now.
			for ( size_t i = 0; i < lettersColors.size(); i++ )
				if ( displayedText.getColor( i ) != lettersColors.at( i ) ) {
					displayedText.setColor( lettersColors.at( i ), i );
					break;
				}

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