#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
class ItemWaku : public IGameObject
{
public:
	ItemWaku();
	~ItemWaku();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();      //���W
	CVector3 m_scale = CVector3::One();          //�g�嗦
	//CQuaternion m_rotation = CQuaternion::Identity();
	Sprite m_sprite;   //�X�v���C�g
};

