#include "stdafx.h"
#include "AlphaBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"

AlphaBike::AlphaBike()
{
	m_model = new  SkinModel();
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model->Init(L"Assets/modelData/Bike2.cmo");
	//�o�C�N�̈ړ�������������
	m_bikeMove = new BikeMove_Enemy();

}


AlphaBike::~AlphaBike()
{
}

void AlphaBike::Move()
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

void AlphaBike::Turn()
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
			|| m_point ->s_number == 12 || m_point->s_number == 20
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

void AlphaBike::Update()
{
	//�o�C�N�̈ړ����������s����B
	m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
// Move();
 //Turn();
  m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
  m_model->Draw(
	  g_camera3D.GetViewMatrix(),
	  g_camera3D.GetProjectionMatrix()
  );
}

void AlphaBike::Render()
{

}

void AlphaBike::Draw()
{

}