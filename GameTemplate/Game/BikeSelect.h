#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
class BikeSelect : public  IGameObject
{
public:
	BikeSelect();
	~BikeSelect();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();   //���W
	CVector3 m_scale = CVector3::One();       //�X�P�[��
	CQuaternion m_rotation = CQuaternion::Identity(); //��]
	Sprite m_sprite;
};

