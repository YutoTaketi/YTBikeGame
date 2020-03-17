#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "graphics/SkinModel.h"

Title::Title()
{
	m_sprite.Init(L"Assets/sprite/Tyaika.dds", 1000.0f, 800.0f);
	//m_model.Init(L"Assets/modelData/PlayerBike.cmo");
}


Title::~Title()
{
	
}

void Title::Update()
{
	m_sprite.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	Draw();
	/*
	m_model.UpdateWorldMatrix(m_bikepos, m_bikerot, m_bikescale);
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
	if (g_pad[0].IsTrigger(enButtonA)) {
		g_goMgr.DeleteGameObject(this);
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