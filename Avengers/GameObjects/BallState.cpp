#include "BallState.h"
#include <math.h>

BallState::BallState(Ball *ball, int states)
{
	this->ball = ball;
	this->states = states;
}

BallState::~BallState()
{

}
void BallState::Update(DWORD dt)
{
	int state = this->states;//Lấy ra trạng thái nhân vật hiện tại
	switch (state)
	{
	case CAPTAIN_ANI_JUMP://Nhân vật nhảy
	{

	default:
		break;
	}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();//Lấy ra danh sách các tiles hiện tại

	//ball->SetSpeedY(ball->GetSpeedY() - CAPTAIN_GRAVITY);//vy của nhân vật luôn bị trừ 0.025f
	//ball->SetSpeedX(ball->GetSpeedX() + CAPTAIN_GRAVITY);
	coEvents.clear();
	ball->SetDt(dt);
	ball->CalcPotentialCollisions(tiles, coEvents);//Tính toán khả năng đụng độ giữa tiles hiện tại và ball object

	if (coEvents.size() == 0)//trường hợp không xảy ra đụng độ
	{
		float moveX = trunc(ball->GetSpeedX()* dt);
		float moveY = trunc(ball->GetSpeedY()* dt);
		ball->SetPositionX(ball->GetPositionX() + moveX);//cộng một lượng vx*dt vào position x của captain
		ball->SetPositionY(ball->GetPositionY() + moveY);//cộng một lượng vx*dt vào position y của captain
	}
	else //xảy ra đụng độ
	{
		float min_tx, min_ty, nx = 0, ny;

		ball->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * ball->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * ball->GetSpeedY() * dt + ny * 0.4;

		ball->SetPositionX(ball->GetPositionX() + moveX);
		ball->SetPositionY(ball->GetPositionY() + moveY);


		if (nx != 0) ball->SetSpeedX(ball->GetSpeedX()*-1);
		if (ny != 0) ball->SetSpeedY(ball->GetSpeedY()*-1);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				//captain->SetIsGrounded(true);//Cho captain dứng trên mặt đất
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	
}
void BallState::Render()
{
	int state = this->states;

	SpriteData spriteData;
	if (this->ball != NULL)
	{
		spriteData.width = BALL_SPRITE_WIDTH;
		spriteData.height = BALL_SPRITE_HEIGHT;
		spriteData.x = ball->GetPositionX();
		spriteData.y = ball->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = false;//ball->IsLeft();
		spriteData.isFlipped = false;//ball->IsFlipped();
	}
	switch (state)
	{
	case CAPTAIN_ANI_IDLE:
	{
		ball->GetAnimationsList()[CAPTAIN_ANI_IDLE]->Render(spriteData);
		break;
	}
	
	}
}

