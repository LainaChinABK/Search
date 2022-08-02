#pragma once
#include "Texture.h"

class Tile : public QuickSDL::GameEntity
{
public:

	enum TileDirections
	{
		Up,
		Down,
		Left,
		Right,
		Max
	};

public:

	Tile();

	~Tile();

	void Render();

	void SetAsStartPoint();
	void SetAsEndPoint();
	void SetAsVisitedPoint();
	void SetAsPathPoint();

	void SetNeighbours(Tile* up, Tile* down, Tile* left, Tile* right);

	void Visit();

	void VisitNeighbours();

	bool GetOpen() { return m_open; }

	Tile* GetPrevTile() { return m_prevTile; }

	void SetIsWall() { m_wall = true; }

private:

	bool m_open;
	bool m_visited;
	bool m_wall;

	Tile* m_prevTile;

	Tile* m_neighbours[4];

	QuickSDL::Texture* m_texture;
};