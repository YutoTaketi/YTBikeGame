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
	//cmo�t�@�C���̓ǂݍ��݁B
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
	//�o�C�N�̈ړ�������������
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

	//�o�C�N�̈ړ����������s����B
  m_bikeMove->Execute(m_position, m_rotation, m_moveSpeed, m_accel, m_accelNum, m_friction);
  m_model->UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
  
 
}

void AlphaBike::Render()
{
	m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void AlphaBike::Draw()
{

}