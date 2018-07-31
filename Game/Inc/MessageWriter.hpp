/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

class MessageViewer;

class MessageWriter final 
{
public:
	struct FormatedStringData
	{
		std::vector<std::string> linesToDisplay;
		std::vector<std::vector<sf::Color>> linesColorData;
	};

	MessageWriter( MessageViewer& messageViewer );

	enum class WriteSpeed
	{
		Fast, Normal, Slow
	};

	// Resets all info
	void reset();

	// |(r,g,b){} - sets color of characters in {} to given rgb
	// || - cuts string (auto-cut if string is longer than 16)
	MessageWriter& setText( const std::string& text );
	MessageWriter& setDisplaySpeed( WriteSpeed writeSpeed_ );
	MessageWriter& setSound( const std::string& soundName_ );

private:
	FormatedStringData getFormatedStringData();

	sf::Time convertWriteSpeedToTime( WriteSpeed d );
};