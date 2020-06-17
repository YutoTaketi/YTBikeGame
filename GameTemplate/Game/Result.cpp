#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Font.h"
#include "graphics/GraphicsEngine.h"

Result::Result()
{
	m_sprite.Init(L"Assets/sprite/Result.dds", 1000.0f, 800.0f);
	m_firstplace = new Font();
	m_secondplace = new Font();
	m_thirdplace = new Font();
	m_fourthplace = new Font();
	m_fifthplace = new Font();
	m_Firstplacepos = { 350.0f, 159.0f };
	m_Secondplacepos = { 350.0f, 263.0f };
	m_Thirdplacepos = { 350.0f, 382.0f };
	m_Fourthplacepos = { 350.0f, 510.0f };
	m_Fifthplacepos = { 350.0f, 630.0f };
}


Result::~Result()
{
}

void Result::Update()
{
	
	if (g_pad[0].IsTrigger(enButtonB)) {
		g_goMgr.DeleteGameObject(this);
		g_goMgr.NewGO<Title>();
	}
}

void Result::Render()
{
	m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_sprite.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	Draw();
	//1位の表示
	m_firstplace->DrawScreenPos(
		L"Player",
		m_Firstplacepos,
		m_color,
		m_Fontscale,
		pivot,
		rot,
		DirectX::SpriteEffects_None
	);

	//2位の表示
	m_secondplace->DrawScreenPos(
		L"COM",
		m_Secondplacepos,
		m_color2,
		m_Fontscale2,
		pivot2,
		rot2,
		DirectX::SpriteEffects_None
	);

	//3位の表示
	m_thirdplace->DrawScreenPos(
		L"COM",
		m_Thirdplacepos,
		m_color3,
		m_Fontscale3,
		pivot3,
		rot3,
		DirectX::SpriteEffects_None
	);

	//4位の表示
	m_fourthplace->DrawScreenPos(
		L"COM",
		m_Fourthplacepos,
		m_color4,
		m_Fontscale4,
		pivot4,
		rot4,
		DirectX::SpriteEffects_None
	);

	//5位の表示
	m_fifthplace->DrawScreenPos(
		L"COM",
		m_Fifthplacepos,
		m_color5,
		m_Fontscale5,
		pivot5,
		rot5,
		DirectX::SpriteEffects_None
	);
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