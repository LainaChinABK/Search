#pragma once
#include "Texture.h"
#include <vector>
#include "Tile.h"

class Grid : public QuickSDL::GameEntity
{
private:

	struct GridPoint
	{
		int row;
		int col;
	};

public:

	Grid(unsigned int const& rows, unsigned int const& cols, unsigned int const& width, unsigned int const& height, unsigned int const& padding);

	~Grid();

	void Update();

	void Render();

private:

	void GenerateTiles();

private:

	unsigned int m_rows;
	unsigned int m_cols;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_padding;

	bool m_pathFound;

	GridPoint m_startPoint;
	GridPoint m_endPoint;

	std::vector<std::vector<Tile*>> m_tiles;

	std::vector<Tile*> m_open;

	float const m_visitDelay = 0.1f;
	float m_visitTimer;
};