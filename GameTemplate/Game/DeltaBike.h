#pragma once
#include "GameObjectManager.h"
#include "graphics/SkinModel.h"
#include "BikeController.h"

class Game;
class BikeMove;

class DeltaBike : public IGameObject
{
public:
	DeltaBike();
	~DeltaBike();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
	
	CVector3 GetPosition() const
	{
		return m_position;
	}


	/// <summary>
	/// Game�N���X�ō�����p�X�̏����擾����B
	/// </summary>
	/// <param name="List"></param>
	void GetPassObject(const std::map<int, Point*>& List)
	{
		m_bikeMove->GetPassObject(List);
	}

	/// <summary>
	/// Game�̃|�C���^��n���B
	/// </summary>
	/// <param name="game"></param>
	void SetGame(Game* game)
	{
		m_game = game;
		m_bikeMove->SetGame(game);
	}

private:
	void Render();
	void Draw();

	CVector3 m_position = { -50.0f, 0.0f, 0.0f };      //���W
	CVector3 m_moveSpeed = CVector3::Zero();           //�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity();  //��]
	SkinModel* m_model;                                //�X�L�����f���B
	Game* m_game;

	CVector3 m_accel = CVector3::Zero();                //�����x
	CVector3 m_forward = CVector3::AxisZ();             //�G�l�~�[�̑O������

	float m_accelNum = 40.0f;                           //�������l
	float m_friction = 0.98f;                           //���C�W��

	BikeController* m_bikecontroller;

	std::map<int, Point*> m_pointList;  //�|�C���g�\���̂̔z��
	Point* m_point;                  //�|�C���g�̍\���̂̃|�C���^�A���݂̖ړI�n
	BikeMove* m_bikeMove = nullptr;
	bool m_playerBikeFlag = false;    //�v���C���[�o�C�N���ǂ����̃t���O
};

