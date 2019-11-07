#pragma once
#include "../GameComponents/GameObject.h"

class GameObject;
class GameItem :
	public GameObject
{
private:
	static int GameItemId;
protected:
	int Id;
	vector<Animation *> animations;
	bool Active;

	//Item itemtype;
public:
	GameItem();
	~GameItem();

	bool IsActive() { return this->Active; }
	void SetActive(bool value) { this->Active = value; }

	static int GetGameItemId() { return GameItemId++; }
	int GetId() { return this->Id; }

	//void SetItemType(Item type) { this->itemtype = type; };
	//Item GetItemType() { return this->itemtype; }

	virtual void Update(DWORD dt);
	virtual void Render();
};