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
	//���̃S�[������@��ŃS�[�X�g�ɕύX
	m_charaCon = m_epsilonbike->GetCharaCon();
	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject)
	{
			if (m_ghostObject.IsSelf(contactObject) == true)
			{

			}
	});
	
}
void Goal::Render()
{

}

void Goal::Draw()
{

}

