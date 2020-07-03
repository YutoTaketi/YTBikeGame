#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "graphics/Sprite.h"

class SkinModel;
class BikeMaster;
class GameTime;
class Signal : public IGameObject
{
public:
	Signal();
	~Signal();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	void SetSentaku()
	{
		SelectFlag = true;
	}
private:
	//本体用
	CVector3 m_position = CVector3::Zero();               //座標
	CQuaternion m_rotation = CQuaternion::Identity();     //回転
	CVector3 m_scale = CVector3::One();                   //拡大率

	//左ライト用
	CVector3 m_leftpos = CVector3::Zero();               //座標
	CQuaternion m_leftrot = CQuaternion::Identity();     //回転
	CVector3 m_leftscale = CVector3::One();              //拡大率

	//中心ライト用
	CVector3 m_middlepos = CVector3::Zero();               //座標
	CQuaternion m_middlerot = CQuaternion::Identity();     //回転
	CVector3 m_middlescale = CVector3::One();              //拡大率

	//右ライト用
	CVector3 m_rightpos = CVector3::Zero();               //座標
	CQuaternion m_rightrot = CQuaternion::Identity();     //回転
	CVector3 m_rightscale = CVector3::One();              //拡大率

	//Goスプライト用
	CVector3 m_gopos = CVector3::Zero();               //座標
	CQuaternion m_gorot = CQuaternion::Identity();     //回転
	CVector3 m_goscale = CVector3::One();              //拡大率

	bool SelectFlag = false;                           //バイクがセレクトされているかの判定
	bool SignalGenerate = false;                       //信号機が作られたかの判定
	bool GoSpriteInitFlag = false;                     //Go!スプライトが初期化されたかのフラグ
	bool GoSpriteExpFlag = false;                      //Go!スプライトが拡大されたかのフラグ

	void Render();                                     //3D用
	void Render2D();                                   //2D用
	void Draw();
	SkinModel m_modelHontai;                       //シグナル本体
	SkinModel m_modelLeftSig;                      //シグナル左ライト
	SkinModel m_modelMiddleSig;                    //シグナル中心ライト
	SkinModel m_modelRightSig;                     //シグナル右ライト
	Sprite    m_spriteGo;                               //スプライト
	float m_changetimer = 0.0f;                    //信号モデル変更用タイマー
	

};

