/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

class MessageViewer;

// Helper class for MessageViewer for easier text displaying.
class MessageWriter final
{
public:
	struct FormatedStringData
	{
		std::vector<std::string> linesToDisplay;
		std::vector<std::vector<sf::Color>> linesColorData;
	};

	// Speed in milliseconds
	enum class WriteSpeed
	{
		Fast = 29, Normal = 60, Slow = 100
	};

	inline static const sf::Color DEFAULT_TEXT_COLOR{ 200,200,200 };

	MessageWriter( MessageViewer& messageViewer_ );

	// |(r g b){} - sets color of characters in {} to given rgb
	// || - cuts string 
	MessageWriter& setText( const std::string& text );
	MessageWriter& setDisplaySpeed( WriteSpeed writeSpeed );
	MessageWriter& setSound( const std::string& soundName );

private:
	MessageViewer& messageViewer;

	FormatedStringData getFormatedStringData( const std::string& org );
	std::vector<std::string> formatNewLines( std::string& str );
	std::vector<sf::Color> formatColors( std::string& str );
	sf::Color formatColorInfo( std::string str );
	sf::Time convertWriteSpeedToTime( WriteSpeed ws );
};