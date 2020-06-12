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
	m_Firstplacepos = { 350.0f, 155.0f };
	m_Secondplacepos = { 350.0f, 260.0f };
}


Result::~Result()
{
}

void Result::Update()
{
	m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
	m_sprite.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	Draw();
	//1ˆÊ‚Ì•\Ž¦
	m_firstplace->DrawScreenPos(
		L"Player",
		m_Firstplacepos,
		m_color,
		m_Fontscale,
		pivot,
		rot,
		DirectX::SpriteEffects_None
	);

	//2ˆÊ‚Ì•\Ž¦
	m_secondplace->DrawScreenPos(
	    L"COM",
		m_Secondplacepos,
		m_color2,
		m_Fontscale2,
		pivot2,
		rot2,
		DirectX::SpriteEffects_None
	);





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