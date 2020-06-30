#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"

class SkinModel;
class BikeMaster;
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


	bool SelectFlag = false;
	bool SignalGenerate = false;
	void Render();
	void Draw();
	SkinModel m_modelHontai;                       //シグナル本体
	SkinModel m_modelLeftSig;                      //シグナル左ライト
	SkinModel m_modelMiddleSig;                    //シグナル中心ライト
	SkinModel m_modelRightSig;                     //シグナル右ライト
	//PhysicsStaticObject m_phyStaticObject;   //静的物理オブジェクト
	//ID3D11ShaderResourceView* m_normalMapSRV = nullptr;

};

