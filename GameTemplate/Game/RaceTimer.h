#pragma once
#include "GameObjectManager.h"

class RaceTimer : public IGameObject
{
public:
	RaceTimer();
	~RaceTimer();

	void Update();
private:
	void Render();
	void Draw();

	CVector2 m_Fontpos = CVector2::Zero();
	CVector4 m_color = CVector4::White();
	CVector2 m_Fontscale = CVector2::One();
	CVector2 pivot = CVector2::Zero();
	float rot = 0.0f;

	Font* m_font;
};

