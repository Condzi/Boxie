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

	MessageArea();

	void display( const std::string& textToDisplay_, DisplaySpeed displaySpeed_ );
	void setLettersColors( sf::Color color, size_t pos, size_t count = 1 );
	void displayAll();
	void clear();
	bool isDoneDisplaying() const;

private:
	std::vector<sf::Color> lettersColors;
	con::BitmapText displayedText;
	sf::Time timeSinceLastDisplay;
	DisplaySpeed displaySpeed;

	void update() override;
	void render( sf::RenderWindow& window ) override;
	int8_t getUpdatePriority() const override;
	
	sf::Time displaySpeedToTime( DisplaySpeed d );
};