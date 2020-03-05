#pragma once
#include "BikeMove.h"
#include "BikeController.h"

/// <summary>
/// 敵のバイクを動かす。
/// </summary>

class Game;

class BikeMove_Enemy : public BikeMove
{
public:
	BikeMove_Enemy();
	~BikeMove_Enemy();

	void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction);
	CVector3 m_moveDirectionF = CVector3::Zero();
	BikeController* m_bikecontroller;

};

