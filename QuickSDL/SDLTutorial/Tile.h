#pragma once
#include "Texture.h"

class Tile : public QuickSDL::GameEntity
{
public:

	Tile(int const& cost, int const& color, int const& width, int const& height);
	~Tile();

	void Render() override;

	void SetAsStartTile();
	void SetAsEndTile();
	void SetAsSearchedTile();

	bool GetSearched() { return m_searched; }

private:

	int m_cost;
	int m_width;
	int m_height;

	bool m_searched;

	Tile* m_neighbours[4];

	QuickSDL::Texture* m_texture;
};