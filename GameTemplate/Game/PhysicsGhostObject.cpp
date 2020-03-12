#include "stdafx.h"
#include "PhysicsGhostObject.h"
#include "physics/ICollider.h"
#include "physics/Physics.h"

PhysicsGhostObject::PhysicsGhostObject()
{
}
PhysicsGhostObject::~PhysicsGhostObject()
{
	Release();
}

void PhysicsGhostObject::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = std::make_unique<BoxCollider>();
	m_collider = std::move(boxCollider);
	CreateCommon(pos, rot);
}

void PhysicsGhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
		g_physics.RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}

void PhysicsGhostObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	
	m_ghostObject.setCollisionShape(m_collider->GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);
	//物理エンジンに登録
	g_physics.AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}