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
	inline static const RectF VIEWPORT{ mapPixelXToAbsolute( 1 ), mapPixelYToAbsolute( 9 ), mapPixelXToAbsolute( WINDOW_WIDTH - 2 ), mapPixelYToAbsolute( WINDOW_HEIGHT - 18 ) };
	inline static const Vec2f VIEW_AREA{ WINDOW_WIDTH-4, WINDOW_HEIGHT-18 };

	sf::View View;
	con::FixedArray2D<Tile> TileData;
	const sf::Texture* TilesTexture = nullptr;

	TileMap()
	{
		// @ToDo: Scale it to map size?
		// Map is shrinked 4 pixels in horizontal and 9 from up and down
		View = sf::View{ {0,0, VIEW_AREA.x,VIEW_AREA.y} };
		View.setViewport( VIEWPORT );
		setDrawLayer( static_cast<int16_t>( DrawLayer::TileMap ) );
	}

	virtual ~TileMap() = default;

	void updateVertices()
	{
		if ( !TilesTexture )
			return log( con::LogPriority::Error, "TilesTexture not set." );

		setPositionsOfTiles();

		mapVertices.clear();
		const auto mapWidth = TileData.size2D().x;
		const auto mapHeight = TileData.size2D().y;

		mapVertices.resize( TileData.sizeFlat() * 4 );

		for ( size_t x = 0; x < mapWidth; x++ )
			for ( size_t y = 0; y < mapHeight; y++ ) {
				{
					const auto& tile = TileData.at( { x,y } );
					const uint16_t positionInTexture = tile.TextureIndex * TILE_SIZE;

					sf::Vertex* quad = &mapVertices[( x+y * mapWidth ) * 4];
					quad[0].position = Vec2f( x * TILE_SIZE, y * TILE_SIZE );
					quad[1].position = Vec2f( ( x+1 ) * TILE_SIZE, y * TILE_SIZE );
					quad[2].position = Vec2f( ( x+1 ) * TILE_SIZE, ( y+1 ) * TILE_SIZE );
					quad[3].position = Vec2f( x * TILE_SIZE, ( y+1 ) * TILE_SIZE );

					quad[0].texCoords = Vec2f( positionInTexture, 0 );
					quad[1].texCoords = Vec2f( positionInTexture + TILE_SIZE, 0 );
					quad[2].texCoords = Vec2f( positionInTexture + TILE_SIZE, TILE_SIZE );
					quad[3].texCoords = Vec2f( positionInTexture, TILE_SIZE );
				}
			}
	}

private:
	sf::VertexArray mapVertices{ sf::PrimitiveType::Quads };

	std::string loggerName() const override
	{
		return "TileMap";
	}

	void setPositionsOfTiles()
	{
		for ( size_t x = 0; x < TileData.size2D().x; x++ )
			for ( size_t y = 0; y < TileData.size2D().y; y++ )
				TileData.at( { x,y } ).PositionOnMap = { x,y };
	}

	void render( sf::RenderWindow& window ) override
	{
		sf::RenderStates states;
		states.texture = TilesTexture;

		auto defaultView = window.getView();
		window.setView( View );
		window.draw( mapVertices, states );
		window.setView( defaultView );
	}
};