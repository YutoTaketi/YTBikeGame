#include "stdafx.h"
#include "BetaBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"


BetaBike::BetaBike()
{
	m_model = new  SkinModel();
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model->Init(L"Assets/modelData/Bike3.cmo");
	//�o�C�N�̈ړ�������������
	m_bikeMove = new BikeMove_Enemy();
}


BetaBike::~BetaBike()
{
}

void BetaBike::Update()
{
	//�o�C�N�̈ړ����������s����B
	//m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void BetaBike::Render()
{

}

void BetaBike::Draw()
{

}