#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "BikeMove_Player.h"
#include "EpsilonBike.h"
GameCamera::GameCamera()
{
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	m_toCameraPos.Set(0.0f, 50.0f, -150.0f);
	//g_camera3D.SetNear(1.0f);
	g_camera3D.SetFar(10000.0f);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	//�J�����X�V
	
	//�����_���王�_�ւ̃x�N�g�����v�Z����B
	//�S�[��������J�����𓮂����B
	
		//�����_�v�Z
		m_target = m_epsilonbike->GetPosition();
		m_target.y += 100.0f;


		CVector3 stick;
		CQuaternion qRot = CQuaternion::Identity();
		stick.x = g_pad[0].GetLStickXF();
		qRot.SetRotationDeg(CVector3::AxisY(), stick.x * 1.2f);
		qRot.Multiply(m_toCameraPos);
		m_position = m_target + m_toCameraPos;
		m_finishposition = m_position;


	
	

	g_camera3D.SetTarget(m_target);
	g_camera3D.SetPosition(m_position);

	
	
	g_camera3D.Update();
}
void GameCamera::Render()
{

}

void GameCamera::Draw()
{

}