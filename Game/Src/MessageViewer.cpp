/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "MessageViewer.hpp"

MessageViewer::MessageViewer()
{
	textToDisplay.setFont( con::Global.Assets.BitmapFonts.getDefault() );
}

MessageWriter& MessageViewer::writeNew()
{
	reset();

	return writer;
}

void MessageViewer::displayAll()
{
	const auto& colorData = textData.linesColorData.at( currentViewingLine );

	for ( ; currentViewingLetter < colorData.size(); currentViewingLetter++ )
		textToDisplay.setColor( colorData.at( currentViewingLetter ), currentViewingLetter );
}

void MessageViewer::skip()
{
	if ( isDoneDisplayingAll() )
		reset();
	else if ( isDoneDisplayingLine() )
		if ( !textData.linesToDisplay.empty() )
			nextLine();
}

bool MessageViewer::isDoneDisplayingLine() const
{
	return textData.linesToDisplay.empty() || textData.linesToDisplay.at( currentViewingLine ).empty() ||
		currentViewingLetter == textData.linesToDisplay.at( currentViewingLine ).size();
}

bool MessageViewer::isDoneDisplayingAll() const
{
	return isDoneDisplayingLine() && currentViewingLine == textData.linesToDisplay.size() - 1;
}

void MessageViewer::reset()
{
	timeSinceLastDisplay = sf::Time::Zero;
	displaySpeed = sf::Time::Zero;
	textToDisplay.setString( "" );
	textData = {};
	currentViewingLine = currentViewingLetter = 0;
	soundName = "";
}

void MessageViewer::nextLine()
{
	currentViewingLetter = 0;
	currentViewingLine++;
	textToDisplay.setString( textData.linesToDisplay.at( currentViewingLine ) );
	textToDisplay.setColors( sf::Color::Transparent );
}

void MessageViewer::update()
{
	if ( isDoneDisplayingAll() || isDoneDisplayingLine() )
		return;

	timeSinceLastDisplay -= con::Global.FrameTime;

	if ( timeSinceLastDisplay < sf::Time::Zero ) {
		timeSinceLastDisplay = displaySpeed;
		textToDisplay.setColor( textData.linesColorData.at( currentViewingLine ).at( currentViewingLetter ), currentViewingLetter );
		currentViewingLetter++;

		con::Global.Assets.Sound.play( soundName );
	}
}

void MessageViewer::render( sf::RenderWindow & window )
{
	auto currentView = window.getView();
	auto textView = currentView;
	textView.setViewport( VIEWPORT );

	window.setView( textView );
	window.draw( textToDisplay );
	window.setView( currentView );
}

int8_t MessageViewer::getUpdatePriority() const
{
	return 1;
}
