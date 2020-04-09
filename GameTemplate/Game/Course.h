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
	/// çXêVä÷êî
	/// </summary>
	void Update();

	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
private:
	void Render();
	void Draw();

	SkinModel m_model;
	PhysicsStaticObject m_phyStaticObject;
	
};

