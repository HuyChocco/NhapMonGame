#include "Shield.h"
#include "../GameComponents/Grid.h"

Shield * Shield::__instance = NULL;

Shield * Shield::GetInstance()
{
	if (__instance == NULL)
		__instance = new Shield();
	return __instance;
}

Shield::Shield()
{
	LoadResources();

	//IsActive = false;

	width = SHIELD_WIDTH;
	height = SHIELD_HEIGHT;

	vx = SHIELD_SPEED;

	collider.x = x;
	collider.y = y;
	collider.vx = 0;
	collider.vy = 0;
	collider.width = SHIELD_WIDTH;
	collider.height = SHIELD_HEIGHT;

	state = SHIELD_DOWN;
}

void Shield::LoadResources()
{
	LoadTXT loadTXT;
	RECT* listSprite = loadTXT.LoadRect((char*)"Resources\\Captain\\Captain.txt");
	Animation * anim = new Animation(100);
	//SHIELD_SIDE
	Sprite * sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[46], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	//SHIELD_CENTER
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[47], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	//SHIELD_UP
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[48], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);

	//SHIELD_DOWN
	anim = new Animation(100);
	sprite = new Sprite(CAPTAIN_TEXTURE_LOCATION, listSprite[49], CAPTAIN_TEXTURE_TRANS_COLOR);
	anim->AddFrame(sprite);
	animations.push_back(anim);
}

void Shield::Update(DWORD dt)
{
	this->SetSpeedY(0);
	distance += abs(this->GetSpeedX() * dt);
	Captain* captain = Captain::GetInstance();

	if (captain->GetStateNumber() == CAPTAIN_ANI_IDLE || captain->GetStateNumber() == CAPTAIN_ANI_WALK)//trường hợp captain đứng yên
		//hay đi bộ
	{
		this->state = SHIELD_SIDE;//set state cho shield = SHIELD_SIDE
		this->SetSpeedX(0);//cho vx=0
		if (captain->IsLeft())//nếu captain quay trái
			this->SetPositionX(captain->GetPositionX() - 2);//Lấy vị trí x của captain - 2 gán cho position x của shiled
		else //nếu bên phải
			this->SetPositionX(captain->GetPositionX() + 12);//Lấy vị trí x của captain + 12 gán cho position x của shiled
		this->SetPositionY(captain->GetPositionY() - 8);//Lấy vị trí y của captain - 8 gán cho position x của shiled
	}
	if (captain->GetStateNumber() == CAPTAIN_ANI_JUMP)
	{
		this->state = SHIELD_CENTER;
		this->SetSpeedX(0);
		if (captain->IsLeft())
			this->SetPositionX(captain->GetPositionX());
		else
			this->SetPositionX(captain->GetPositionX() + 8);
		this->SetPositionY(captain->GetPositionY() - 4);
	}
	if (captain->GetStateNumber() == CAPTAIN_ANI_CROUCH)
	{
		this->state = SHIELD_SIDE;
		this->SetSpeedX(0);
		if (captain->IsLeft())
			this->SetPositionX(captain->GetPositionX() - 2);
		else
			this->SetPositionX(captain->GetPositionX() + 12);
		this->SetPositionY(captain->GetPositionY() - 26);
	}
	if (captain->GetStateNumber() == CAPTAIN_ANI_SHIELD_UP)
	{
		this->state = SHIELD_UP;
		this->SetSpeedX(0);
		if (captain->IsLeft())
			this->SetPositionX(captain->GetPositionX());
		else
			this->SetPositionX(captain->GetPositionX() + 8);
		this->SetPositionY(captain->GetPositionY() + 2);
	}
	if (captain->GetStateNumber() == CAPTAIN_ANI_SIT_ON_SHIELD)
	{
		this->state = SHIELD_DOWN;
		this->SetSpeedX(0);
		if (captain->IsLeft())
			this->SetPositionX(captain->GetPositionX() - 2);
		else
			this->SetPositionX(captain->GetPositionX() + 12);
		this->SetPositionY(captain->GetPositionY() - 26);
	}

	this->SetPositionX((float)(this->GetPositionX() + this->GetSpeedX()* dt*(isLeft == true ? -1 : 1)));//set lại theo dt
	this->SetPositionY((float)(this->GetPositionY() + this->GetSpeedY()* dt));//set lại theo dt
}

void Shield::Render()
{
	int state = this->state;//Lấy trạng thái hiện tại
	
	Captain * captain = Captain::GetInstance();//lấy nhân vật hiện tại
	//if (captain->IsThrowing() == true)
	{
		SpriteData spriteData;

		spriteData.width = SHIELD_WIDTH;
		spriteData.height = SHIELD_HEIGHT;
		spriteData.x = this->GetPositionX();
		spriteData.y = this->GetPositionY();

		spriteData.scale = 1;
		spriteData.angle = 0;
		spriteData.isLeft = captain->IsLeft();
		spriteData.isFlipped = captain->IsFlipped();

		switch (state)
		{
		case SHIELD_SIDE:
		{
			this->animations[SHIELD_SIDE]->Render(spriteData);
		}
		break;
		case SHIELD_CENTER:
		{
			this->animations[SHIELD_CENTER]->Render(spriteData);
		}
		break;
		case SHIELD_UP:
		{
			this->animations[SHIELD_UP]->Render(spriteData);
		}
		break;
		case SHIELD_DOWN:
		{
			this->animations[SHIELD_DOWN]->Render(spriteData);
		}
		break;
		}
	}
}

Shield::~Shield()
{
}
