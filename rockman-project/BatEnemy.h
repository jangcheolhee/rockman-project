#pragma once
#include "Enemy.h"
class BatEnemy : public Enemy
{
protected:
	bool isMove = false;
public:



	// Enemy을(를) 통해 상속됨
	void Init() override;
	void Reset() override;
	void UpdateBehavior(float dt) override;

};

