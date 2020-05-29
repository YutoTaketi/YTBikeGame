#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
#include "Font.h"
class Result : public IGameObject
{
public:
	Result();
	~Result();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();  //���U���g�X�v���C�g�̍��W
	CVector3 m_scale = CVector3::One();      //���U���g�X�v���C�g�̊g��
	CQuaternion m_rotation = CQuaternion::Identity(); //���U���g�X�v���C�g�̉�]

	//1�ʕ\���p�̃����o�ϐ�
	CVector2 m_Firstplacepos = CVector2::Zero();  //���W
	CVector4 m_color = CVector4::White();         //�J���[
	CVector2 m_Fontscale = CVector2::One();       //�t�H���g�g�嗦
	CVector2 pivot = CVector2::Zero();            //�s�{�b�g
	float rot = 0.0f;                             //��]

	Sprite m_sprite;  //���U���g�X�v���C�g
	Font* m_firstplace;  //���

};

