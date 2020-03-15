#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	m_sprite.Init(L"Assets/sprite/Tyaika.dds", 1000.0f, 800.0f);
}


Title::~Title()
{
	
}

void Title::Update()
{
	m_sprite.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	Draw();
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		g_goMgr.NewGO<Game>();
	}
	

}

void Title::Render()
{

}
void Title::Draw()
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