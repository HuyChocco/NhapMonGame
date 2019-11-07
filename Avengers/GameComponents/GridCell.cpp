#include "GridCell.h"
#include "Grid.h"
//Hàm thêm các tiles vào vector tiles của GridCell
void GridCell::InsertTiles(vector<Tile *> &output)
{
	output.insert(output.end(), this->tiles.begin(), this->tiles.end());
}

void GridCell::Update(DWORD dt)
{
	return;
}
void GridCell::Render()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		TiledMap::GetInstance()->RenderTile(tiles[i]);// Gọi hàm render 1 ô tile của lớp TiledMap
	}
}

GridCell::~GridCell()
{
}
