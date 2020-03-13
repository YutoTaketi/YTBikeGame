#pragma once
#include "character/CharacterController.h"
#include "GameObjectManager.h"
#include "BikeController.h"
//#include "graphics/SkinModel.h"
//#include "graphics/Camera.h"
class BikeMove;
class Game;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
    CVector3 GetPosition() const
	{
		return m_position;
	}
	
	
private:
	
	void Render();
	void Draw();
private:
	CVector3 m_position = CVector3::Zero();            //���W
	CQuaternion m_rotation = CQuaternion::Identity();  //��]
	CVector3 m_moveSpeed = CVector3::Zero();           //�ړ����x
	CVector3 m_accel = CVector3::Zero();               //�����x
	SkinModel* m_model;								   //�X�L�����f���B
	CVector3 m_playermae = CVector3::Zero();           //�v���C���[�̑O�x�N�g��
	CVector3 m_sinkouhouku = CVector3::Zero();
	CVector3 m_moveDirectionF = CVector3::Zero();      //�J�����̑O����

	float m_accelNum = 1.8f;     //�������l
	float m_friction = 0.97f;    //���C�W��
	double SyukaihanteiOn = false;
	int syukaicount = 0;

	BikeController* m_bikecontroller = nullptr;
	BikeMove* m_bikeMove = nullptr;
	Game* m_game = nullptr;

	
};

