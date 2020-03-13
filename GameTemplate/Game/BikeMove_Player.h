#pragma once

#include "BikeMove.h"
#include "BikeController.h"
#include "Game.h"
/// <summary>
/// �v���C���[�̃o�C�N�𓮂����B
/// </summary>
class Game;
class BikeMove_Player : public BikeMove
{
public:
	BikeMove_Player();
	~BikeMove_Player();

	

	/// <summary>
	/// �v���C���[���g�p����o�C�N�̍X�V�֐�
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum,float& friction);
	CVector3 m_moveDirectionF = CVector3::Zero();     //�ړ�����
	CVector3 playermae = { 0, 0, 1 };                 //�o�C�N�̑O����
	CVector3 sinkouhoukou = g_camera3D.GetForward();  //�i�s����
	BikeController* m_bikecontroller;                 //�o�C�N�̓��ϊO�όv�Z������B

	Game* m_game;
	
};

