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
		m_modelHontai.Init(L"Assets/modelData/SignalHontai.cmo");
		m_position = {0.0f, 150.0f, 0.0f};
		m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);

		m_modelLeftSig.Init(L"Assets/modelData/SignalLeft.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };
		
		SignalGenerate = true;
	}
	
	m_modelHontai.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_modelLeftSig.UpdateWorldMatrix(m_leftpos, m_leftrot, m_leftscale);
}

void Signal::Render()
{
	if (SignalGenerate == true) 
	{
		m_modelHontai.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		m_modelLeftSig.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		
	}
	
}

void Signal::Draw()
{

}