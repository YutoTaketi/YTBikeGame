#include "stdafx.h"
#include "Goal.h"
#include "EpsilonBike.h"

Goal::Goal()
{
	
	m_ghostObject.CreateBox(m_position, m_rotation, m_scale);
}


Goal::~Goal()
{
	//g_goMgr.DeleteGameObject(this);
}

void Goal::Update()
{
	//仮のゴール判定　後でゴーストに変更
	
	g_physics.ContactTest(m_epsilonbike.GetCharaCon(), [&](const btCollisionObject& contactObject)
	{

	});
	
}
void Goal::Render()
{

}

void Goal::Draw()
{

}

