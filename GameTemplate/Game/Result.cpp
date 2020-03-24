#include "stdafx.h"
#include "Result.h"
#include "Title.h"

Result::Result()
{
	m_sprite.Init(L"Assets/sprite/NijiSeeds.dds", 1000.0f, 800.0f);
}


Result::~Result()
{
}

void Result::Update()
{
	m_sprite.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	Draw();
	if (g_pad[0].IsTrigger(enButtonB)) {
		g_goMgr.DeleteGameObject(this);
		g_goMgr.NewGO<Title>();
	}
}

void Result::Render()
{
	
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