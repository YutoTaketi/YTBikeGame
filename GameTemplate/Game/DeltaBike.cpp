#include "stdafx.h"
#include "DeltaBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"


DeltaBike::DeltaBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/Bike4.cmo");
	//バイクの移動処理を初期化
	m_bikeMove = new BikeMove_Enemy();

}


DeltaBike::~DeltaBike()
{
	//g_goMgr.DeleteGameObject(this);
	delete m_model;
	delete m_bikeMove;
}

void DeltaBike::Update()
{
	
	//バイクの移動処理を実行する。
	//m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void DeltaBike::Render()
{

}

void DeltaBike::Draw()
{

}