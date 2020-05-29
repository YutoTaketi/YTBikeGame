#pragma once
#include "GameObjectManager.h"
//#include "graphics/SkinModel.h"
#include "physics/PhysicsStaticObject.h"
class SkinModel;
class Course : public IGameObject
{
public:
	Course();
	~Course();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();
	/// <summary>
	/// 座標を返す
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を返す
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	CVector3 m_position = CVector3::Zero();               //座標
	CQuaternion m_rotation = CQuaternion::Identity();     //回転
	CVector3 m_scale = CVector3::One();                    //拡大率
private:
	void Render();
	void Draw();

	SkinModel m_model;                       //スキンモデル
	PhysicsStaticObject m_phyStaticObject;   //静的物理オブジェクト
	
};

