#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "BikeSelect.h"
#include "graphics/SkinModel.h"
#include "Font.h"
#include "graphics/GraphicsEngine.h"
Title::Title()
{
	m_sprite.Init(L"Assets/sprite/Rider_Title.dds", 1290.0f, 800.0f);
	//m_model.Init(L"Assets/modelData/PlayerBike.cmo");
	m_font = new Font();
}


Title::~Title()
{
	
}

void Title::Update()
{
	m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_sprite.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	Draw();
	/*
	m_model.UpdateWorldMatrix(m_bikepos, m_bikerot, m_bikescale);
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
	m_font->DrawScreenPos(
	   L"Bike Operation",
	   m_Fontpos,
	   m_color,
	   m_Fontscale,
	   pivot,
	   rot,
	   DirectX::SpriteEffects_None
	);
	if (g_pad[0].IsTrigger(enButtonA)) {
		g_goMgr.DeleteGameObject(this);
		g_goMgr.NewGO<Game>();
		//g_goMgr.NewGO<BikeSelect>();
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