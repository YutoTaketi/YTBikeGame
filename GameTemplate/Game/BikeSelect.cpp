#include "stdafx.h"
#include "BikeSelect.h"
#include "BikeMaster.h"

BikeSelect::BikeSelect()
{
	m_sprite.Init(L"Assets/sprite/BikeSelect.dds", 1000.0f, 800.0f);
	m_sentakuwaku.Init(L"Assets/sprite/BikeSentakuWaku.dds", 600.0f, 600.0f);
	m_sentakupos = m_wakupos;
}


BikeSelect::~BikeSelect()
{
}

void BikeSelect::Update()
{
	//選択された番号をセット
	if (GetAsyncKeyState('0'))
	{
		m_bikemaster->SetSentakuNo(0); 
			m_select = true;
	}
	else if (GetAsyncKeyState('1'))
	{
		m_bikemaster->SetSentakuNo(1);
		m_select = true;
	}
	else if (GetAsyncKeyState('2'))
	{
		m_bikemaster->SetSentakuNo(2);
		m_select = true;
	}
	else if (GetAsyncKeyState('3'))
	{
		m_bikemaster->SetSentakuNo(3);
		m_select = true;
	}
	else if (GetAsyncKeyState('4'))
	{
		m_bikemaster->SetSentakuNo(4);
		m_select = true;
	}


	if (wakuNo == 0 && g_pad[0].IsTrigger(enButtonB))
	{
		 sentakuNo = 0;
	}
	
	if (sentakuNo == 0)
	{
		m_bikemaster->SetSentakuNo(0);
		m_select = true;
	}


	if ( m_select == true)
	{
		g_goMgr.DeleteGameObject(this);
	}
	

	m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	
	m_sprite.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	m_sentakuwaku.UpdateWorldMatrix(m_sentakupos, m_wakurot, m_wakuscale);
	
}

void BikeSelect::Render()
{
	Draw();
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

	m_sentakuwaku.Draw(mView, mProj);
}