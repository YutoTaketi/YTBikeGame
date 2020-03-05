#pragma once
#include "GameObjectManager.h"
#include "graphics/SkinModel.h"
#include "BikeController.h"
#include "graphics/SkinModel.h"

//�G�o�C�N�P�̃N���X
class UnionBike : public IGameObject
{
public:
	UnionBike();
	~UnionBike();
	
	void Update();


	const std::map<int, Point*>& GetPassObject(const std::map<int, Point*>& List)
	{
		m_pointList = List;
		m_point = m_pointList[1];
		return m_pointList;
	}

	//Game�̃|�C���^��n��
	void SetGame(Game* game)
	{
		m_game = game;
	}

private:
	void Move();
	void Turn();
	void Render();
	void Draw();

	CVector3 m_position = { 5.0f, 0.0f, 0.0f };  //���W
	CVector3 m_moveSpeed = CVector3::Zero(); //�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity(); //��]
	SkinModel* m_model;          //�X�L�����f���B
	Game* m_game;

	CVector3 m_accel = CVector3::Zero();    //�����x
	CVector3 m_forward = CVector3::AxisZ();   //�G�l�~�[�̑O������

	float m_accelNum = 30.0f;        //�������l
	float m_friction = 0.98f;        //���C�W��

	BikeController* m_bikecontroller;

	std::map<int, Point*> m_pointList;  //�|�C���g�\���̂̔z��
	Point* m_point;                  //�|�C���g�̍\���̂̃|�C���^�A���݂̖ړI�n

};

