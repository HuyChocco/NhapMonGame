#include "Ball.h"

vector<Animation *> Ball::animations = vector<Animation *>();
Ball *Ball::__instance = NULL;

Ball::Ball()
{
	LoadResources();

	idleState = new BallState(this, CAPTAIN_ANI_IDLE);
	state = idleState;//trạng thái ban đầu cho captain
	this->x = 70;
	this->y = 300;
	this->width = BALL_SPRITE_WIDTH;
	this->height = BALL_SPRITE_HEIGHT;
	this->vx = 0.125;
	this->vy = -0.125;
	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = BALL_SPRITE_WIDTH;
	collider.height = BALL_SPRITE_HEIGHT;

	
}

Ball  *Ball::GetInstance()
{
	if (__instance == NULL)
		__instance = new Ball();
	return __instance;
}
//Nạp các animation cho ball
void Ball::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Ball\\ball.txt");

	
	
	
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(BALL_TEXTURE_LOCATION, listSprite[i], BALL_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//// CAPTAIN_ANI_WALK
	//anim = new Animation(100);
	//for (int i = 1; i < 5; i++)
	//{
	//	Sprite * sprite = new Sprite(BALL_TEXTURE_LOCATION, listSprite[i], BALL_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
}

void Ball::SetState(State * state)
{
	this->state = state;
}


void Ball::TurnLeft()
{
	isLeft = true;
}
void Ball::TurnRight()
{
	isLeft = false;
}
//Hàm trả về trạng thái nhân vật và camera ban đầu
void Ball::Reset()
{
	this->SetPositionX(50);
	this->SetPositionY(200);
	Viewport::GetInstance()->Reset();
}

void Ball::Update(DWORD dt)
{

	if (this->GetSpeedX() < 0 && this->GetPositionX() < 0)
	{
		this->SetPositionX(0);
	}
	if (this->GetPositionX() >= Game::GetInstance()->GetTiledMap()->GetInstance()->GetWidth() - 50)
	{
		this->SetPositionX(Game::GetInstance()->GetTiledMap()->GetInstance()->GetWidth() - 50);
	}
	if (this->GetPositionY() <= 0)
	{
		//this->SetPositionX(0);
		//this->SetPositionY(0);
	}
	state->Update(dt);// gọi hàm cập nhật của ball state
	
}
void Ball::Render()
{
	state->Render();//gọi hàm cập nhật của captain state
	
}
