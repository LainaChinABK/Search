#pragma once
#include "Texture.h"
#include <vector>
#include "Tile.h"

class Grid : public QuickSDL::GameEntity
{
private:

	struct GridPoint
	{
		GridPoint(int _row = 0, int _col = 0)
			: row(_row)
			, col(_col)
		{

		}

		int row;
		int col;
	};

public:

	Grid(unsigned int const& rows, unsigned int const& cols, unsigned int const& width, unsigned int const& height, unsigned int const& padding);

	~Grid();

	void Update() override;

	void Render() override;

private:

	void GenerateTiles();

private:

	unsigned int m_rows;
	unsigned int m_cols;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_padding;

	GridPoint m_start;
	GridPoint m_end;

	std::vector<std::vector<Tile*>> m_tiles;

	std::vector<Tile*> m_open;
	std::vector<Tile*> m_searched;

	float const m_waitTimer = 0.1f;
	float m_waitTime;

	bool m_pathFound = false;
};