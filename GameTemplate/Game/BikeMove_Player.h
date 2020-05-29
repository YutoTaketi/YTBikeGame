#pragma once

#include "BikeMove.h"
#include "BikeController.h"
#include "Game.h"
#include "character/CharacterController.h"
#include "GameTime.h"
/// <summary>
/// �v���C���[�̃o�C�N�𓮂����B
/// </summary>
class Game;
class CharacterController;
class GameTime;
class Goal;
class BikeMove_Player : public BikeMove
{
public:
	BikeMove_Player();
	~BikeMove_Player();

	/// <summary>
	/// �L�����R����Ԃ�
	/// </summary>
	/// <returns></returns>
	CharacterController& GetCharaCon()
	{
		return m_charaCon;
	}


	/// <summary>
	/// �v���C���[���g�p����o�C�N�̍X�V�֐�
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	void Execute(CVector3& m_position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum,float& friction);
	CVector3 m_position = CVector3::Zero();
	CVector3 m_moveDirectionF = CVector3::Zero();     //�ړ�����
	CVector3 playermae = { 0, 0, 1 };                 //�o�C�N�̑O����
	CVector3 sinkouhoukou = g_camera3D.GetForward();  //�i�s����
	BikeController* m_bikecontroller;                 //�o�C�N�̓��ϊO�όv�Z������B
	
	
	CharacterController m_charaCon;       //�L�����N�^�[�R���g���[���[
	PhysicsGhostObject m_ghostObject;     //�S�[�X�g�I�u�W�F�N�g

	int timer = 0;                        //�S�[�X�g�I�u�W�F�N�g�Ƃ̓����蔻��p�^�C�}�[
	bool m_CharaConInitFlag = false;     //�L�����N�^�[�R���g���[���[������������Ă��邩�̃t���O
};

