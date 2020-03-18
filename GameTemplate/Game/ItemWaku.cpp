#include "stdafx.h"
#include "ItemWaku.h"


ItemWaku::ItemWaku()
{
	m_sprite.Init(L"Assets/sprite/Tyaika.dds",1000.0f, 800.0f);
	//m_scale = { 8.0f, 8.0f, 8.0f };
	//m_position.y = 200.0f;
	
}


ItemWaku::~ItemWaku()
{
	//g_goMgr.DeleteGameObject(this);
}
void ItemWaku::Update()
{
	m_sprite.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
	Draw();
	
}

void ItemWaku::Render()
{

}
void ItemWaku::Draw()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		{0, 0, 1},
		{0, 0, 0},
		{0, 1, 0}
	);
	mProj.MakeOrthoProjectionMatrix(
		FRAME_BUFFER_W, FRAME_BUFFER_H, 0.1, 100);
	m_sprite.Draw(mView, mProj);
}