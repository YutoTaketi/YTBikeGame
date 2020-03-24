#include "stdafx.h"
#include "BikeSelect.h"
#include "BikeMaster.h"

BikeSelect::BikeSelect()
{
	m_sprite.Init(L"Assets/sprite/BikeSelect.dds", 1000.0f, 800.0f);
}


BikeSelect::~BikeSelect()
{
}

void BikeSelect::Update()
{
	if (GetAsyncKeyState('0'))
	{
		
		m_select = true;

	}
	else if (GetAsyncKeyState('1'))
	{
		m_select = true;
	}
	else if (GetAsyncKeyState('2'))
	{
		m_select = true;
	}
	else if (GetAsyncKeyState('3'))
	{
		m_select = true;
	}
	else if (GetAsyncKeyState('4'))
	{
		m_select = true;
	}
	if ( m_select == true)
	{
		g_goMgr.DeleteGameObject(this);
	}


	m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_sprite.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	Draw();
}

void BikeSelect::Render()
{

}

void BikeSelect::Draw()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		{ 0, 0, 1 },
		{ 0, 0, 0 },
		{ 0, 1, 0 }
	);
	mProj.MakeOrthoProjectionMatrix(
		FRAME_BUFFER_W, FRAME_BUFFER_H, 0.1, 100);
	m_sprite.Draw(mView, mProj);
}