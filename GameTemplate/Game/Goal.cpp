#include "stdafx.h"
#include "Goal.h"


Goal::Goal()
{
	
	m_ghostObject.CreateBox(m_position, CQuaternion::Identity(), { 200.0f,200.0f, 200.0f });
}


Goal::~Goal()
{
	g_goMgr.DeleteGameObject(this);
}

void Goal::Update()
{
	//���̃S�[������@��ŃS�[�X�g�ɕύX
	
	if (m_game->GetFinishFlag() == true)
	{
		g_goMgr.DeleteGameObject(this);
	}
	
}
void Goal::Render()
{

}

void Goal::Draw()
{

}

