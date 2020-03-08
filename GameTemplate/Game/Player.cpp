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
	

void Player::Update()
{
	//�o�C�N�̈ړ����������s����B
	
	m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	//Turn();
	
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