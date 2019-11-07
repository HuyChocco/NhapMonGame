#pragma once
#include "d3d9.h"

class Captain;
class State
{
protected:
	DWORD dt;
public:
	State();
	void setDelta(DWORD dt) { this->dt = dt; }
	virtual void Idle();
	virtual void Walk();
	virtual void Stop();
	virtual void Jump();
	virtual void Crouch();
	virtual void ThrowShield();
	virtual void Roll();
	virtual void Kick();
	virtual void StandHit();
	virtual void CrouchHit();
	virtual void SitOnShield();
	virtual void Swing();
	virtual void Wade();
	virtual void ShieldUp();
	virtual void GetHurt();
	virtual void Dead();
	virtual void Update(DWORD dt);
	virtual void Render();
};