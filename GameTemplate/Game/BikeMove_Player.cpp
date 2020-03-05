#include "stdafx.h"
#include "BikeMove_Player.h"


BikeMove_Player::BikeMove_Player()
{
	m_bikecontroller = new BikeController();
}


BikeMove_Player::~BikeMove_Player()
{
}

void BikeMove_Player::Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction)
{
	//�J�����̑O���������擾
	CVector3 cameraForward = g_camera3D.GetForward();

	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();

	if (g_pad[0].IsPress(enButtonA))
	{
		//�����x���v�Z
		m_moveDirectionF = cameraForward;

		accel = m_bikecontroller->BikeAccel(m_moveDirectionF, accelnum);

	}
	else {
		accel = CVector3::Zero();
	}

	movespeed += accel;
	//���C�W������Z
	movespeed *= friction;
	//�ړ����x���v�Z
	position += movespeed;
	if (movespeed.LengthSq() >= 300.0f * 300.0f) {
		movespeed.Normalize();
		movespeed *= 300.0f;
	}

	//��]����

}