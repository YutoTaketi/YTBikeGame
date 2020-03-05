#include "stdafx.h"
#include "StageDemo.h"
#include "level/Level.h"

StageDemo::StageDemo()
{
	m_model.Init(L"Assets/modelData/Course.cmo");
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_phyStaticObject.CreateMeshObject(m_model, CVector3::Zero(), CQuaternion::Identity());
	
}


StageDemo::~StageDemo()
{
}

void StageDemo::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void StageDemo::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	/*m_model.PostEffectDraw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
}

void StageDemo::Render()
{
   //m_shadowMap.RegistShadowCaster(&m_model);
}