#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"

class SkinModel;
class Guest : public IGameObject
{
public:
	Guest();
	~Guest();

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
	//�q�̃A�j���[�V����
	/*enum EnAnimationClip {
		enAnimationClip_Guest_Idle,
		enAnimationClip_Guest_Kobusi,
		enAnimationClip_num
	};*/

	CVector3 m_position = CVector3::Zero();               //���W
	CQuaternion m_rotation = CQuaternion::Identity();     //��]
	CVector3 m_scale = CVector3::One();                   //�g�嗦

	void Render();
	void Draw();

	SkinModel m_model;                       //�X�L�����f��
	PhysicsStaticObject m_phyStaticObject;   //�ÓI�����I�u�W�F�N�g
	//Animation m_animation;
	//AnimationClip m_animationClip[enAnimationClip_num];    //�A�j���[�V�����N���b�v
	//EnAnimationClip m_EnAnimationClip;
};

