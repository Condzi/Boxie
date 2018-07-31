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
	void clear();
	bool isDoneDisplaying() const;

private:
	MessageWriter writer;
	sf::Time timeSinceLastDisplay;
	sf::Time displaySpeed;
	con::BitmapText textToDisplay;

	void update() override;
	void render( sf::RenderWindow& window ) override;
	int8_t getUpdatePriority() const override;
};