#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
class ItemWaku : public IGameObject
{
public:
	ItemWaku();
	~ItemWaku();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();      //座標
	CVector3 m_scale = CVector3::One();          //拡大率
	//CQuaternion m_rotation = CQuaternion::Identity();
	Sprite m_sprite;   //スプライト
};

