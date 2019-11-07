#pragma once
#include "../GameComponents/GameObject.h"
#include "State.h"
#include "../GameComponents/Constants.h"
#include "../GameComponents/Game.h"
#include "CaptainState.h"
#include "Shield.h"

class Captain : public GameObject
{
	Captain();//constructor của Captain

	static Captain *__instance;//thành viên tĩnh captain

	State *idleState;//đứng yên
	State *walkState;//đi bộ
	State *jumpState;//nhảy
	State *crouchState;//cúi
	State *throwShieldState;//ném khiêng
	State *rollState;//trượt
	State *kickState;//đá
	State *standHitState;//đứng đánh
	State *crouchHitState;//ngồi đánh
	State *sitOnShieldState;//ngồi trên khiêng
	State *swingState;//đung đưa
	State *wadeState;//lội
	State *shieldUpState;//đưa khiêng lên 
	State *getHurtState;//bị thương
	State *deadState;//chết
	State *stopState;
	State *state;

	Shield *shield;

	int stateNumber;

	bool isGrounded = false;
	bool isCrouching = false;
	bool isShieldUp = false;
	bool isThrowing;

	static vector<Animation *> animations;
	DWORD lastFrameTime;

public: 
	//Nạp các tài nguyên cho nhân vật
	void LoadResources();
	//Lấy thể hiện của đối tượng captain
	static Captain *GetInstance();

	DWORD GetLastFrameTime() { return this->lastFrameTime; }

	void SetLastFrameTime(DWORD lastFrameTime) { this->lastFrameTime = lastFrameTime; }

	void SetIsGrounded(bool isGrounded) { this->isGrounded = isGrounded; }
	void SetIsCrouching(bool isCrouching) { this->isCrouching = isCrouching; }
	void SetIsShieldUp(bool isShieldUp) { this->isShieldUp = isShieldUp; }

	State *GetSate() { return this->state; }
	void SetState(State *state);
	//Lấy số trạng thái
	int GetStateNumber() { return this->stateNumber; }
	//Gán số trạng thái
	void SetStateNumber(int number) { this->stateNumber = number; }
	//Các hàm lấy trạng thái nhân vật và thiết lập số trạng thái nhân vật
	State *GetIdleState();
	State *GetWalkState();
	State *GetJumpState();
	State *GetCrouchState();
	State *GetThrowShieldState();
	State *GetRollState();
	State *GetKickState();
	State *GetStandHitState();
	State *GetCrouchHitState();
	State *GetSitOnShieldState();
	State *GetSwingState();
	State *GetWadeState();
	State *GetShieldUpState();
	State *GetGetHurtState();
	State *GetDeadState();
	State *GetStopState();
	//Các hàm kiểm tra trạng thái nhân vật
	bool IsGrounded() { return isGrounded; }
	bool IsCrouching() { return isCrouching; }
	bool IsShieldUp() { return isShieldUp; }
	bool IsLeft() { return isLeft; }
	bool IsFlipped() { isFlipped = isLeft ? true : false; return isFlipped; }
	bool IsThrowing() { return this->isThrowing; }
	//Hàm thiết lập trạng thái ném
	void SetThrowing(bool value) { this->isThrowing = value; }
	//Các hàm override từ lớp CaptainState
	void Idle();
	void Walk();
	void Stop();
	void Jump();
	void Crouch();
	void ThrowShield();
	void Roll();
	void Kick();
	void StandHit();
	void CrouchHit();
	void SitOnShield();
	void Swing();
	void Wade();
	void ShieldUp();
	void GetHurt();
	void Dead();
	//set width,height cho collider object captain
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
	//Hàm cập nhật captain
	void Update(DWORD dt) override;
	//Hàm render captain
	void Render() override;
};