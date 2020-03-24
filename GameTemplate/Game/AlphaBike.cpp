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
	m_model->Init(L"Assets/modelData/Bike2.cmo");
	//バイクの移動処理を初期化
	if (m_playerBikeFlag == false)
	{
		m_bikeMove = new BikeMove_Enemy();
	}
	

}

AlphaBike::~AlphaBike()
{
	delete m_model;
	delete m_bikeMove;
	//g_goMgr.DeleteGameObject(this);
}

void AlphaBike::Update()
{
	
	//バイクの移動処理を実行する。
//  m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
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