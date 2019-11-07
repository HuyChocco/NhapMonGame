#include "CaptainState.h"
#include <math.h>

CaptainState::CaptainState(Captain *captain, int states) 
{
	this->captain = captain;
	this->states = states;
}

CaptainState::~CaptainState() 
{

}

void CaptainState::Jump()
{
	int state = this->states;//lấy trạng thái hiện tại

	switch (state)
	{
	case CAPTAIN_ANI_CROUCH:
	case CAPTAIN_ANI_JUMP:
		break;
	case CAPTAIN_ANI_IDLE:
	case CAPTAIN_ANI_WALK:
	{
		if (captain->IsGrounded())//kiểm tra nhân vật có ở trên mặt đất không
		{
			captain->SetIsGrounded(false);//đổi cờ trên mặt đất thành false
			captain->SetSpeedY(CAPTAIN_JUMP_SPEED_Y);//set vy=0.6f
			captain->SetState(captain->GetJumpState());//thiết lập lại số trạng thái cho nhân vật captain
													   // và trả về trạng thái jump
		}
	}
	break;
	}
}

void CaptainState::Idle()
{
	int state = this->states;

	switch (state)
	{
	case CAPTAIN_ANI_IDLE:
		break;
	case CAPTAIN_ANI_CROUCH:
	{
		captain->SetIsCrouching(false);//Thay đổi cờ iscrounching
		captain->SetState(captain->GetIdleState());//Thay đổi state cho nhân vật
	}
	break;
	case ALADIN_ANI_STOP:
	{
		captain->SetSpeedX(0);//cho nhân vật dừng lại
		captain->SetState(captain->GetIdleState());//Thay đổi state cho nhân vật
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->SetSpeedX(0);//cho nhân vật dừng lại
		captain->SetState(captain->GetIdleState());//Thay đổi state cho nhân vật
	}
	break;
	}
}

void CaptainState::Walk()
{
	int state = this->states;
	switch (state)
	{
	case CAPTAIN_ANI_CROUCH:
	case CAPTAIN_ANI_JUMP:
		break;
	case CAPTAIN_ANI_IDLE:
	{
		captain->SetSpeedX(CAPTAIN_WALK_SPEED * (captain->IsLeft() ? -1 : 1));
		captain->SetState(captain->GetWalkState());
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->SetSpeedX(CAPTAIN_WALK_SPEED * (captain->IsLeft() ? -1 : 1));
	}
	break;
	}
}
void CaptainState::Stop()
{
	int state = this->states;
	switch (state)
	{
	
	case CAPTAIN_ANI_WALK:
	{
		captain->SetState(captain->GetStopState());
		captain->GetAnimationsList()[ALADIN_ANI_STOP]->setIsStop(true);
		captain->SetSpeedX(captain->GetSpeedX()/2);
	}
	break;
	}
}
void CaptainState::Crouch()
{
	int state = this->states;

	switch (state)
	{
	case CAPTAIN_ANI_CROUCH:
	case CAPTAIN_ANI_JUMP:
		break;
	case CAPTAIN_ANI_IDLE:
	{
		captain->SetIsCrouching(true);
		captain->SetState(captain->GetCrouchState());
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->SetSpeedX(0);
		captain->SetIsCrouching(true);
		captain->SetState(captain->GetCrouchState());
	}
	break;
	}
}

void CaptainState::ThrowShield()
{
	int state = this->states;
}

void CaptainState::Roll()
{
	int state = this->states;
}

void CaptainState::Kick()
{
	int state = this->states;
}

void CaptainState::StandHit()
{
	int state = this->states;
}

void CaptainState::CrouchHit()
{
	int state = this->states;
}

void CaptainState::SitOnShield()
{
	int state = this->states;
}

void CaptainState::Swing()
{
	int state = this->states;
}

void CaptainState::Wade()
{
	int state = this->states;
}

void CaptainState::ShieldUp()
{
	int state = this->states;

	switch (state)
	{
	case CAPTAIN_ANI_SHIELD_UP:
	case CAPTAIN_ANI_JUMP:
		break;
	case CAPTAIN_ANI_IDLE:
	{
		captain->SetIsShieldUp(true);
		captain->SetState(captain->GetShieldUpState());
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->SetSpeedX(0);
		captain->SetIsShieldUp(true);
		captain->SetState(captain->GetShieldUpState());
	}
	break;
	}
}

void CaptainState::GetHurt()
{
	int state = this->states;
}

void CaptainState::Dead()
{
	int state = this->states;
}

void CaptainState::Update(DWORD dt)
{
	setDelta(dt);
	int state = this->states;//Lấy ra trạng thái nhân vật hiện tại
	switch (state)
	{
	case CAPTAIN_ANI_JUMP://Nhân vật nhảy
	{
		if (captain->IsGrounded())//Nếu nhân vật trên mặt đất
		{
			captain->SetState(captain->GetIdleState());
		}
		if (captain->GetPositionY() >= TiledMap::GetInstance()->GetHeight() + 20)
		{
			captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_GRAVITY);
		}
	}
	break;
	default:
		break;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

#pragma region	Collide with brick
	vector<Tile *> tiles = Grid::GetInstance()->GetCurTiles();//Lấy ra danh sách các tiles hiện tại
	
	captain->SetSpeedY(captain->GetSpeedY() - CAPTAIN_GRAVITY);//vy của nhân vật luôn bị trừ 0.025f

	coEvents.clear();
	captain->SetDt(dt);
	captain->CalcPotentialCollisions(tiles, coEvents);//Tính toán khả năng đụng độ giữa tiles hiện tại và captain object

	if (coEvents.size() == 0)//trường hợp không xảy ra đụng độ
	{
		float moveX = trunc(captain->GetSpeedX()* dt);
		float moveY = trunc(captain->GetSpeedY()* dt);
		captain->SetPositionX(captain->GetPositionX() + moveX);//cộng một lượng vx*dt vào position x của captain
		captain->SetPositionY(captain->GetPositionY() + moveY);//cộng một lượng vx*dt vào position y của captain
	}
	else //xảy ra đụng độ
	{
		float min_tx, min_ty, nx = 0, ny;

		captain->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		float moveX = min_tx * captain->GetSpeedX() * dt + nx * 0.4;
		float moveY = min_ty * captain->GetSpeedY() * dt + ny * 0.4;

		captain->SetPositionX(captain->GetPositionX() + moveX);
		captain->SetPositionY(captain->GetPositionY() + moveY);


		if (nx != 0) captain->SetSpeedX(0);
		if (ny != 0) captain->SetSpeedY(0);

		if (coEventsResult[0]->collisionID == 1)
		{
			if (ny == 1)
			{
				captain->SetIsGrounded(true);//Cho captain dứng trên mặt đất
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
}

void CaptainState::Render()
{
	int state = this->states;

	SpriteData spriteData;
	if (this->captain != NULL)
	{
		spriteData.width = CAPTAIN_SPRITE_WIDTH;
		spriteData.height = CAPTAIN_SPRITE_HEIGHT;
		spriteData.x = captain->GetPositionX();
		spriteData.y = captain->GetPositionY();
		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = captain->IsLeft();
		spriteData.isFlipped = captain->IsFlipped();
	}

	switch (state)
	{
	case CAPTAIN_ANI_IDLE:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_IDLE]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_WALK:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_WALK]->Render(spriteData);
	}
	break;
	case ALADIN_ANI_STOP:
	{
		captain->GetAnimationsList()[ALADIN_ANI_STOP]->Render(spriteData);
		
	}
	break;
	/*case CAPTAIN_ANI_CROUCH:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_CROUCH]->Render(spriteData);
	}
	break;
	
	case CAPTAIN_ANI_JUMP:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_JUMP]->Render(spriteData);
	}
	break;
	
	case CAPTAIN_ANI_THROW_SHIELD:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_THROW_SHIELD]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_ROLL:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_ROLL]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_KICK:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_KICK]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_STAND_HIT:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_STAND_HIT]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_CROUCH_HIT:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_CROUCH_HIT]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_SIT_ON_SHIELD:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_SIT_ON_SHIELD]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_SWING:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_SWING]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_WADE:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_WADE]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_SHIELD_UP:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_SHIELD_UP]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_GET_HURT:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_GET_HURT]->Render(spriteData);
	}
	break;
	case CAPTAIN_ANI_DEAD:
	{
		captain->GetAnimationsList()[CAPTAIN_ANI_DEAD]->Render(spriteData);
	}
	break;*/
	}
}

