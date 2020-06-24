#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"

class SkinModel;
class Kyakuseki : public IGameObject
{
public:
	Kyakuseki();
	~Kyakuseki();

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
	/// <summary>
	/// �g�嗦��Ԃ�
	/// </summary>
	/// <param name="sclae"></param>
	void SetSclae(CVector3 sclae)
	{
		m_scale = sclae;
	}
	
private:
	CVector3 m_position = CVector3::Zero();               //���W
	CQuaternion m_rotation = CQuaternion::Identity();     //��]
	CVector3 m_scale = CVector3::One();                    //�g�嗦

	void Render();
	void Draw();
	SkinModel m_model;                       //�X�L�����f��
	PhysicsStaticObject m_phyStaticObject;   //�ÓI�����I�u�W�F�N�g
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;
};

