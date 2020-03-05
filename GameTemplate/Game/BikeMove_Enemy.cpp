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
	
	//�ړ��|�C���g�̔ԍ����擾
	CVector3 diff = m_point->s_position - position;
	if (diff.LengthSq() <= 1000.0f) {
		m_point = m_game->GetNextNumber(m_point->s_number);
	}
	movespeed = m_point->s_position - position;
	movespeed.Normalize();
	accel = movespeed * accelnum;
	movespeed += accel;
	//���C�W������Z
	movespeed *= friction;
	//�ړ����x���v�Z
	position += movespeed;
	
}
