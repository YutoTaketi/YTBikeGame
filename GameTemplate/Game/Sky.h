#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"

class SkinModel;
class Sky 
{
public:
	Sky();
	~Sky();

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
	/// <summary>
	/// 拡大率を返す
	/// </summary>
	/// <param name="sclae"></param>
	void SetSclae(CVector3 sclae)
	{
		m_scale = sclae;
	}

private:
	CVector3 m_position = CVector3::Zero();               //座標
	CQuaternion m_rotation = CQuaternion::Identity();     //回転
	CVector3 m_scale = CVector3::One();                    //拡大率

	void Render();
	void Draw();
	SkinModel m_model;                       //スキンモデル
};

