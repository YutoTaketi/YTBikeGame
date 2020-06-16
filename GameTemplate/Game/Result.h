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

	//2位表示用のメンバ変数
	CVector2 m_Secondplacepos = CVector2::Zero();  //座標
	CVector4 m_color2 = CVector4::White();         //カラー
	CVector2 m_Fontscale2 = CVector2::One();       //フォント拡大率
	CVector2 pivot2 = CVector2::Zero();            //ピボット
	float rot2 = 0.0f;                             //回転

	//3位表示用のメンバ変数
	CVector2 m_Thirdplacepos = CVector2::Zero();  //座標
	CVector4 m_color3 = CVector4::White();         //カラー
	CVector2 m_Fontscale3 = CVector2::One();       //フォント拡大率
	CVector2 pivot3 = CVector2::Zero();            //ピボット
	float rot3 = 0.0f;                             //回転

	//4位表示用のメンバ変数
	CVector2 m_Fourthplacepos = CVector2::Zero();  //座標
	CVector4 m_color4 = CVector4::White();         //カラー
	CVector2 m_Fontscale4 = CVector2::One();       //フォント拡大率
	CVector2 pivot4 = CVector2::Zero();            //ピボット
	float rot4 = 0.0f;                             //回転

	//5位表示用のメンバ変数
	CVector2 m_Fifthplacepos = CVector2::Zero();  //座標
	CVector4 m_color5 = CVector4::White();         //カラー
	CVector2 m_Fontscale5 = CVector2::One();       //フォント拡大率
	CVector2 pivot5 = CVector2::Zero();            //ピボット
	float rot5 = 0.0f;                             //回転

	Sprite m_sprite;  //リザルトスプライト
	Font* m_firstplace;  //一位
	Font* m_secondplace; //二位
	Font* m_thirdplace;  //三位
	Font* m_fourthplace; //四位
	Font* m_fifthplace;  //五位
};

