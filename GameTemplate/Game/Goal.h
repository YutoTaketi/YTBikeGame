#pragma once
#include "GameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "physics/Physics.h"
#include "graphics/SkinModel.h"
class Game;
class EpsilonBike;
class BikeMaster;
class SkinModel;
class Goal : public IGameObject
{
public:
	Goal();
	~Goal();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// Game�̃|�C���^���Z�b�g����
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		
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
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ��]��Ԃ�
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �S�[�X�g�I�u�W�F�N�g��Ԃ�
	/// </summary>
	/// <returns></returns>
	PhysicsGhostObject& GetGoalPoint()
	{
		return m_ghostObject;
	}

	CVector3 m_position = CVector3::Zero();  //���W
	CVector3 m_scale = CVector3::One();      //�X�P�[��
	CQuaternion m_rotation = CQuaternion::Identity();  //��]
private:
	void Render();
	void Draw();
	
	
	PhysicsGhostObject m_ghostObject;     //�S�[�X�g�I�u�W�F�N�g
	SkinModel* m_model;                   //���W
	Game* m_game;                         //Game�|�C���^
	
	BikeMaster* m_bikemaster;             //�o�C�N�}�X�^�[�̃|�C���^
	bool MakeGoalFlag = false;            //�S�[���쐬�t���O
};