#pragma once

#include "BikeMove.h"
#include "BikeController.h"
/// <summary>
/// プレイヤーのバイクを動かす。
/// </summary>
class BikeMove_Player : public BikeMove
{
public:
	BikeMove_Player();
	~BikeMove_Player();
	void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum,float& friction);
	CVector3 m_moveDirectionF = CVector3::Zero();
	CVector3 playermae = { 0, 0, 1 };
	CVector3 sinkouhoukou = g_camera3D.GetForward();
	BikeController* m_bikecontroller;
};

