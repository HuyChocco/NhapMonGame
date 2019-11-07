#pragma once
#include "../GameComponents/GameObject.h"
#include "State.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "BallState.h"

class Ball : public GameObject
{
	Ball();//constructor 
	State *idleState;//đứng yên
	static Ball *__instance;//thành viên tĩnh 
	State *state;
	static vector<Animation *> animations;
	DWORD lastFrameTime;

public:
	//Nạp các tài nguyên cho nhân vật
	void LoadResources();
	//Lấy thể hiện của đối tượng
	static Ball *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }

	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	

	State *GetSate() { return this->state; }
	void SetState(State *state);
	
	
	
	//set width,height cho collider object 
	void SetColliderDemension(float width, float height)
	{
		this->collider.width = width;
		this->collider.height = height;
	}

	void Reset();
	//Hàm thiết lập trạng thái quay trái cho nhân vật
	void TurnLeft();
	//Hàm thiết lập trạng thái quay phải cho nhân vật
	void TurnRight();

	vector<Animation *> GetAnimationsList() { return animations; }
	//Hàm cập nhật
	void Update(DWORD dt) override;
	//Hàm render 
	void Render() override;
};