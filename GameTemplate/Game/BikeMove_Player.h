#pragma once

#include "BikeMove.h"
#include "BikeController.h"
/// <summary>
/// �v���C���[�̃o�C�N�𓮂����B
/// </summary>
class BikeMove_Player : public BikeMove
{
public:
	BikeMove_Player();
	~BikeMove_Player();
	void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum,float& friction);
	CVector3 m_moveDirectionF = CVector3::Zero();
	BikeController* m_bikecontroller;
};

