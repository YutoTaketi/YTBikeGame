#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
#include "Font.h"
//class Font;
class Title : public IGameObject
{
public:
	Title();
	~Title();

	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();

	CVector2 m_Fontpos = CVector2::Zero();
	CVector4 m_color = CVector4::White();
	CVector2 m_Fontscale = CVector2::One();
	CVector2 pivot = CVector2::Zero();
	float rot = 0.0f;

	CVector3 m_bikepos = CVector3::Zero();
	CVector3 m_bikescale = CVector3::One();
	CQuaternion m_bikerot = CQuaternion::Identity();
	//CQuaternion m_rotation = CQuaternion::Identity();
	Sprite m_sprite;
	SkinModel m_model;
	Font* m_font;
};

