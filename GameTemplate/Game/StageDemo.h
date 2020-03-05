#pragma once
#include "GameObjectManager.h"
#include "physics/PhysicsStaticObject.h"


class StageDemo : public IGameObject
{
public:
	StageDemo();
	~StageDemo();
	void Update();
	void Draw();
	void Render();

	CVector3 m_position = CVector3::Zero();              //座標
	CQuaternion m_rotation = CQuaternion::Identity();    //回転
	CVector3 m_scale = CVector3::One();                  //スケール

	
	SkinModel m_model;
	PhysicsStaticObject m_phyStaticObject;
};

