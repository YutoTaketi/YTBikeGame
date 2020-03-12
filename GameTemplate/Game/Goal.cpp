#include "stdafx.h"
#include "Goal.h"


Goal::Goal()
{
	m_ghostObject.CreateBox(m_position, CQuaternion::Identity(), { 200.0f,200.0f, 200.0f });
}


Goal::~Goal()
{
}

void Goal::Update()
{

}
void Goal::Render()
{

}

void Goal::Draw()
{

}

