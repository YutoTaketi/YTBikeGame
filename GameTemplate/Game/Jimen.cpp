#include "stdafx.h"
#include "Jimen.h"
#include "graphics/SkinModel.h"


Jimen::Jimen()
{
	m_model.Init(L"Assets/modelData/CourseJimen.cmo");

	//�ÓI�����I�u�W�F�N�g���쐬
	m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
	//�@���}�b�v�����[�h
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),
		L"Assets/modelData/Jimen_normal.dds",
		0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		false,
		nullptr,
		&m_normalMapSRV
	);
	m_model.SetNormalMap(m_normalMapSRV);
}

Jimen::~Jimen()
{
	//todo �@���}�b�v������B
	if (m_normalMapSRV != nullptr) {
		m_normalMapSRV->Release();
	}
}

void Jimen::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Jimen::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Jimen::Draw()
{

}