#include "stdafx.h"
#include "EpsilonBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"
#include "GameTime.h"

EpsilonBike::EpsilonBike()
{
	m_model = new  SkinModel();
	//cmoファイルの読み込み。
	m_model->Init(L"Assets/modelData/Bike5.cmo");
	//バイクの移動処理を初期化
	if (m_playerBikeFlag == false)
	{

	}
	m_bikeMove = new BikeMove_Player();
	//m_charaCon.Init(30.0f, 100.0f, m_position);
	//m_ghostObject.CreateBox(m_goalpos, CQuaternion::Identity(), { 100.0f, 0.0f, 200.0f });
}


EpsilonBike::~EpsilonBike()
{
	delete m_model;
	delete m_bikeMove;
}

void EpsilonBike::Update()
{
	
	if ( m_game->GetFinishFlag() == false) {
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
	}
	/*
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			m_bikeMove->Syukaihantei = true;
		}
	});
	*/
	
	//バイクの移動処理を実行する。
	m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
	//m_charaCon.Execute(m_moveSpeed, SetGameTime().GetFrameDeltaTime());
	m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

	
}

void EpsilonBike::Render()
{

}

void EpsilonBike::Draw()
{

}