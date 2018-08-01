/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "MessageWriter.hpp"
#include "MessageViewer.hpp"

MessageWriter::MessageWriter( MessageViewer & messageViewer_ ) :
	messageViewer( messageViewer_ )
{}

MessageWriter& MessageWriter::setText( const std::string & text )
{
	messageViewer.textData = getFormatedStringData( text );
	messageViewer.textToDisplay.setString( *messageViewer.textData.linesToDisplay.begin() );
	messageViewer.textToDisplay.setColors( sf::Color::Transparent );

	return *this;
}

MessageWriter& MessageWriter::setDisplaySpeed( WriteSpeed writeSpeed )
{
	messageViewer.displaySpeed = convertWriteSpeedToTime( writeSpeed );
	return *this;
}

MessageWriter& MessageWriter::setSound( const std::string & soundName )
{
	messageViewer.soundName = soundName;
	return *this;
}

MessageWriter::FormatedStringData MessageWriter::getFormatedStringData( const std::string & org )
{
	FormatedStringData data;
	auto& linesText = data.linesToDisplay;
	auto& colors = data.linesColorData;

	auto copy = org;
	linesText = formatNewLines( copy );
	colors.resize( linesText.size() );

	for ( size_t i = 0; i < linesText.size(); i++ )
		colors.at( i ) = formatColors( linesText.at( i ) );

	return data;
}

std::vector<std::string> MessageWriter::formatNewLines( std::string & str )
{
	std::vector<std::string> lines;

	auto pos = str.find( "||" );
	for ( ; pos != std::string::npos; pos = str.find( "||" ) ) {
		str.erase( pos, 2 );
		lines.emplace_back( str.substr( 0, pos ) );
		str = str.substr( pos );
	}

	lines.emplace_back( str );

	return lines;
}

std::vector<sf::Color> MessageWriter::formatColors( std::string& str )
{
	std::vector<sf::Color> colors;
	colors.resize( str.size(), DEFAULT_TEXT_COLOR );

	for ( auto colorInfoBegin = str.find_first_of( "|(" ); colorInfoBegin != std::string::npos; colorInfoBegin = str.find_first_of( "|(" ) ) {
		auto colorInfoEnd = str.find_first_of( ")", colorInfoBegin );
		auto textAreaBegin = str.find_first_of( "{", colorInfoEnd );
		auto textAreaEnd = str.find_first_of( "}", textAreaBegin );

		auto color = formatColorInfo( str.substr( colorInfoBegin, colorInfoEnd - colorInfoBegin ) );
		std::fill( colors.begin() + textAreaBegin + 1, colors.begin() + textAreaEnd, color );

		auto diff = textAreaBegin + 1 - colorInfoBegin;

		colors.erase( colors.begin() + colorInfoBegin, colors.begin() + textAreaBegin + 1 );
		// without () - vector + iterator offst out of range exception
		colors.erase( colors.begin() + ( textAreaEnd - diff ) );

		str.erase( str.begin() + colorInfoBegin, str.begin() + textAreaBegin + 1 );
		str.erase( str.begin() + ( textAreaEnd - diff ) );
	}

	return colors;
}

sf::Color MessageWriter::formatColorInfo( std::string str )
{
	uint8_t r, g, b;
	// Always 2 because |(123 < starts at 2 index!
	auto pos = 2;
	auto space = str.find_first_of( ' ', pos );
	r = con::ConvertTo<uint8_t>( str.substr( pos, space - pos ) );

	pos = str.find_first_not_of( ' ', space );
	space = str.find_first_of( ' ', pos );
	g = con::ConvertTo<uint8_t>( str.substr( pos, space - pos ) );

	pos = str.find_first_not_of( ' ', space );
	space = str.find_first_of( ' ', pos );
	if ( space == std::string::npos )
		space = str.size();
	b = con::ConvertTo<uint8_t>( str.substr( pos, space - pos ) );

	return { r,g,b };
}

sf::Time MessageWriter::convertWriteSpeedToTime( WriteSpeed ws )
{
	return sf::milliseconds( static_cast<int32_t>( ws ) );
}
