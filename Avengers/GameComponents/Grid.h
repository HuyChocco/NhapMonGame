#pragma once
#include "GameObject.h"
#include "Constants.h" 
#include "GridCell.h"
#include "../GameObjects/Captain.h"
#include "../GameObjects/Ball.h"
#include <vector>

#include <fstream>
#include <string>

#define POSTOCELL(K) (int)(K/GRID_SIZE);
#define POSXTOCELL(K) (int)(K/GRID_SIZE);
#define POSYTOCELL(K) (int)(K % GRID_SIZE == 0 ? K/GRID_SIZE - 1 : K/GRID_SIZE);

using namespace std;

class Cell;
class Ball;
typedef vector<GridCell *> CellRow;
typedef vector<CellRow> CellMatrix;
class Grid {
private:
	static Grid *__instance;// thành viên tĩnh
	int width, height;

	CellMatrix cells; 

	vector<Tile *> curTiles;

	vector<Tile *> CollisionTiles;

	Viewport *viewport;

	Captain * captain;

	Ball* ball;

	Grid();

public:
	static Grid *GetInstance();

	void LoadCells();

	void GetCameraPosOnGrid(int &l, int &r, int &t, int &b);
	void GetCaptainPosOnGrid(int &l, int &r, int &t, int &b);

	vector<Tile *> GetCurTiles() { return this->curTiles; }
	vector<Tile *> GetCollisionTiles() { return this->CollisionTiles; }
 
	void Update(DWORD dt);
	void Render();

	CellMatrix GetTile() { return this->cells; }

	static void SetNewGrid()
	{
		__instance = NULL;
		__instance = new Grid();
	}
	~Grid() {
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				if (cells[i][j] != NULL)
					delete cells[i][j];
			}
	}
};