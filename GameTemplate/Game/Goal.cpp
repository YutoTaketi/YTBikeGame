#include "stdafx.h"
#include "Goal.h"
#include "EpsilonBike.h"

Goal::Goal()
{
	
	MakeGoalFlag = false;
}


Goal::~Goal()
{
	g_goMgr.DeleteGameObject(this);
}

void Goal::Update()
{
	if (MakeGoalFlag == false)
	{
		m_ghostObject.CreateBox(m_position, m_rotation, m_scale);
		MakeGoalFlag = true;
	}
	//仮のゴール判定　後でゴーストに変更0
	/*
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject)
	{
			if (m_ghostObject.IsSelf(contactObject) == true)
			{

			}
	});*/
	
}
void Goal::Render()
{

}

void Goal::Draw()
{

}

