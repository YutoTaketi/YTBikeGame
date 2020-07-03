#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "graphics/Sprite.h"

class SkinModel;
class BikeMaster;
class GameTime;
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
	//�{�̗p
	CVector3 m_position = CVector3::Zero();               //���W
	CQuaternion m_rotation = CQuaternion::Identity();     //��]
	CVector3 m_scale = CVector3::One();                   //�g�嗦

	//�����C�g�p
	CVector3 m_leftpos = CVector3::Zero();               //���W
	CQuaternion m_leftrot = CQuaternion::Identity();     //��]
	CVector3 m_leftscale = CVector3::One();              //�g�嗦

	//���S���C�g�p
	CVector3 m_middlepos = CVector3::Zero();               //���W
	CQuaternion m_middlerot = CQuaternion::Identity();     //��]
	CVector3 m_middlescale = CVector3::One();              //�g�嗦

	//�E���C�g�p
	CVector3 m_rightpos = CVector3::Zero();               //���W
	CQuaternion m_rightrot = CQuaternion::Identity();     //��]
	CVector3 m_rightscale = CVector3::One();              //�g�嗦

	//Go�X�v���C�g�p
	CVector3 m_gopos = CVector3::Zero();               //���W
	CQuaternion m_gorot = CQuaternion::Identity();     //��]
	CVector3 m_goscale = CVector3::One();              //�g�嗦

	bool SelectFlag = false;                           //�o�C�N���Z���N�g����Ă��邩�̔���
	bool SignalGenerate = false;                       //�M���@�����ꂽ���̔���
	bool GoSpriteInitFlag = false;                     //Go!�X�v���C�g�����������ꂽ���̃t���O
	bool GoSpriteExpFlag = false;                      //Go!�X�v���C�g���g�傳�ꂽ���̃t���O

	void Render();                                     //3D�p
	void Render2D();                                   //2D�p
	void Draw();
	SkinModel m_modelHontai;                       //�V�O�i���{��
	SkinModel m_modelLeftSig;                      //�V�O�i�������C�g
	SkinModel m_modelMiddleSig;                    //�V�O�i�����S���C�g
	SkinModel m_modelRightSig;                     //�V�O�i���E���C�g
	Sprite    m_spriteGo;                               //�X�v���C�g
	float m_changetimer = 0.0f;                    //�M�����f���ύX�p�^�C�}�[
	

};

