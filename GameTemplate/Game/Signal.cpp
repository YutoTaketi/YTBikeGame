#include "stdafx.h"
#include "Signal.h"
#include "GameTime.h"

Signal::Signal()
{
	
}

Signal::~Signal()
{

}

void Signal::Update()
{
	//ライト部分が縞模様の信号機を出す
	if (SelectFlag == true && SignalGenerate == false)
	{
		//本体
		m_modelHontai.Init(L"Assets/modelData/SignalHontai.cmo");
		m_position = {0.0f, 150.0f, 0.0f};
		m_rotation.SetRotationDeg(CVector3::AxisY(), 180.0f);

		//左ライト
		m_modelLeftSig.Init(L"Assets/modelData/SignalLeft.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };

		//中心ライト
		m_modelMiddleSig.Init(L"Assets/modelData/SignalMiddle.cmo");
		m_middlepos = { 1.5f, 150.0f, -20.0f };

		//右ライト
		m_modelRightSig.Init(L"Assets/modelData/SignalRight.cmo");
		m_rightpos = { 1.5f, 150.0f, -20.0f };
		
		SignalGenerate = true;
	}
	
	//信号が出たらカウント開始
	if (SignalGenerate == true)
	{
		m_changetimer++;
	}

	if (SignalGenerate == true && m_changetimer == 15.0f)
	{
		m_modelLeftSig.Init(L"Assets/modelData/SignalLeft_Red.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };
	}

	if (SignalGenerate == true && m_changetimer == 35.0f)
	{
		m_modelLeftSig.Init(L"Assets/modelData/SignalLeft.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };

		m_modelMiddleSig.Init(L"Assets/modelData/SignalMiddle_Red.cmo");
		m_middlepos = { 1.5f, 150.0f, -20.0f };
	}

	if (SignalGenerate == true && m_changetimer == 55.0f)
	{
		m_modelLeftSig.Init(L"Assets/modelData/SignalLeft.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };

		m_modelMiddleSig.Init(L"Assets/modelData/SignalMiddle.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };

		m_modelRightSig.Init(L"Assets/modelData/SignalRight_Red.cmo");
		m_middlepos = { 1.5f, 150.0f, -20.0f };
	}

	if (SignalGenerate == true && m_changetimer == 75.0f)
	{
		m_modelLeftSig.Init(L"Assets/modelData/SignalLeft_Green.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };

		m_modelMiddleSig.Init(L"Assets/modelData/SignalMiddle_Green.cmo");
		m_leftpos = { 1.5f, 150.0f, -20.0f };

		m_modelRightSig.Init(L"Assets/modelData/SignalRight_Green.cmo");
		m_middlepos = { 1.5f, 150.0f, -20.0f };
	}

	m_modelHontai.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_modelLeftSig.UpdateWorldMatrix(m_leftpos, m_leftrot, m_leftscale);
	m_modelMiddleSig.UpdateWorldMatrix(m_middlepos, m_middlerot, m_middlescale);
	m_modelRightSig.UpdateWorldMatrix(m_rightpos, m_rightrot, m_rightscale);
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
		m_modelMiddleSig.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		m_modelRightSig.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	
}

void Signal::Draw()
{

}