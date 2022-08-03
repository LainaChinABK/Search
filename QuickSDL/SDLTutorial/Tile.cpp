#include "Tile.h"

Tile::Tile()
	: m_visited(false)
	, m_open(false)
	, m_prevTile(nullptr)
	, m_wall(false)
{
	m_texture = new QuickSDL::Texture("stars.png", 8, 0, 4, 4);
	m_texture->Parent(this);
}

Tile::~Tile()
{
	delete m_texture;
}

void Tile::SetAsStartPoint()
{
	m_texture->MoveClipRect(12, 0);
}

void Tile::SetAsEndPoint()
{
	m_texture->MoveClipRect(4, 0);
}

void Tile::SetAsVisitedPoint()
{
	m_texture->MoveClipRect(0, 0);
}

void Tile::SetAsPathPoint()
{
	m_texture->MoveClipRect(16, 0);
}

void Tile::SetNeighbours(Tile* up, Tile* down, Tile* left, Tile* right)
{
	if (up && !up->m_wall)
	{
		m_neighbours[Up] = up;
	}
	if (down && !down->m_wall)
	{
		m_neighbours[Down] = down;
	}
	if (left && !left->m_wall)
	{
		m_neighbours[Left] = left;
	}
	if (right && !right->m_wall)
	{
		m_neighbours[Right] = right;
	}
}

void Tile::Visit()
{
	m_open = true;
	m_visited = true;
	SetAsVisitedPoint();
}

void Tile::VisitNeighbours()
{
	for (int i = 0; i < Max; i++)
	{
		if (m_neighbours[i] && !m_neighbours[i]->m_visited)
		{
			// update g(n) if necessary
			int tempG = GetG() + 1;
			if (tempG < m_neighbours[i]->GetG())
			{
				m_neighbours[i]->SetG(tempG);
			}

			m_neighbours[i]->Visit();
			m_neighbours[i]->m_prevTile = this;
		}
	}

	m_open = false;
}

void Tile::Render()
{
	if (!m_wall)
	{
		m_texture->Render();
	}
}