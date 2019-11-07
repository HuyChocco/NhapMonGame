#pragma once

#include <vector>
#include "GameObject.h"
#include "TiledMap.h"

class GridCell
{
private:
	vector<Tile *> tiles; //danh sách các tile

	int iX;
	int iY;
public:
	//constructor với tham số
	GridCell(int iX, int iY) { this->iX = iX; this->iY = iY; }
	//Hàm thêm 1 ô tile vào danh sách các tile của GridCell
	void AddTile(Tile *tile) { this->tiles.push_back(tile); }
	void clear() {}
	int GetPositionX() { return iX * GRID_SIZE; }//GRID_SIZE=16*4=64
	int GetPositionY() { return (iY + 1) * GRID_SIZE; }
	//Hàm thêm các tiles vào vector tiles của GridCell
	void InsertTiles(vector<Tile *> &output);
	//Hàm cập nhật gridcell
	void Update(DWORD dt);
	//Hàm render gridcell
	void Render();
	~GridCell();
};

