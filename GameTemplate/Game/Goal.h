#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "physics/Physics.h"
class Game;
class EpsilonBike;
class Goal : public IGameObject
{
public:
	Goal();
	~Goal();

	void Update();

	void SetGame(Game* game)
	{
		m_game = game;
		//m_bikeMove->SetGame(game);
	}
	/// <summary>
	/// �z�u�����S�[���|�C���g�̍��W���擾
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �z�u�����S�[���|�C���g�̃X�P�[�����擾
	/// </summary>
	/// <param name="sale"></param>
	void SetScale(CVector3 sale)
	{
		m_scale = sale;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	PhysicsGhostObject* GetGoalPoint()
	{
		return &m_ghostObject;
	}

	
private:
	void Render();
	void Draw();
	
	CVector3 m_position = CVector3::Zero();  //���W
	CVector3 m_scale = CVector3::One();      //�X�P�[��
	CQuaternion m_rotation = CQuaternion::Identity();  //��]
	PhysicsGhostObject m_ghostObject;     //�S�[�X�g�I�u�W�F�N�g
	
	Game* m_game;
	EpsilonBike m_epsilonbike;
};

