#include "stdafx.h"
#include "Goal.h"


Goal::Goal()
{
	//�S�[�X�g�g���ƃG���[���o��B
	m_ghostObject.CreateBox(m_position, CQuaternion::Identity(), { 200.0f,200.0f, 200.0f });
}


Goal::~Goal()
{
}

void Goal::Update()
{
	//���̃S�[������@��ŃS�[�X�g�ɕύX

}
void Goal::Render()
{

}

void Goal::Draw()
{

}

