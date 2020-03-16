#include "stdafx.h"
#include "Result.h"


Result::Result()
{
	m_sprite.Init(L"Assets/sprite/Tyaika.dds", 1000.0f, 800.0f);
}


Result::~Result()
{
}

void Result::Update()
{
	m_sprite.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	Draw();
}

void Result::Render()
{
	g_goMgr.DeleteGameObject(this);
}

void Result::Draw()
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