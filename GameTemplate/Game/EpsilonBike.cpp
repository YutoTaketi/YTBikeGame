#include "stdafx.h"
#include "EpsilonBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"


EpsilonBike::EpsilonBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/Bike5.cmo");
	
	
}


EpsilonBike::~EpsilonBike()
{
	delete m_model;
	delete m_bikeMove;
}

void EpsilonBike::Update()
{


	//バイクの移動処理を初期化
	//COMバイクの時
	if (m_playerBikeFlag == false && m_bikeMoveDecision == false)
	{
		m_bikeMove = new BikeMove_Enemy();
		m_bikeMove->SetGame(m_game);
		m_bikeMove->GetPassObject(m_pointList);
		m_bikeMoveDecision = true;
	}
	//プレイヤーバイクの時
	if (m_playerBikeFlag == true && m_bikeMoveDecision == false)
	{
		m_bikeMove = new BikeMove_Player();
		m_bikeMove->SetGame(m_game);
		m_bikeMove->SetGoal(m_goal);
		m_bikeMoveDecision = true;
	}

	
	
	
	//バイクの移動処理を実行する。
	m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	//m_charaCon.Execute(m_moveSpeed, SetGameTime().GetFrameDeltaTime());
	m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	

	
}

void EpsilonBike::Render()
{
	m_model->Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void EpsilonBike::Draw()
{

}