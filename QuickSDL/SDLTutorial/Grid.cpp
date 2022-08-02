#include "Grid.h"

Grid::Grid(unsigned int const& rows, unsigned int const& cols, unsigned int const& width, unsigned int const& height, unsigned int const& padding)
	: m_rows(rows)
	, m_cols(cols)
	, m_width(width)
	, m_height(height)
	, m_padding(padding)
{
	GenerateTiles();
}

Grid::~Grid()
{
	for (unsigned int i = 0; i < m_tiles.size(); i++)
	{
		for (unsigned int j = 0; j < m_tiles[i].size(); j++)
		{
			delete m_tiles[i][j];
			m_tiles[i][j] = nullptr;
		}
		m_tiles[i].clear();
	}

	m_tiles.clear();
}

void Grid::GenerateTiles()
{
	m_start.row = 3;
	m_start.col = 10;

	m_end.row = 10;
	m_end.col = 2;

	float totalWidth = m_cols * (m_width + (m_padding - 1));
	float totalheight = m_rows * (m_height + (m_padding - 1));
	QuickSDL::Vector2 startingPoint(totalWidth * -0.5f, totalheight * -0.5f);

	for (unsigned int i = 0; i < m_rows; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());

		for (unsigned int j = 0; j < m_cols; j++)
		{
			Tile* newTile = new Tile(0, 0, m_width, m_height);
			newTile->Pos(startingPoint + QuickSDL::Vector2(m_width * 0.5f + (m_width + m_padding) * j, m_height * 0.5f + (m_height + m_padding) * i));
			newTile->Scale(QuickSDL::Vector2(5.0f, 5.0f));
			newTile->Parent(this);

			m_tiles[i].push_back(newTile);
		}
	}

	m_tiles[m_start.row][m_start.col]->SetAsStartTile();
	m_tiles[m_end.row][m_end.col]->SetAsEndTile();
}



void Grid::Render()
{
	for (unsigned int i = 0; i < m_tiles.size(); i++)
	{
		for (unsigned int j = 0; j < m_tiles[i].size(); j++)
		{
			m_tiles[i][j]->Render();
		}
	}
}