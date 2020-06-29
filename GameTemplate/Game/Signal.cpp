#include "stdafx.h"
#include "Signal.h"

Signal::Signal()
{
	
}

Signal::~Signal()
{

}

void Signal::Update()
{
	if (SelectFlag == true && SignalGenerate == false)
	{
		m_model.Init(L"Assets/modelData/SignalHontai.cmo");
		m_position = {0.0f, 150.0f, 0.0f};
		m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);
		SignalGenerate = true;
	}
	
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Signal::Render()
{
	if (SignalGenerate == true) 
	{
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	
}

void Signal::Draw()
{

}