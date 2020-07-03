#pragma once
#include "BikeMove.h"
#include "BikeController.h"
#include "character/CharacterController.h"
/// <summary>
/// �G�̃o�C�N�𓮂����B
/// </summary>

class Game;
class CharacterController;
class BikeMove_Enemy : public BikeMove
{
public:
	BikeMove_Enemy();
	~BikeMove_Enemy();
	/// <summary>
	/// AI�œ����o�C�N�̍X�V�֐�
	/// </summary>
	/// <param name="position"></param>
	/// <param name="rotation"></param>
	/// <param name="movespeed"></param>
	/// <param name="accel"></param>
	/// <param name="accelnum"></param>
	/// <param name="friction"></param>
	void Execute(CVector3& position, CQuaternion& rotation, CVector3& movespeed, CVector3& accel, float& accelnum, float& friction);
	CVector3 m_moveDirectionF = CVector3::Zero();  //�O����
	BikeController* m_bikecontroller;   //�o�C�N�R���g���[���[�̃|�C���^
	CharacterController m_charaCon;     //�L�����N�^�[�R���g���[���[
	bool m_CharaConInitFlag = false;    //�L�����N�^�[�R���g���[���[������������Ă��邩�̃t���O
	bool m_AIStartFlag = false;         //AI������o�����߂̃t���O
	float m_StartTimer = 0.0f;          //AI������o���܂ł̃^�C�}�[

};