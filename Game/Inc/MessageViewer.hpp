/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "MessageWriter.hpp"

class MessageViewer final :
	public con::IDrawable,
	public con::IUpdatable
{
	friend class MessageWriter;
public:
	inline static const RectF VIEWPORT{ 0, 0, 1, 1 };

	MessageViewer();

	MessageWriter& writeNew();

	void displayAll();
	void skip();
	bool isDoneDisplayingLine() const;
	bool isDoneDisplayingAll() const;

private:
	MessageWriter writer{*this};
	sf::Time timeSinceLastDisplay;
	sf::Time displaySpeed;
	con::BitmapText textToDisplay;
	size_t currentViewingLine{}, currentViewingLetter{};
	MessageWriter::FormatedStringData textData;
	std::string soundName;

	// Resets all info
	void reset();
	void nextLine();
	void update() override;
	void render( sf::RenderWindow& window ) override;
	int8_t getUpdatePriority() const override;
};