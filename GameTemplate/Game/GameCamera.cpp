#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "BikeMove_Player.h"
#include "EpsilonBike.h"
#include "AlphaBike.h"
#include "BetaBike.h"
#include "DeltaBike.h"
#include "GammaBike.h"
#include "BikeMaster.h"
GameCamera::GameCamera()
{
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	m_toCameraPos.Set(0.0f, 50.0f, -150.0f);
	//g_camera3D.SetNear(1.0f);
	g_camera3D.SetFar(1000000.0f);
}


GameCamera::~GameCamera()
{
	//g_goMgr.DeleteGameObject(this);
}

void GameCamera::Update()
{
	
	//カメラ更新
	
	//注視点から視点へのベクトルを計算する。
	//ゴールしたらカメラを動かす。
	//if (m_PlayerBikeSetFlag == true)
	//{
		//注視点計算
	if (m_bikemaster->GetBikeNo() == 0)
	{
		m_target = m_alphabike->GetPosition();
	}
	else if (m_bikemaster->GetBikeNo() == 1)
	{
		m_target = m_betabike->GetPosition();
	}
	else if (m_bikemaster->GetBikeNo() == 2)
	{
		m_target = m_gammabike->GetPosition();
	}
	else if (m_bikemaster->GetBikeNo() == 3)
	{
		m_target = m_deltabike->GetPosition();
	}
	else if (m_bikemaster->GetBikeNo() == 4)
	{
		m_target = m_epsilonbike->GetPosition();
	}
		m_target.y += 100.0f;

		
		CVector3 stick;
		CQuaternion qRot = CQuaternion::Identity();
		stick.x = g_pad[0].GetLStickXF();
		qRot.SetRotationDeg(CVector3::AxisY(), stick.x * 1.2f);
		qRot.Multiply(m_toCameraPos);
		m_position = m_target + m_toCameraPos;
		m_finishposition = m_position;

	//}
		

	
	

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