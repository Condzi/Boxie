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

	for ( size_t i = 0; i < linesText.size(); i++ )
		colors.at( i ) = formatColors( linesText.at( i ) );

	return data;
}

std::vector<std::string> MessageWriter::formatNewLines( std::string & str )
{
	std::vector<std::string> lines;

	for ( auto pos = str.find_first_of( "||" ); pos != std::string::npos; ) {
		str.erase( pos, 2 );
		lines.emplace_back( str.substr( 0, pos ) );
		str.erase( 0, pos );
	}

	return lines;
}

std::vector<sf::Color> MessageWriter::formatColors( std::string& str )
{
	std::vector<sf::Color> colors;
	colors.resize( str.size(), DEFAULT_TEXT_COLOR );

	for ( auto colorInfoBegin = str.find_first_of( "|(" ); colorInfoBegin != std::string::npos; ) {
		auto colorInfoEnd = str.find_first_of( ")", colorInfoBegin );
		auto textAreaBegin = str.find_first_not_of( "{", colorInfoEnd );
		auto textAreaEnd = str.find_first_of( "}", textAreaBegin );

		auto color = formatColorInfo( str.substr( colorInfoBegin, colorInfoEnd - colorInfoBegin ));
		std::fill( colors.begin() + textAreaBegin, colors.begin() + textAreaEnd - 1, color );

		colors.erase( colors.begin() + colorInfoBegin, colors.begin() + textAreaBegin );
		colors.erase( colors.begin() + textAreaEnd );

		str.erase( str.begin() + colorInfoBegin, str.begin() + textAreaBegin );
		str.erase( str.begin() + textAreaEnd );
	}

	return colors;
}

sf::Color MessageWriter::formatColorInfo( std::string str )
{
	uint8_t r, g, b;
	auto pos = str.find_first_not_of( ' ' );
	auto space = str.find_first_of( ' ', pos );
	r = con::ConvertTo<uint8_t>( str.substr( pos, space - pos ) );
	
	pos = str.find_first_not_of( ' ' );
	space = str.find_first_of( ' ', pos );
	g = con::ConvertTo<uint8_t>( str.substr( pos, space - pos ) );
	
	pos = str.find_first_not_of( ' ' );
	space = str.find_first_of( ' ', pos );
	if ( space == std::string::npos )
		space = str.size() - 1;
	b = con::ConvertTo<uint8_t>( str.substr( pos, space - pos ) );

	return { r,g,b };
}

sf::Time MessageWriter::convertWriteSpeedToTime( WriteSpeed ws )
{
	return sf::milliseconds( static_cast<int32_t>( ws ) );
}
