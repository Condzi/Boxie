/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

struct Tile
{
	// In map units
	Vec2u PositionOnMap;
	uint8_t TextureIndex{};
	// When Entity starts stepping on this tile
	std::function<void( Tile&, con::Entity& )> OnIntersectionBegin = []( Tile&, con::Entity& ) {};
	// When entity is whole on this tile (stops moving towards it)
	std::function<void( Tile&, con::Entity& )> OnIntersectionEnd = []( Tile&, con::Entity& ) {};
	con::Entity* EntityOnTop = nullptr;

	virtual ~Tile() = default;
};

class TileMap :
	public con::IDrawable,
	public con::ILogger
{
public:
	inline static constexpr uint8_t TILE_SIZE = 4;
	// Map is shrinked 4 pixels in horizontal and 9 from up and down
	inline static const RectF VIEWPORT{ mapPixelXToAbsolute( 1 ), mapPixelYToAbsolute( 9 ), mapPixelXToAbsolute( WINDOW_WIDTH - 2 ), mapPixelYToAbsolute( WINDOW_HEIGHT - 18 ) };
	inline static const Vec2f VIEW_AREA{ WINDOW_WIDTH-4, WINDOW_HEIGHT-18 };

	sf::View View;
	con::FixedArray2D<Tile> TileData;
	const sf::Texture* TilesTexture = nullptr;

	TileMap();
	virtual ~TileMap() = default;

	void updateVertices();

private:
	sf::VertexArray mapVertices{ sf::PrimitiveType::Quads };

	std::string loggerName() const override;
	void render( sf::RenderWindow& window ) override;
};