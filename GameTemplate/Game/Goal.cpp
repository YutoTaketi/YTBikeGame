#include "stdafx.h"
#include "Goal.h"


Goal::Goal()
{
	//ゴースト使うとエラーが出る。
	m_ghostObject.CreateBox(m_position, CQuaternion::Identity(), { 200.0f,200.0f, 200.0f });
}


Goal::~Goal()
{
}

void Goal::Update()
{
	//仮のゴール判定　後でゴーストに変更

}
void Goal::Render()
{

}

void Goal::Draw()
{

}

