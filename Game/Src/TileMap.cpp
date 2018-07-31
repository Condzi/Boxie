/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "GamePCH.hpp"
#include "TileMap.hpp"

TileMap::TileMap()
{
	View = sf::View{ {0,0, VIEW_AREA.x,VIEW_AREA.y} };
	View.setViewport( VIEWPORT );
	setDrawLayer( static_cast<int16_t>( DrawLayer::TileMap ) );
}

void TileMap::updateVertices()
{
	if ( !TilesTexture )
		return log( con::LogPriority::Error, "TilesTexture not set." );

	mapVertices.clear();
	const auto mapWidth = TileData.size2D().x;
	const auto mapHeight = TileData.size2D().y;

	mapVertices.resize( TileData.sizeFlat() * 4 );

	for ( size_t x = 0; x < mapWidth; x++ )
		for ( size_t y = 0; y < mapHeight; y++ ) {
			{
				auto& tile = TileData.at( { x,y } );
				tile.PositionOnMap = { x,y };
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

std::string TileMap::loggerName() const
{
	// @ToDo: Combine with its name
	return "TileMap";
}

void TileMap::render( sf::RenderWindow & window )
{
	sf::RenderStates states;
	states.texture = TilesTexture;

	auto defaultView = window.getView();
	window.setView( View );
	window.draw( mapVertices, states );
	window.setView( defaultView );
}
