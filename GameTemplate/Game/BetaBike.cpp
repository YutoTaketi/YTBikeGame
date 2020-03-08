#include "stdafx.h"
#include "BetaBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"


BetaBike::BetaBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/Bike3.cmo");
	//バイクの移動処理を初期化
	m_bikeMove = new BikeMove_Enemy();
}


BetaBike::~BetaBike()
{
}

void BetaBike::Update()
{
	//バイクの移動処理を実行する。
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