/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "MessageArea.hpp"

MessageArea::MessageArea()
{
	displayedText.setFont( con::Global.Assets.BitmapFonts.getDefault() );
}

void MessageArea::display( const std::string & textToDisplay_, DisplaySpeed displaySpeed_ )
{
	clear();
	displaySpeed = displaySpeed_;
	timeSinceLastDisplay = displaySpeedToTime( displaySpeed );
	displayedText.setString( textToDisplay_ );
	displayedText.setColors( sf::Color::Transparent );
	lettersColors.resize( textToDisplay_.size(), sf::Color( 200, 200, 200 ) );
}

void MessageArea::setLettersColors( sf::Color color, size_t pos, size_t count )
{
	auto beg = lettersColors.begin() + pos;
	auto end = beg + count;;
	std::fill( beg, end, color );
}

void MessageArea::displayAll()
{
	for ( size_t i = 0; i < lettersColors.size(); i++ )
		if ( displayedText.getColor( i ) != lettersColors.at( i ) )
			displayedText.setColor( lettersColors.at( i ), i );
}

void MessageArea::clear()
{
	displayedText.setString( "" );
	lettersColors.clear();
}

bool MessageArea::isDoneDisplaying() const
{
	return lettersColors.empty() ||
		displayedText.getColor( displayedText.getString().size() - 1 ) == lettersColors.at( displayedText.getString().size() - 1 );
}

void MessageArea::update()
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

void MessageArea::render( sf::RenderWindow & window )
{
	auto currentView = window.getView();
	auto textView = currentView;
	textView.setViewport( VIEWPORT );

	window.setView( textView );
	window.draw( displayedText );
	window.setView( currentView );
}

int8_t MessageArea::getUpdatePriority() const
{
	return 1;
}

sf::Time MessageArea::displaySpeedToTime( DisplaySpeed d )
{
	switch ( d ) {
	case DisplaySpeed::Fast: return sf::seconds( SPEED_FAST );
	case DisplaySpeed::Normal: return sf::seconds( SPEED_NORMAL );
	case DisplaySpeed::Slow: return sf::seconds( SPEED_SLOW );
	}
}
