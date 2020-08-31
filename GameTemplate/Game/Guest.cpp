#include "stdafx.h"
#include "Guest.h"
#include "graphics/SkinModel.h"

Guest::Guest()
{
	m_model.Init(L"Assets/modelData/Guest.cmo");
	//�ÓI�����I�u�W�F�N�g���쐬
	//m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);

	//�A�j���[�V�����N���b�v�̃��[�h
	m_animationClip[enAnimationClip_Guest_Idle].Load(L"Assets/animData/Guest_Idle.tka");
	//���[�v�t���O�̐ݒ�
	m_animationClip[enAnimationClip_Guest_Idle].SetLoopFlag(true);
	m_animation.Init(m_model, m_animationClip, enAnimationClip_num);
	//m_animation.Play(enAnimationClip_Guest_Idle, 0.2f);

	m_model.SetShadowReciever(true);
}
Guest::~Guest()
{

}

void Guest::Update()
{
	m_animation.Play(enAnimationClip_Guest_Idle, 0.0f);
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

