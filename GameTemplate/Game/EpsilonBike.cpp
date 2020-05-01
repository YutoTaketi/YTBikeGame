#include "stdafx.h"
#include "EpsilonBike.h"
#include "Game.h"
#include "BikeMove.h"
#include "BikeMove_Enemy.h"
#include "BikeMove_Player.h"


EpsilonBike::EpsilonBike()
{
	m_model = new  SkinModel();
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model->Init(L"Assets/modelData/Bike5.cmo");
	//�o�C�N�̈ړ�������������
	
}


EpsilonBike::~EpsilonBike()
{
	delete m_model;
	delete m_bikeMove;
}

void EpsilonBike::Update()
{


	//�o�C�N�̈ړ�������������
	//COM�o�C�N�̎�
	if (m_playerBikeFlag == false && m_bikeMoveDecision == false)
	{
		m_bikeMove = new BikeMove_Enemy();
		m_bikeMove->SetGame(m_game);
		m_bikeMove->GetPassObject(m_pointList);
		m_bikeMoveDecision = true;
	}
	//�v���C���[�o�C�N�̎�
	if (m_playerBikeFlag == true && m_bikeMoveDecision == false)
	{
		m_bikeMove = new BikeMove_Player();
		m_bikeMove->SetGame(m_game);
		m_bikeMove->SetGoal(m_goal);
		m_bikeMoveDecision = true;
	}

	/*if ( m_game->GetFinishFlag() == false) {
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
	/*
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			m_bikeMove->Syukaihantei = true;
		}
	});
	*/
	
	//�o�C�N�̈ړ����������s����B
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