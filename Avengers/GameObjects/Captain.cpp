#include "Captain.h"

vector<Animation *> Captain::animations = vector<Animation *>();
Captain *Captain::__instance = NULL;

Captain::Captain()
{
	LoadResources();

	idleState = new CaptainState(this, CAPTAIN_ANI_IDLE);
	walkState = new CaptainState(this, CAPTAIN_ANI_WALK);
	stopState = new CaptainState(this, ALADIN_ANI_STOP);
	jumpState = new CaptainState(this, CAPTAIN_ANI_JUMP);
	crouchState = new CaptainState(this, CAPTAIN_ANI_CROUCH);
	throwShieldState = new CaptainState(this, CAPTAIN_ANI_THROW_SHIELD);
	rollState = new CaptainState(this, CAPTAIN_ANI_ROLL);
	kickState = new CaptainState(this, CAPTAIN_ANI_KICK);
	standHitState = new CaptainState(this, CAPTAIN_ANI_STAND_HIT);
	crouchHitState = new CaptainState(this, CAPTAIN_ANI_CROUCH_HIT);
	sitOnShieldState = new CaptainState(this, CAPTAIN_ANI_SIT_ON_SHIELD);
	swingState = new CaptainState(this, CAPTAIN_ANI_SWING);
	wadeState = new CaptainState(this, CAPTAIN_ANI_WADE);
	shieldUpState = new CaptainState(this, CAPTAIN_ANI_SHIELD_UP);
	getHurtState = new CaptainState(this, CAPTAIN_ANI_GET_HURT);
	deadState = new CaptainState(this, CAPTAIN_ANI_DEAD);

	state = idleState;//trạng thái ban đầu cho captain

	this->x = 50;
	this->y = 200;
	this->width = CAPTAIN_SPRITE_WIDTH;
	this->height = CAPTAIN_SPRITE_HEIGHT;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = CAPTAIN_SPRITE_WIDTH;
	collider.height = CAPTAIN_SPRITE_HEIGHT;

	shield = new Shield();
}

Captain *Captain::GetInstance()
{
	if (__instance == NULL)
		__instance = new Captain();
	return __instance;
}
//Nạp các animation cho captain
void Captain::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");

	// CAPTAIN_ANI_IDLE
	Animation * anim = new Animation(100);
	for (int i = 0; i < 1; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);

	 /////CAPTAIN_ANI_WALK
	anim = new Animation(100);
	for (int i = 1; i < 13; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	/////ALADIN_ANI_STOP
	anim = new Animation(100);
	for (int i = 13; i < 22; i++)
	{
		Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
		anim->AddFrame(sprite);
	}
	animations.push_back(anim);
	//// CAPTAIN_ANI_JUMP
	//anim = new Animation(100);
	//for (int i = 7; i < 8; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_CROUCH
	//anim = new Animation(100);
	//for (int i = 6; i < 7; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_THROW_SHIELD
	//anim = new Animation(300);
	//for (int i = 11; i < 13; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_ROLL
	//anim = new Animation(300);
	//for (int i = 8; i < 10; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_KICK
	//anim = new Animation(300);
	//for (int i = 10; i < 11; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_STAND_HIT
	//anim = new Animation(300);
	//for (int i = 13; i < 15; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_CROUCH_HIT
	//anim = new Animation(300);
	//for (int i = 15; i < 17; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_SIT_ON_SHIELD
	//anim = new Animation(300);
	//for (int i = 19; i < 20; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_SWING
	//anim = new Animation(300);
	//for (int i = 27; i < 30; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_WADE
	//anim = new Animation(300);
	//for (int i = 44; i < 46; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_SHIELD_UP
	//anim = new Animation(300);
	//for (int i = 5; i < 6; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_GET_HURT
	//anim = new Animation(300);
	//for (int i = 33; i < 34; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);

	//// CAPTAIN_ANI_DEAD
	//anim = new Animation(300);
	//for (int i = 34; i < 36; i++)
	//{
	//	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[i], CAPTAIN_TEXTURE_TRANS_COLOR);
	//	anim->AddFrame(sprite);
	//}
	//animations.push_back(anim);
}

void Captain::SetState(State * state)
{
	this->state = state;
}

State * Captain::GetIdleState()
{
	this->SetStateNumber(CAPTAIN_ANI_IDLE);
	return idleState;
}

State * Captain::GetWalkState()
{
	this->SetStateNumber(CAPTAIN_ANI_WALK);
	return walkState;
}

State * Captain::GetJumpState()
{
	this->SetStateNumber(CAPTAIN_ANI_JUMP);
	return jumpState;
}

State * Captain::GetCrouchState()
{
	this->SetStateNumber(CAPTAIN_ANI_CROUCH);
	return crouchState;
}

State * Captain::GetThrowShieldState()
{
	this->SetStateNumber(CAPTAIN_ANI_THROW_SHIELD);
	return throwShieldState;
}

State * Captain::GetRollState()
{
	this->SetStateNumber(CAPTAIN_ANI_ROLL);
	return rollState;
}

State * Captain::GetKickState()
{
	this->SetStateNumber(CAPTAIN_ANI_KICK);
	return kickState;
}

State * Captain::GetStandHitState()
{
	this->SetStateNumber(CAPTAIN_ANI_STAND_HIT);
	return standHitState;
}

State * Captain::GetCrouchHitState()
{
	this->SetStateNumber(CAPTAIN_ANI_CROUCH_HIT);
	return crouchHitState;
}

State * Captain::GetSitOnShieldState()
{
	this->SetStateNumber(CAPTAIN_ANI_SIT_ON_SHIELD);
	return sitOnShieldState;
}

State * Captain::GetSwingState()
{
	this->SetStateNumber(CAPTAIN_ANI_SWING);
	return swingState;
}

State * Captain::GetWadeState()
{
	this->SetStateNumber(CAPTAIN_ANI_WADE);
	return wadeState;
}

State * Captain::GetShieldUpState()
{
	this->SetStateNumber(CAPTAIN_ANI_SHIELD_UP);
	return shieldUpState;
}

State * Captain::GetGetHurtState()
{
	this->SetStateNumber(CAPTAIN_ANI_GET_HURT);
	return getHurtState;
}

State * Captain::GetDeadState()
{
	this->SetStateNumber(CAPTAIN_ANI_DEAD);
	return deadState;
}

State * Captain::GetStopState()
{
	this->SetStateNumber(ALADIN_ANI_STOP);
	return stopState;
}
void Captain::Idle()
{
	state->Idle();
}

void Captain::Walk()
{
	state->Walk();
}
void Captain::Stop()
{
	state->Stop();
}
void Captain::Jump()
{
	state->Jump();
}

void Captain::Crouch()
{
	state->Crouch();
}

void Captain::ThrowShield()
{
	state->ThrowShield();
}

void Captain::Roll()
{
	state->Roll();
}

void Captain::Kick()
{
	state->Kick();
}

void Captain::StandHit()
{
	state->StandHit();
}

void Captain::CrouchHit()
{
	state->CrouchHit();
}

void Captain::SitOnShield()
{
	state->SitOnShield();
}

void Captain::Swing()
{
	state->Swing();
}

void Captain::Wade()
{
	state->Wade();
}

void Captain::ShieldUp()
{
	state->ShieldUp();
}

void Captain::GetHurt()
{
	state->GetHurt();
}

void Captain::Dead()
{
	state->Dead();
}

void Captain::TurnLeft()
{
	isLeft = true;
}
void Captain::TurnRight()
{
	isLeft = false;
}
//Hàm trả về trạng thái nhân vật và camera ban đầu
void Captain::Reset()
{
	this->SetPositionX(50);
	this->SetPositionY(200);
	Viewport::GetInstance()->Reset();
}

void Captain::Update(DWORD dt)
{
	
	if (this->GetSpeedX() < 0 && this->GetPositionX() < 0)
	{
		this->SetPositionX(0);
	}
	if (this->GetPositionX() >= Game::GetInstance()->GetTiledMap()->GetInstance()->GetWidth()-50)
	{
		this->SetPositionX(Game::GetInstance()->GetTiledMap()->GetInstance()->GetWidth() - 50);
	}
	if (this->GetPositionY() <=0)
	{
		//this->SetPositionX(0);
		//this->SetPositionY(0);
	}
	state->Update(dt);// gọi hàm cập nhật của captain state
	//shield->Update(dt);
}
void Captain::Render()
{
	state->Render();//gọi hàm cập nhật của captain state
	//shield->Render();// gọi hàm cập nhật của shield
}
