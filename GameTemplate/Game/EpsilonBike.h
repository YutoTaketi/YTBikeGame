#pragma once
#include "GameObjectManager.h"
#include "graphics/SkinModel.h"
#include "BikeController.h"

class Game;
class BikeMove;

class PhysicsWorld;
class CharacterController;
class Goal;
class PhysicsGhostObject;
class EpsilonBike : public IGameObject
{
public:
	EpsilonBike();
	~EpsilonBike();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();


	CVector3 GetPosition() const
	{
		return m_position;
	}


	/// <summary>
	/// �p�X�ړ��Ɋւ���֐��Ɣz��
	/// </summary>
	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{

		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	/// <summary>
	/// Game�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
	}
	//�v���C���[�Ȃ�؂�ւ���B
	void ChangePlayerBikeFlag()
	{
		m_playerBikeFlag = true;
	}
	/*CharacterController GetCharaCon()
	{
		return m_charaCon;
	}*/
private:
	void Render();
	void Draw();

	CVector3 m_position = { 200.0f, 0.0f, 0.0f };      //���W
	CVector3 m_moveSpeed = CVector3::Zero();          //�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity(); //��]
	CVector3 m_pointOnePos = CVector3::Zero();
	SkinModel* m_model;                               //�X�L�����f���B
	//CharacterController m_charaCon;
	PhysicsWorld m_physics;
	Goal goal;
	//GameTime m_gameTime;
	Game* m_game = nullptr;

	CVector3 m_accel = CVector3::Zero();    //�����x
	CVector3 m_forward = CVector3::AxisZ();   //�G�l�~�[�̑O������

	float m_accelNum = 80.8f;        //�������l
	float m_friction = 0.98f;        //���C�W��

	BikeController* m_bikecontroller;
	
	std::map<int, Point*> m_pointList;  //�|�C���g�\���̂̔z��
	Point* m_point;                  //�|�C���g�̍\���̂̃|�C���^�A���݂̖ړI�n
	
	BikeMove* m_bikeMove = nullptr;

	CVector3 m_goalpos = { 0.0f, 0.0f, 1150.0f };
	PhysicsGhostObject m_ghostObject;     //�S�[�X�g�I�u�W�F�N�g
	bool m_playerBikeFlag = false;    //�v���C���[�o�C�N���ǂ����̃t���O
	bool m_bikeMoveDecision = false;   //�o�C�N�𓮂������������肵�����̃t���O�B
};

