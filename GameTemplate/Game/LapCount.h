#pragma once
#include "GameObjectManager.h"
#include "Font.h"
//class Font;
class BikeSelect;
class LapCount : public IGameObject
{
public:
	LapCount();
	~LapCount();

	void Update();
	/// <summary>
	/// BikeMasterのポインタを渡す。
	/// </summary>
	/// <param name="game"></param>
	void SetBikeSelect(BikeSelect* bikeselect)
	{
		m_bikeselect = bikeselect;

	}
private:
	void Render();
	void Draw();

	CVector2 m_Fontpos = CVector2::Zero();
	CVector4 m_color = CVector4::White();
	CVector2 m_Fontscale = CVector2::One();
	CVector2 pivot = CVector2::Zero();
	float rot = 0.0f;

	//ラップ数で変わる
	CVector2 m_Fontpos2 = CVector2::Zero();
	CVector4 m_color2 = CVector4::White();
	CVector2 m_Fontscale2 = CVector2::One();
	CVector2 pivot2 = CVector2::Zero();
	float rot2 = 0.0f;

	
	Font* m_font;
	Font* m_font2;
	BikeSelect* m_bikeselect;
};

