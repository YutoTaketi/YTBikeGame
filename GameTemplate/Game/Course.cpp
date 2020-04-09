#include "stdafx.h"
#include "Course.h"
#include "graphics/SkinModel.h"

Course::Course()
{
	//m_model = new  SkinModel();
	m_model.Init(L"Assets/modelData/Course01.cmo");

	//静的物理オブジェクトを作成。
	m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
}


Course::~Course()
{
}

void Course::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Course::Render()
{

}

void Course::Draw()
{

}