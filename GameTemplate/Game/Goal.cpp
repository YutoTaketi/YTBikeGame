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
	//���̃S�[������@��ŃS�[�X�g�ɕύX0
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

