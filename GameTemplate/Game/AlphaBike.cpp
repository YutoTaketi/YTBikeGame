#include "stdafx.h"
#include "AlphaBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"
#include "Goal.h"


AlphaBike::AlphaBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/PlayerBike1.cmo");
	m_scale = m_gamescale;
}

AlphaBike::~AlphaBike()
{
	delete m_model;
	delete m_bikeMove;
	//g_goMgr.DeleteGameObject(this);
	
}

void AlphaBike::Update()
{
	//バイクの移動処理を初期化
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
  m_model->UpdateWorldMatrix(m_position, m_rotation, m_scale);
  //シャドウマップの作成
  ShadowMap::GetInstance().Update(
	  m_position + CVector3::AxisY() * 300.0f + CVector3::AxisX() * -300.0f,
	  m_position );
  m_model->SetShadowReciever(true);
}

void AlphaBike::Render()
{
	m_model->Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void AlphaBike::Draw()
{

}