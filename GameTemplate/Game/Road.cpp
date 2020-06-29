#include "stdafx.h"
#include "Road.h"
#include "graphics/SkinModel.h"

Road::Road()
{
	m_model.Init(L"Assets/modelData/Course01_Road.cmo");

	//静的物理オブジェクトを作成
	m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
	//法線マップをロード
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),
		L"Assets/modelData/road_normal.dds",
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

Road::~Road()
{
	if (m_normalMapSRV != nullptr) {
		m_normalMapSRV->Release();
	}
}

void Road::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Road::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Road::Draw()
{

}