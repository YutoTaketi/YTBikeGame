#pragma once
#include "GameObjectManager.h"
#include "graphics/Sprite.h"
#include "Font.h"
#include "FontRender.h"
//class Font;

class FontRender;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();            //座標
	CVector3 m_scale = CVector3::One();                //拡大率
	CQuaternion m_rotation = CQuaternion::Identity();  //回転

	CVector2 m_Fontpos = CVector2::Zero();             //フォント座標
	CVector4 m_color = CVector4::White();              //カラー
	CVector2 m_Fontscale = CVector2::One();            //フォント拡大率
	CVector2 pivot = CVector2::Zero();                 //ピボット
	float rot = 0.0f;                                  //回転

	
	Sprite m_sprite;  //スプライト
	
	Font* m_font;     //フォント
	FontRender m_fontrender;
};

