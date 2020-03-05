#include "stdafx.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "BikeMove.h"
#include "BikeMove_Player.h"
Player::Player()
{
	m_model = new SkinModel();
	m_bikecontroller = new BikeController();

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model->Init(L"Assets/modelData/playerBike.cmo");
	//�o�C�N�̈ړ�������������
	m_bikeMove = new BikeMove_Player;
}



Player::~Player()
{

}

void Player::Move()
{
	/*
	//�J�����̑O���������擾
	CVector3 cameraForward = g_camera3D.GetForward();
	
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	
	
	 if (g_pad[0].IsPress(enButtonA))
	 {
		 //�����x���v�Z
		 m_moveDirectionF = cameraForward;
		 
		 m_accel = m_bikecontroller->BikeAccel(m_moveDirectionF, m_accelNum);
		 
	 }
	 else {
		 m_accel = CVector3::Zero();
	 }
	
	 m_moveSpeed += m_accel;
	 //���C�W������Z
	 m_moveSpeed *= m_friction;  
	 //�ړ����x���v�Z
	 m_position += m_moveSpeed;
	 if (m_moveSpeed.LengthSq() >= 300.0f * 300.0f) {
		 m_moveSpeed.Normalize();
		 m_moveSpeed *= 300.0f;
	 }
	 
	*/
	 //�G�ƂԂ�������͂������B*/
}
void Player::Turn()
{
	//���X�e�B�b�N�Ńv���C���[����]
	CVector3 stick; //Y����]�p
	CVector3 stickyokokaitenn; //Z����]�p
	CQuaternion qRot = CQuaternion::Identity();  //Y����]�p
	
	stick.x = g_pad[0].GetLStickXF();
	stickyokokaitenn.x = g_pad[0].GetLStickXF();
	//�v���C���[�̑O�x�N�g���Ɛi�s�����̓��ς����߂�
	CVector3 playermae = { 0, 0, 1 };
	CVector3 sinkouhoukou = g_camera3D.GetForward();
	
	//���ς��v�Z
	
	float angle = m_bikecontroller->NaisekiTheata(playermae, sinkouhoukou);
	//�O�ς��v�Z
	
	CVector3 playerjiku;
	playerjiku = m_bikecontroller->KatamukiJiku(playermae, sinkouhoukou);
	
	if (playerjiku.Length() > 0.001f)
	{
		//�o�C�N��i�s�����Ɍ����邽�߂̉�]�N�H�[�^�j�I�����v�Z����B
		qRot.SetRotation(playerjiku, angle);
		//�o�C�N���X���邽�߂̉�]�N�H�[�^�j�I�����v�Z����B
		m_rotation.SetRotation(CVector3::AxisZ(), stickyokokaitenn.x * -1.0f);
	}
	//�o�C�N��i�s�����Ɍ�����N�H�[�^�j�I����
	//�X����N�H�[�^�j�I����������������B
	m_rotation.Multiply(qRot, m_rotation);
	//m_rotation.Multiply(qRot2);
	

}


void Player::Update()
{
	//�o�C�N�̈ړ����������s����B
	m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	Turn();
	
	//���[���h�s��̍X�V�B
	m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3{1.0f,1.0f, 1.0f});
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Render()
{
	//m_shadowMap.RegistShadowCaster(m_model);
}
void Player::Draw()
{
	/*m_model->PostEffectDraw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
}