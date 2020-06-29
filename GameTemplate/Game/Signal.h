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
	CVector3 m_position = CVector3::Zero();               //座標
	CQuaternion m_rotation = CQuaternion::Identity();     //回転
	CVector3 m_scale = CVector3::One();                    //拡大率

	bool SelectFlag = false;
	bool SignalGenerate = false;
	void Render();
	void Draw();
	SkinModel m_model;                       //スキンモデル
	//PhysicsStaticObject m_phyStaticObject;   //静的物理オブジェクト
	//ID3D11ShaderResourceView* m_normalMapSRV = nullptr;

};

