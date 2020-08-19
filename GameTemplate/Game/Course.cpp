#include "stdafx.h"
#include "Course.h"
#include "graphics/SkinModel.h"

Course::Course()
{
	//m_model = new  SkinModel();
	m_model.Init(L"Assets/modelData/Course01.cmo");

	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
	m_model.SetShadowReciever(true);
}


Course::~Course()
{
}

void Course::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	
}

void Course::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Course::Draw()
{

}