#pragma once
#include "GameObjectManager.h"
//#include "graphics/SkinModel.h"
#include "physics/PhysicsStaticObject.h"
class SkinModel;
class Course : public IGameObject
{
public:
	Course();
	~Course();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��Ԃ�
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	CVector3 m_position = CVector3::Zero();               //���W
	CQuaternion m_rotation = CQuaternion::Identity();     //��]
	CVector3 m_scale = CVector3::One();                    //�g�嗦
private:
	void Render();
	void Draw();

	SkinModel m_model;                       //�X�L�����f��
	PhysicsStaticObject m_phyStaticObject;   //�ÓI�����I�u�W�F�N�g
	
};

