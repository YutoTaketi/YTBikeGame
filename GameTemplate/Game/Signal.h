#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"

class SkinModel;
class BikeMaster;
class Signal : public IGameObject
{
public:
	Signal();
	~Signal();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	void SetSentaku()
	{
		SelectFlag = true;
	}
private:
	CVector3 m_position = CVector3::Zero();               //���W
	CQuaternion m_rotation = CQuaternion::Identity();     //��]
	CVector3 m_scale = CVector3::One();                    //�g�嗦

	bool SelectFlag = false;
	bool SignalGenerate = false;
	void Render();
	void Draw();
	SkinModel m_model;                       //�X�L�����f��
	//PhysicsStaticObject m_phyStaticObject;   //�ÓI�����I�u�W�F�N�g
	//ID3D11ShaderResourceView* m_normalMapSRV = nullptr;

};

