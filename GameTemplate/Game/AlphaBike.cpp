#include "stdafx.h"
#include "AlphaBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"

AlphaBike::AlphaBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/PlayerBike1.cmo");
	
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
		
		m_bikeMoveDecision = true;
	}

	//ゴールの判定

	/*if (m_game->GetFinishFlag() == false) {
		m_point = m_game->GetGorlPoint();
		CVector3 m_gorlpos = m_point->s_position;
		CVector3 m_gorltoPlayer = m_gorlpos - m_position;
		if (m_gorltoPlayer.Length() < 100.0)
		{
			m_bikeMove->Syukaihantei = true;
		}
		if (m_bikeMove->Syukaihantei == true && m_gorltoPlayer.Length() < 50.0)
		{
			m_game->SyuukaiCount();
		}
		if (m_game->GetFinishHantei() == 4)
		{
			m_game->ChangeFinishFlag();
		}
	}*/

	
	



	//バイクの移動処理を実行する。
  m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
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