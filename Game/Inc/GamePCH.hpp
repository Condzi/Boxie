/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <Engine/All.hpp>

constexpr float32_t WINDOW_WIDTH = 128;
constexpr float32_t WINDOW_HEIGHT = 96;

inline float32_t mapPixelXToAbsolute( float32_t x )
{
	return x / WINDOW_WIDTH;
}

inline float32_t mapPixelYToAbsolute( float32_t y )
{
	return y / WINDOW_HEIGHT;
}

inline Vec2f mapPixelToAbsolute( const Vec2f& point )
{
	return { mapPixelXToAbsolute( point.x ), mapPixelYToAbsolute( point.y ) };
}

enum class SceneID : int16_t
{
	Loader,
	Game
};

enum class DrawLayer : int16_t
{
	TileMap,
	Entity
};

// Created Iterator-like style
enum class TileID : uint8_t
{
	FLOOR_BEGIN = 0, // Add floor tiles here \/\/
	Floor = FLOOR_BEGIN,
	FLOOR_END,
	WALL_BEGIN = FLOOR_END, // Add wall tiles here \/\/
	Wall = WALL_BEGIN,
	WALL_END
};

