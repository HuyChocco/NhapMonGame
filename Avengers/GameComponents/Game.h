#pragma once
#include "Constants.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "TiledMap.h"
#include "Grid.h"
#include "../GameObjects/Captain.h"
#include "../GameObjects/Ball.h"
#include <chrono>

class Graphics;
class Keyboard;
class Grid;

class Game
{
	bool initialized = false;

	static Game *__instance;
	static HINSTANCE hInstance;
	HWND hWnd;									

	Keyboard *keyboard;
	Graphics *graphics;

	Captain *captain;
	Ball* ball;
	TiledMap *tiledMap;
	Viewport *viewport;

	Grid *grid;

	Stage stage;
public:
	Stage GetStage() { return this->stage; }
	void SetStage(int stage) { this->stage = (Stage)stage; }
	//Hàm khởi tạo game
	void Init();
	//Hàm tạo cửa sổ game
	HWND CreateGameWindow(HINSTANCE hInstance, int ScreenWidth, int ScreenHeight);
	//Hàm xử lý các thông điệp
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//Hàm nạp các tài nguyên của game
	void LoadResources();

	//Hàm cập nhật game
	void Update(DWORD dt);
	//Hàm render game
	void Render();
	//Hàm run
	int Run();
	//Hàm lấy captain
	Captain *GetCaptain();
	//Hàm lấy tiledmap
	TiledMap *GetTiledMap() { return tiledMap; }

	void SetTileMap(TiledMap *tiledMap) {
		this->tiledMap = tiledMap;
	}

	void SetGrid(Grid *grid)
	{
		this->grid = grid;
	}
	//Hàm sweptAABB
	static float SweptAABB(Collider c1, Collider c2, float &normalx, float &normaly);

	static Game *GetInstance();
	~Game();
};


