#pragma once
#include "State.h"
#include "../GameComponents/Constants.h"
#include "Ball.h"
class Ball;
class BallState : public State
{
private:
	Ball *ball;

	int states;
public:
	BallState(Ball *ball, int states);
	~BallState();

	void Update(DWORD dt) override;
	void Render() override;
};
