#include "stdafx.h"
#include "Guest.h"
#include "graphics/SkinModel.h"

Guest::Guest()
{
	m_model.Init(L"Assets/modelData/Guest.cmo");
	//静的物理オブジェクトを作成
	//m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);

	//アニメーションクリップのロード
	m_animationClip[enAnimationClip_Guest_Idle].Load(L"Assets/animData/Guest_Idle.tka");
	m_animationClip[enAnimationClip_Guest_Kobusi].Load(L"Assets/animData/Guest_Kobusi.tka");
	//ループフラグの設定
	m_animationClip[enAnimationClip_Guest_Idle].SetLoopFlag(true);
	m_animationClip[enAnimationClip_Guest_Kobusi].SetLoopFlag(true);
	//初期化
	m_animation.Init(m_model, m_animationClip, enAnimationClip_num);
	//m_animation.Play(enAnimationClip_Guest_Idle, 0.2f);

	m_model.SetShadowReciever(true);
}
Guest::~Guest()
{

}

void Guest::Update()
{
	m_animation.Play(enAnimationClip_Guest_Kobusi, 0.2f);
	m_animation.Update(1.0f / 30.0f);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Guest::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Guest::Draw()
{
	
}

