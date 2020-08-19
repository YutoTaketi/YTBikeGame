#include "stdafx.h"
#include "Kyakuseki.h"
#include "graphics/SkinModel.h"

Kyakuseki::Kyakuseki()
{
	m_model.Init(L"Assets/modelData/Kyakuseki.cmo");
	
	//静的物理オブジェクトを作成
	m_phyStaticObject.CreateMeshObject(m_model, m_position, m_rotation);
	//法線マップをロード
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),
		L"Assets/modelData/kyakuseki_normal.dds",
		0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		false,
		nullptr,
		&m_normalMapSRV
	);
	m_model.SetNormalMap(m_normalMapSRV);
	//m_model.SetShadowReciever(true);
}

Kyakuseki::~Kyakuseki()
{
	//todo 法線マップを解放。
	if (m_normalMapSRV != nullptr) {
		m_normalMapSRV->Release();
	}
}

void Kyakuseki::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Kyakuseki::Render()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Kyakuseki::Draw()
{

}