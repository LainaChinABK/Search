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

	Tile(int const& cost, int const& color, int const& width, int const& height);
	~Tile();

	void Render() override;

	void SetAsStartTile();
	void SetAsEndTile();
	void SetAsSearchedTile();
	void SetAsPathTile();

	bool GetSearched() { return m_searched; }
	bool GetOpen() { return m_searched; }

	void Search(Tile* pathLink);

	void SetNeightbours(Tile* up, Tile* down, Tile* left, Tile* right);

	void SearchNeighbours();

	Tile* GetPathLink() { return m_pathLink; }

private:

	int m_cost;
	int m_width;
	int m_height;

	bool m_searched;
	bool m_open;

	Tile* m_neighbours[TileDirections::Max];

	Tile* m_pathLink;

	QuickSDL::Texture* m_texture;
};