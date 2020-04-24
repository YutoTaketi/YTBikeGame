#include "stdafx.h"
#include "BikeMove_Enemy.h"
#include "Game.h"
#include "character/CharacterController.h"
#include "GameTime.h"

BikeMove_Enemy::BikeMove_Enemy()
{
	m_bikecontroller = new BikeController();
}


BikeMove_Enemy::~BikeMove_Enemy()
{
	
}

void BikeMove_Enemy::Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction)
{
	
	if (m_CharaConInitFlag == false)
	{
		//�L�����N�^�[�R���g���[���[�̏�����
		m_charaCon.Init(
			45.0f,           //���a
			100.0f,          //����
			position
		);
		m_CharaConInitFlag = true;
	}

	//�ړ��|�C���g�̔ԍ����擾
	CVector3 diff = m_point->s_position - position;
	//if (m_game->GetFinishFlag() == false) 
	//{
		if (diff.LengthSq() <= 1000.0f) {
			m_point = m_game->GetNextNumber(m_point->s_number);
		}
	//}
	movespeed = m_point->s_position - position;
	movespeed.Normalize();
	accel = movespeed * accelnum;
	movespeed += accel;
	//���C�W������Z
	movespeed *= friction;
	//�ړ����x���v�Z
	position += movespeed;
	

	//��]����
	//�|�C���g�Ƃ̋���
	CVector3 pointLen = m_point->s_position - position;
	//�o�C�N�̑O����
	CVector3 bikemae = { 0, 0, 1 };
	//�o�C�N�̐i�s����
	CVector3 sinkouhoukou = pointLen;
	CQuaternion qRot = CQuaternion::Identity();  //Y����]�p
	//���ς̃Ƃ����߂�
	float angle = m_bikecontroller->NaisekiTheata(bikemae, sinkouhoukou);
	//Z����]�̎������߂�
	CVector3 jiku;
	jiku = m_bikecontroller->KatamukiJiku(bikemae, sinkouhoukou);

	//�o�C�N��i�s�����Ɍ�����N�H�[�^�j�I����
	//�X����N�H�[�^�j�I����������������B
	if (jiku.Length() > 0.001f)
	{
		//�o�C�N��i�s�����Ɍ����邽�߂̉�]�N�H�[�^�j�I�����v�Z����B
		qRot.SetRotation(jiku, angle);
		//�o�C�N���X���邽�߂̏���
		CVector3 TiltConditions = position - m_point->s_position;
		//�E�X��
		if (m_point->s_number == 04    || m_point->s_number == 07
			|| m_point->s_number == 8  || m_point->s_number == 13
			|| m_point->s_number == 14 || m_point->s_number == 15
			|| m_point->s_number == 16 || m_point->s_number == 17
			|| m_point->s_number == 18 || m_point->s_number == 21
			|| m_point->s_number == 22) {
			//�o�C�N���X���邽�߂̉�]�N�H�[�^�j�I�����v�Z����B
			rotation.SetRotation(CVector3::AxisZ(), -0.5f);
		}
		//���X��
		else if (m_point->s_number == 03 || m_point->s_number == 10
			  || m_point->s_number == 11 || m_point->s_number == 12
			  || m_point->s_number == 20 || m_point->s_number == 23
			  || m_point->s_number == 24)
		{
			rotation.SetRotation(CVector3::AxisZ(), -5.5f);
		}
		else {
			rotation.SetRotation(CVector3::AxisZ(), 0.0f);
		}
	}
	rotation.Multiply(qRot, rotation);

	//�L�����N�^�[�R���g���[���[�̍X�V
	if (m_CharaConInitFlag == true)
	{
		 position = m_charaCon.Execute(movespeed,
			//1.0f / 60.0f 
			GameTimeIns().GetFrameDeltaTime()
		);
	}
}
