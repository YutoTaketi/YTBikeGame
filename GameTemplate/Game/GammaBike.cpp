#include "stdafx.h"
#include "GammaBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"


GammaBike::GammaBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/Bike3.cmo");
	
}


GammaBike::~GammaBike()
{
	//g_goMgr.DeleteGameObject(this);
	delete m_model;
	delete m_bikeMove;
}

void GammaBike::Update()
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
	m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	
}

void GammaBike::Render()
{
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void GammaBike::Draw()
{

}