#include"Grid.h"
#include "Game.h"

Grid *Grid::__instance = NULL;

Grid::Grid()
{
	curTiles.clear();

	
	this->width = (int)(Game::GetInstance()->GetTiledMap()->GetWidth() / 64) + 2;//Chiều rộng của Grid
	this->height = (int)(Game::GetInstance()->GetTiledMap()->GetHeight() / 64) + 2;//Chiều dài của Grid

	for (int i = 0; i < height; i++)
	{
		CellRow curRow;//1 hàng của Grid=vector các GridCell
		for (int j = 0; j < width; j++)
		{
			GridCell *curCell = new GridCell(j, i);
			curRow.push_back(curCell);
		}
		cells.push_back(curRow);//Thêm hàng trên vào ma trận Grid
	}

	LoadCells();//Load tilemap vào 

	//Luu viewport
	this->viewport = Viewport::GetInstance();
	
	//Lưu captain
	this->captain = Captain::GetInstance();

	this->ball = Ball::GetInstance();
}

void Grid::LoadCells()
{
	Matrix &tiledMapMatrix = Game::GetInstance()->GetTiledMap()->GetMatrix();//hàm trả về tham chiếu đến ma trận của TiledMap
	for (int i = 0; i < tiledMapMatrix.size(); i++)
	{
		for (int j = 0; j < tiledMapMatrix[i].size(); j++)
		{
			//Tim vi tri o chua tile
			int cellX = POSXTOCELL(tiledMapMatrix[i][j].x);
			int cellY = POSYTOCELL(tiledMapMatrix[i][j].y);

			Tile *dummyPtr = &tiledMapMatrix[i][j];
			cells[cellY][cellX]->AddTile(dummyPtr);//Thêm tiled từ ma trận của tilemap vào ma trận của GridCell

			if (tiledMapMatrix[i][j].type == ObjectType::BRICK)//nếu ô tiled trong ma trận của TileMap là kiểu BRICK
			{
				CollisionTiles.push_back(dummyPtr);//thì thêm vào vector collisiontile
			}
		}
	}
}

void Grid::GetCaptainPosOnGrid(int &l, int &r, int &t, int &b)
{
	RECT rect = captain->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}

void Grid::GetCameraPosOnGrid(int &l, int &r, int &t, int &b) {
	RECT rect = viewport->GetRect();
	l = (int)(rect.left / GRID_SIZE);
	t = (int)(rect.top % GRID_SIZE == 0 ? rect.top / GRID_SIZE - 1 : rect.top / GRID_SIZE);
	r = (int)(rect.right / GRID_SIZE);
	b = (int)(rect.bottom / GRID_SIZE);
}
//Hàm update của grid
void Grid::Update(DWORD dt)
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);

	
	curTiles.clear();

	for (size_t i = 0; i < cells.size(); i++)
	{
		for (size_t j = 0; j < cells[i].size(); j++)
		{
			cells[i][j]->clear();
		}
	}

	int captainLCell, captainRCell, captainTCell, captainBCell;

	this->GetCaptainPosOnGrid(captainLCell, captainRCell, captainTCell, captainBCell);

	for (int i = captainBCell; i <= captainTCell; i++)
	{
		//if (captainLCell - 2 >= 0)
		{
			if ( Game::GetInstance()->GetStage() != Stage::STAGE_BOSS_1 && Game::GetInstance()->GetStage() != Stage::STAGE_BOSS_2)
			{
				for (int j = captainLCell; j <= captainRCell; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
				}
			}
			else if ( Game::GetInstance()->GetStage() != Stage::STAGE_BOSS_1 && Game::GetInstance()->GetStage() != Stage::STAGE_BOSS_2)
			{
				for (int j = captainLCell; j <= captainRCell; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
				}
			}
			else if (Game::GetInstance()->GetStage() == Stage::STAGE_BOSS_1)
			{
				for (int j = captainLCell; j <= captainRCell; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
				}
			}
			else if (Game::GetInstance()->GetStage() == Stage::STAGE_BOSS_2)
			{
				for (int j = captainLCell; j <= captainRCell; j++)
				{
					cells[i][j]->InsertTiles(curTiles);
				}
			}
		}
	}

	captain->Update(dt);
	
}
//Hàm render của Grid
void Grid::Render()
{
	int lCell, rCell, tCell, bCell;
	this->GetCameraPosOnGrid(lCell, rCell, tCell, bCell);
	curTiles.clear();

	for (int i = bCell; i <= tCell; i++)
	{
		for (int j = lCell; j <= rCell; j++)
		{
			cells[i][j]->Render();//gọi hàm render của gridcell để render những cell nằm trong phạm vi của camera
		}
	}

	captain->Render();
	
}

Grid *Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}
