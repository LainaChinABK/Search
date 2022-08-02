#include "Tile.h"

Tile::Tile(int const& cost, int const& color, int const& width, int const& height)
	: m_cost(cost)
	, m_width(width)
	, m_height(height)
	, m_searched(false)
	, m_pathLink(nullptr)
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

void Tile::SetAsPathTile()
{
	m_texture->MoveClipRect(16, 0);
}

void Tile::Search(Tile* pathLink)
{
	m_open = true;
	m_searched = true;
	SetAsSearchedTile();
	m_pathLink = pathLink;
}

void Tile::SetNeightbours(Tile* up, Tile* down, Tile* left, Tile* right)
{
	m_neighbours[Up] = up;
	m_neighbours[Down] = down;
	m_neighbours[Left] = left;
	m_neighbours[Right] = right;
}

void Tile::SearchNeighbours()
{
	for (int i = 0; i < TileDirections::Max; i++)
	{
		if (m_neighbours[i] && !m_neighbours[i]->GetSearched())
		{
			m_neighbours[i]->Search(this);
		}
	}

	m_open = false;
}

void Tile::Render()
{
	m_texture->Render();
}