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
	/// 更新関数
	/// </summary>
	void Update();
private:
	void Render();
	void Draw();
	CVector3 m_position = CVector3::Zero();  //リザルトスプライトの座標
	CVector3 m_scale = CVector3::One();      //リザルトスプライトの拡大
	CQuaternion m_rotation = CQuaternion::Identity(); //リザルトスプライトの回転

	//1位表示用のメンバ変数
	CVector2 m_Firstplacepos = CVector2::Zero();  //座標
	CVector4 m_color = CVector4::White();         //カラー
	CVector2 m_Fontscale = CVector2::One();       //フォント拡大率
	CVector2 pivot = CVector2::Zero();            //ピボット
	float rot = 0.0f;                             //回転

	Sprite m_sprite;  //リザルトスプライト
	Font* m_firstplace;  //一位

};

