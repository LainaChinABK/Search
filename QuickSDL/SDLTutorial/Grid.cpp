#include "Grid.h"
#include "Timer.h"
#include <time.h>

Grid::Grid(unsigned int const& rows, unsigned int const& cols, unsigned int const& width, unsigned int const& height, unsigned int const& padding)
	: m_rows(rows)
	, m_cols(cols)
	, m_width(width)
	, m_height(height)
	, m_padding(padding)
	, m_visitTimer(0.0f)
	, m_pathFound(false)
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
	srand(time(NULL));

	float totalWidth = m_cols * (m_width + (m_padding - 1));
	float totalheight = m_rows * (m_height + (m_padding - 1));
	QuickSDL::Vector2 startingPoint(totalWidth * -0.5f, totalheight * -0.5f);

	m_startPoint.row = 5;
	m_startPoint.col = 12;

	m_endPoint.row = 15;
	m_endPoint.col = 3;

	for (unsigned int i = 0; i < m_rows; i++)
	{
		m_tiles.push_back(std::vector<Tile*>());

		for (unsigned int j = 0; j < m_cols; j++)
		{
			Tile* newTile = new Tile();
			newTile->Pos(startingPoint + QuickSDL::Vector2(m_width * 0.5f + (m_width + m_padding) * j, m_height * 0.5f + (m_height + m_padding) * i));
			newTile->Scale(QuickSDL::Vector2(5.0f, 5.0f));
			newTile->Parent(this);

			if (i != m_startPoint.row || j != m_startPoint.col)
			{
				if (i != m_endPoint.row || j != m_endPoint.col)
				{
					if (rand() % 100 < 10)
					{
						newTile->SetIsWall();
					}
				}
			}



			m_tiles[i].push_back(newTile);
		}
	}

	for (unsigned int i = 0; i < m_rows; i++)
	{
		for (unsigned int j = 0; j < m_cols; j++)
		{
			m_tiles[i][j]->SetNeighbours(i > 0 ? m_tiles[i - 1][j] : nullptr, i < m_rows - 1 ? m_tiles[i + 1][j] : nullptr
				, j > 0 ? m_tiles[i][j - 1] : nullptr, j < m_cols - 1 ? m_tiles[i][j + 1] : nullptr);
		}
	}

	m_tiles[m_startPoint.row][m_startPoint.col]->SetAsStartPoint();
	m_tiles[m_endPoint.row][m_endPoint.col]->SetAsEndPoint();

	m_tiles[m_startPoint.row][m_startPoint.col]->Visit();
}

void Grid::Update()
{
	m_visitTimer += QuickSDL::Timer::Instance()->DeltaTime();

	if (m_visitTimer > m_visitDelay)
	{
		m_visitTimer = 0.0f;

		if (!m_pathFound)
		{
			for (unsigned int i = 0; i < m_rows; i++)
			{
				for (unsigned int j = 0; j < m_cols; j++)
				{
					if (m_tiles[i][j]->GetOpen())
					{
						m_open.push_back(m_tiles[i][j]);
					}
				}
			}

			for (unsigned int i = 0; i < m_open.size(); i++)
			{
				m_open[i]->VisitNeighbours();
			}

			if (m_tiles[m_endPoint.row][m_endPoint.col]->GetOpen())
			{
				m_pathFound = true;

				Tile* currentPoint = m_tiles[m_endPoint.row][m_endPoint.col]->GetPrevTile();

				while (currentPoint)
				{
					currentPoint->SetAsPathPoint();
					currentPoint = currentPoint->GetPrevTile();
				}

				m_tiles[m_startPoint.row][m_startPoint.col]->SetAsStartPoint();
				m_tiles[m_endPoint.row][m_endPoint.col]->SetAsEndPoint();
			}

			m_open.clear();
		}
	}
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