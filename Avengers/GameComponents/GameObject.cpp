#include "GameObject.h"
#include "Game.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = 0;
	collider.height = 0;
}
GameObject::GameObject(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	vx = vy = 0;

	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.width = width;
	collider.height = height;
}

GameObject::~GameObject()
{
}

//Hàm cập nhật
void GameObject::Update(DWORD dt)
{

}
//Hàm render
void GameObject::Render()
{

}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float t, nx, ny;
	//Kiểm tra va chạm
	t = Game::SweptAABB(
		this->collider,
		coO->GetCollider(),
		nx,
		ny
	);

	LPCOLLISIONEVENT e = new CollisionEvent(t, nx, ny, coO);// sự kiện dụng độ
	return e;// Trả về con trỏ sự kiện va chạm
}
void GameObject::CalcPotentialGameObjectCollisions(
	vector<LPGAMEOBJECT> &coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	return;
}
//Hàm tính toán khả năng va chạm giữa object và các tile
void GameObject::CalcPotentialMapCollisions(
	vector<Tile *> &tiles,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	LPGAMEOBJECT solidTileDummy = new GameObject(0, 0, 16, 16);
	for (int i = 0; i < tiles.size(); i++)
	{
		Tile *curTile = tiles[i];//Lấy tile
		solidTileDummy->SetPositionX(curTile->x);//set position x cho object theo curTile
		solidTileDummy->SetPositionY(curTile->y);//set position y cho object theo curTile
		solidTileDummy->UpdateTileCollider();// cập nhật collider cho gameobject mới này

		if (curTile->type == ObjectType::BRICK || curTile->type == ObjectType::BRICK_NOCOLLISION_BOTTOM)
		{	
			LPCOLLISIONEVENT e = SweptAABBEx(solidTileDummy);//kiểm tra va chạm giữa gameobject mới và gameobject hiện tại
			e->collisionID = 1;

			if (e->t >= 0 && e->t < 1.0f && (e->ny == 1|| e->nx == 1))
			{
				coEvents.push_back(e);//va chạm thì thêm vào danh sách LPCOLLISIONEVENT
			}
			else
			{
				delete e;
			}
		}
		else 
		{
			
		}
	}
}

void GameObject::CalcPotentialCollisions(
	vector<Tile *> &tiles,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	this->UpdateObjectCollider();// cập nhật collider của game object
	CalcPotentialMapCollisions(tiles, coEvents);// Gọi hàm

	sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);// Sort các event theo thứ tự thời gian tăng dần
}

void GameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) 
		{
			min_tx = c->t; 
			nx = c->nx; 
			min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) 
		{
			min_ty = c->t; 
			ny = c->ny; 
			min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

bool GameObject::IsCollide(GameObject *CollisionObject)
{
	Collider MainObject = this->collider;
	RECT rec;
	rec.top = MainObject.y;
	rec.left = MainObject.x;
	rec.right = MainObject.x + MainObject.width;
	rec.bottom = MainObject.y - MainObject.height;

	Collider TargetObject = CollisionObject->collider;
	if (MainObject.direction == 1)
	{
		if (TargetObject.x > rec.left && TargetObject.x < rec.right )
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
		}
		else 
		{
			return false;
		}
	}
	else if (MainObject.direction == -1)
	{
		if (TargetObject.x + TargetObject.width > rec.left && TargetObject.x + TargetObject.width < rec.right)
		{
			if ((rec.top < TargetObject.y && rec.top > TargetObject.y - TargetObject.height)
				|| (rec.top > TargetObject.y && rec.bottom < TargetObject.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}
	return false;
}

void GameObject::UpdateObjectCollider()
{
	int direction = (isLeft == true) ? -1 : 1;
	collider.x = x;
	collider.y = y;
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.direction = direction;
}

void GameObject::UpdateTileCollider()
{
	collider.x = x;
	collider.y = y - 8;//???
	collider.vx = vx;
	collider.vy = vy;
	collider.dt = dt;
	collider.height = 8;//???
}
RECT GameObject::GetRect()
{
	RECT rect;
	rect.top = y;
	rect.left = x;
	rect.right = x + width;
	rect.bottom = y - height;
	return rect;
}