#pragma once
#include "State.h"
#include "../GameComponents/Constants.h"
#include "Captain.h"

class CaptainState : public State
{
private:
	Captain *captain;
	int states;
public: 
	CaptainState(Captain *captain, int states);
	~CaptainState();

	void Jump() override;
	void Idle() override;
	void Walk() override;
	void Stop() override;
	void Crouch() override;
	void ThrowShield() override;
	void Roll() override;
	void Kick() override;
	void StandHit() override;
	void CrouchHit() override;
	void SitOnShield() override;
	void Swing() override;
	void Wade() override;
	void ShieldUp() override;
	void GetHurt() override;
	void Dead() override;

	void Update(DWORD dt) override;
	void Render() override;
};
