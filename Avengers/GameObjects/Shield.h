#pragma once
#include "GameItem.h"

class Shield : public GameItem
{
	int damage = 10;

	vector<Animation *> animations;
	static Shield * __instance;

	int state;

	bool Active;

	float distance;//khoảng cách 
public:
	Shield();
	//void CreateShield(float posx, float posy, float dt, bool isLeft);
	int GetDamage() { return this->damage; }
	bool IsActive() { return this->Active; }
	bool SetActive(bool value) { this->Active = value; }

	static Shield * GetInstance();
	//Load các animation cho shield
	void LoadResources();

	void Update(DWORD dt) override;
	void Render() override;

	float GetDistance() { return this->distance; }

	~Shield();
};

