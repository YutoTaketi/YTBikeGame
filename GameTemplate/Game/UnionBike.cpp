#include "stdafx.h"
#include "UnionBike.h"
#include "Game.h"

UnionBike::UnionBike()
{
	m_model = new  SkinModel();
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model->Init(L"Assets/modelData/Bike3.cmo");
}


UnionBike::~UnionBike()
{
}

void UnionBike::Move()
{
	//�ړ��|�C���g�̔ԍ����擾
	CVector3 diff = m_point->s_position - m_position;
	if (diff.LengthSq() <= 1000.0f) {
		m_point = m_game->GetNextNumber(m_point->s_number);
	}

	m_moveSpeed = m_point->s_position - m_position;
	m_moveSpeed.Normalize();
	m_accel = m_moveSpeed * m_accelNum;
	m_moveSpeed += m_accel;
	//���C�W������Z
	m_moveSpeed *= m_friction;
	//�ړ����x���v�Z
	m_position += m_moveSpeed;
}

void UnionBike::Turn()
{
	//�|�C���g�Ƃ̋���
	CVector3 pointLen = m_point->s_position - m_position;
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
		CVector3 TiltConditions = m_position - m_point->s_position;
		if (m_point->s_number == 04 || m_point->s_number == 07
			|| m_point->s_number == 8 || m_point->s_number == 13
			|| m_point->s_number == 16 || m_point->s_number == 18
			|| m_point->s_number == 22) {
			//�o�C�N���X���邽�߂̉�]�N�H�[�^�j�I�����v�Z����B
			m_rotation.SetRotation(CVector3::AxisZ(), -0.5f);
		}
		else if (m_point->s_number == 03 || m_point->s_number == 10
			|| m_point->s_number == 12 || m_point->s_number == 20
			|| m_point->s_number == 24)
		{
			m_rotation.SetRotation(CVector3::AxisZ(), -5.5f);
		}
		else {
			m_rotation.SetRotation(CVector3::AxisZ(), 0.0f);
		}
	}
	m_rotation.Multiply(qRot, m_rotation);
}


void UnionBike::Update()
{
	Move();
	Turn();
}

void UnionBike::Render()
{

}

void UnionBike::Draw()
{

}