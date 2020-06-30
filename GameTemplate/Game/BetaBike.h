#pragma once
#include "GameObjectManager.h"
#include "graphics/SkinModel.h"
#include "BikeController.h"

class Game;
class BikeMove;

class BetaBike : public IGameObject
{
public:
	BetaBike();
	~BetaBike();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <returns></returns>
	CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ���x��Ԃ�
	/// </summary>
	/// <returns></returns>
	CVector3 GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/// <summary>
	/// Game�N���X�ō�����p�X�̏����擾����B
	/// </summary>
	/// <param name="List"></param>
	/*void GetPassObject(const std::map<int, Point*>& List)
	{
		m_bikeMove->GetPassObject(List);
	}*/
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

	/// <summary>
	/// Goal�̃|�C���^��n��
	/// </summary>
	/// <param name="goal"></param>
	void SetGoal(Goal* goal)
	{
		m_goal = goal;
	}
	/// <summary>
	/// �v���C���[�o�C�N�t���O�̍X�V
	/// </summary>
	void ChangePlayerBikeFlag()
	{
		m_playerBikeFlag = true;
	}
private:
	void Render();
	void Draw();

	CVector3 m_position = { 180.0f, 0.0f, 0.0f };      //���W
	CVector3 m_moveSpeed = CVector3::Zero();          //�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity(); //��]
	SkinModel* m_model;                               //�X�L�����f���B
	Game* m_game;                                      //Game�̃|�C���^
	Goal* m_goal;                                      //Goal�̃|�C���^
	CVector3 m_accel = CVector3::Zero();              //�����x
	CVector3 m_forward = CVector3::AxisZ();           //�G�l�~�[�̑O������

	float m_accelNum = 300.0f;        //�������l
	float m_friction = 0.98f;        //���C�W��



	std::map<int, Point*> m_pointList;  //�|�C���g�\���̂̔z��
	Point* m_point;                  //�|�C���g�̍\���̂̃|�C���^�A���݂̖ړI�n
	BikeMove* m_bikeMove = nullptr;  //�o�C�N���[�u�̃|�C���^
	bool m_playerBikeFlag = false;     //�v���C���[�o�C�N���ǂ����̃t���O�B
	bool m_bikeMoveDecision = false;   //�o�C�N�𓮂������������肵�����̃t���O�B
};

