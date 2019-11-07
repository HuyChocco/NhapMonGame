#pragma once


//Tên ứng dụng
#define WINDOW_CLASS_NAME L"Avengers"
#define MAIN_WINDOW_TITLE L"Captain America and The Avengers"
//Màu background, kích cỡ màn hình
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

//Framerate tối đa
#define MAX_FRAME_RATE 90

//
enum Stage {
	STAGE_1,
	STAGE_2,
	STAGE_BOSS_1,
	STAGE_BOSS_2
};
enum ObjectType
{
	DEFAULT,
	BRICK,
	BRICK_NOCOLLISION_BOTTOM,
	ON_BUTTON,
	RIVER,
	SWING
};
//TiledMap
//
// MAP
#define BACKGROUND_1 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_2 L"Resources\\TiledMap\\Map-Pittsburgh.png"
#define BACKGROUND_BOSS_1 L"Resources\\TiledMap\\Map-Boss1.png"
#define BACKGROUND_BOSS_2 L"Resources\\TiledMap\\Map-Boss2.png"
// TILE
#define TILES_MATRIX_STAGE_1 L"Resources\\TiledMap\\Map-Charleston-Matrix.txt"
#define TILES_MATRIX_STAGE_2 L"Resources\\TiledMap\\Map-Pittsburgh-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS_1 L"Resources\\TiledMap\\Map-Boss1-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS_2 L"Resources\\TiledMap\\Map-Boss2-Matrix.txt"

#define TILES_MATRIX_DELIMITER ","
#define TILES_WIDTH_PER_TILE	16
#define TILES_HEIGHT_PER_TILE	16
#define TILES_TRANSCOLOR D3DCOLOR_XRGB(255, 0, 255)

#define GRID_SIZE 64
#define GRID_MAX_X 48
#define GRID_MAX_Y 5

//Giá trị tốc độ đi, tốc độ nhảy, trọng lực
#define CAPTAIN_WALK_SPEED		0.125f
#define CAPTAIN_JUMP_SPEED_Y	0.6f
#define CAPTAIN_GRAVITY			0.025f

//Animation của Captain
#define CAPTAIN_ANI_IDLE				0
#define CAPTAIN_ANI_WALK				1
#define ALADIN_ANI_STOP					2
#define CAPTAIN_ANI_JUMP				3
#define CAPTAIN_ANI_CROUCH 				4
#define CAPTAIN_ANI_THROW_SHIELD 		5
#define CAPTAIN_ANI_ROLL				6
#define CAPTAIN_ANI_KICK				7
#define CAPTAIN_ANI_STAND_HIT			8
#define CAPTAIN_ANI_CROUCH_HIT			9
#define CAPTAIN_ANI_SIT_ON_SHIELD		10
#define CAPTAIN_ANI_SWING				11
#define CAPTAIN_ANI_WADE				12
#define CAPTAIN_ANI_SHIELD_UP			13
#define CAPTAIN_ANI_GET_HURT			14
#define CAPTAIN_ANI_DEAD				15


#define CAPTAIN_TEXTURE_LOCATION L"Resources\\Aladin\\aladin.png"
#define CAPTAIN_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(255, 0, 255)
#define CAPTAIN_SPRITE_WIDTH 40
#define CAPTAIN_SPRITE_HEIGHT 50

#define BALL_TEXTURE_LOCATION L"Resources\\Ball\\circle.png"
#define BALL_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define BALL_SPRITE_WIDTH 44
#define BALL_SPRITE_HEIGHT 44

#define ALADIN_TEXTURE_LOCATION L"Resources\\Aladin\\aladin.png"
#define ALADIN_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define ALADIN_SPRITE_WIDTH 44
#define ALADIN_SPRITE_HEIGHT 44
//Animation của Shield
#define SHIELD_SIDE 0
#define SHIELD_CENTER 1
#define SHIELD_UP 2
#define SHIELD_DOWN 3

#define SHIELD_WIDTH 16
#define SHIELD_HEIGHT 16
#define SHIELD_SPEED 0.125f