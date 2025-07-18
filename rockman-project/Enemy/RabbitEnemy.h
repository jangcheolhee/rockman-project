#pragma once
#include "Enemy.h"
class RabbitEnemy : public Enemy
{
protected:
	bool isGrounded = false;

public:
	void Init() override;
	void Reset() override;
	void UpdateBehavior(float dt) override;
};

