#pragma once
#include "Enemy.h"
class RabbitEnemy : public Enemy
{
protected:
	bool isGrounded = false;
	bool move = false;
	int attack = 3;


public:
	void Init() override;
	void Reset() override;
	void UpdateBehavior(float dt) override;
};

