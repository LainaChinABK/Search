#include "Tile.h"

Tile::Tile(int const& cost, int const& color, int const& width, int const& height)
	: m_cost(cost)
	, m_width(width)
	, m_height(height)
	, m_searched(false)
{
	m_texture = new QuickSDL::Texture("stars.png", 8, 0, 4, 4);
	m_texture->Parent(this);
}

Tile::~Tile()
{
	delete m_texture;
}

void Tile::SetAsStartTile()
{
	m_texture->MoveClipRect(12, 0);
}

void Tile::SetAsEndTile()
{
	m_texture->MoveClipRect(4, 0);
}
void Tile::SetAsSearchedTile()
{
	m_texture->MoveClipRect(0, 0);
}

void Tile::Render()
{
	m_texture->Render();
}