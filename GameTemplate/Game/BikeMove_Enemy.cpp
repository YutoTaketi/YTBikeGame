#include "stdafx.h"
#include "BikeMove_Enemy.h"
#include "Game.h"

BikeMove_Enemy::BikeMove_Enemy()
{
	m_bikecontroller = new BikeController();
}


BikeMove_Enemy::~BikeMove_Enemy()
{
}

void BikeMove_Enemy::Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction)
{
	
	//移動ポイントの番号を取得
	CVector3 diff = m_point->s_position - position;
	if (diff.LengthSq() <= 1000.0f) {
		m_point = m_game->GetNextNumber(m_point->s_number);
	}
	movespeed = m_point->s_position - position;
	movespeed.Normalize();
	accel = movespeed * accelnum;
	movespeed += accel;
	//摩擦係数を乗算
	movespeed *= friction;
	//移動速度を計算
	position += movespeed;
	
}
