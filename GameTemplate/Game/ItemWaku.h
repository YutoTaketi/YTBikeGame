#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
class ItemWaku : public IGameObject
{
public:
	ItemWaku();
	~ItemWaku();

	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	//CQuaternion m_rotation = CQuaternion::Identity();
	Sprite m_sprite;
};

