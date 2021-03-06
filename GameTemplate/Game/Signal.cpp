#include "stdafx.h"
#include "Signal.h"
#include "GameTime.h"
#include "SoundSource.h"

Signal::Signal()
{
	m_se.Init(L"Assets/sound/CountDown.wav");
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

	if (SignalSE == false && SignalGenerate == true && m_changetimer > 15.0f) {

		m_se.Play(false);
		SignalSE = true;
	}

		//左シグナルが赤
		if (SignalGenerate == true && m_changetimer == 15.0f)
		{
			m_modelLeftSig.Init(L"Assets/modelData/SignalLeft_Red.cmo");
			m_leftpos = { 1.5f, 150.0f, -20.0f };
		}
		//中央シグナルが赤
		if (SignalGenerate == true && m_changetimer == 35.0f)
		{
			m_modelLeftSig.Init(L"Assets/modelData/SignalLeft.cmo");
			m_leftpos = { 1.5f, 150.0f, -20.0f };

			m_modelMiddleSig.Init(L"Assets/modelData/SignalMiddle_Red.cmo");
			m_middlepos = { 1.5f, 150.0f, -20.0f };
		}
		//右シグナルが赤
		if (SignalGenerate == true && m_changetimer == 55.0f)
		{
			m_modelLeftSig.Init(L"Assets/modelData/SignalLeft.cmo");
			m_leftpos = { 1.5f, 150.0f, -20.0f };

			m_modelMiddleSig.Init(L"Assets/modelData/SignalMiddle.cmo");
			m_leftpos = { 1.5f, 150.0f, -20.0f };

			m_modelRightSig.Init(L"Assets/modelData/SignalRight_Red.cmo");
			m_middlepos = { 1.5f, 150.0f, -20.0f };
		}
		//全てのシグナルが青
		if (SignalGenerate == true && m_changetimer == 75.0f)
		{
			m_modelLeftSig.Init(L"Assets/modelData/SignalLeft_Green.cmo");
			m_leftpos = { 1.5f, 150.0f, -20.0f };

			m_modelMiddleSig.Init(L"Assets/modelData/SignalMiddle_Green.cmo");
			m_leftpos = { 1.5f, 150.0f, -20.0f };

			m_modelRightSig.Init(L"Assets/modelData/SignalRight_Green.cmo");
			m_middlepos = { 1.5f, 150.0f, -20.0f };
		}
		
		//SignalSE = true;
	
	
	//信号が青の時、Go!スプライトを出す。
	if (SignalGenerate == true && m_changetimer == 75.0f && GoSpriteInitFlag == false)
	{
		m_spriteGo.Init(L"Assets/sprite/Go.dds", 1290.0f, 800.0f);
		m_gorot.SetRotationDeg(CVector3::AxisY(), 180.0f);
		m_goscale = { 0.0f, 0.0f, 0.0f };
		m_gopos = { 0.0f, 150.0f, 0.0f };
		GoSpriteInitFlag = true;
	}

	//Go!の拡大
	if (GoSpriteInitFlag == true && GoSpriteExpFlag == false)
	{
		if (m_goscale.x < 0.5f, m_goscale.y < 0.5f, m_goscale.z < 0.5f)
		{
			m_goscale.x = m_goscale.x + 0.1f;
			m_goscale.y = m_goscale.y + 0.1f;
			m_goscale.z = m_goscale.z + 0.1f;
		}
		else {
			//拡大された
			GoSpriteExpFlag = true;
		}
	}

	if (GoSpriteExpFlag == true)
	{
		if (m_Gorottimer != 10.0f)
		{
			m_Gorottimer++;
		}
		
		if (m_Gorottimer == 10.0f)
		{
			//回転させる
			CQuaternion addRot;
			addRot.SetRotationDeg(CVector3::AxisZ(), 45.0f);
			m_gorot *= addRot;
			//縮小させる
			if (GoSpriteReduFlag == false)
			{
				if (m_goscale.x > 0.1f, m_goscale.y > 0.1f)
				{
					m_goscale.x = m_goscale.x - 0.1f;
					m_goscale.y = m_goscale.y - 0.1f;
				}
				else
				{
					GoSpriteReduFlag = true;
				}
			}
			
		}
		//透明にする
		if (GoSpriteReduFlag == true && m_goscale.x == 0.1f, m_goscale.y == 0.1f)
		{
			if (m_spriteGo.GetAlpha() != 0.0f)
			{
				m_spriteGo.DeltaAlpha(-0.2f);
			}
		}
			
	}

	if (SignalGenerate == true)
	{
		m_modelHontai.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_modelLeftSig.UpdateWorldMatrix(m_leftpos, m_leftrot, m_leftscale);
		m_modelMiddleSig.UpdateWorldMatrix(m_middlepos, m_middlerot, m_middlescale);
		m_modelRightSig.UpdateWorldMatrix(m_rightpos, m_rightrot, m_rightscale);
	}
	
	if (GoSpriteInitFlag == true)
	{
		m_spriteGo.UpdateWorldMatrix(m_gopos, m_gorot, m_goscale);
	}
	
	
}

void Signal::Render()
{
	if (SignalGenerate == true) 
	{
		m_modelHontai.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		m_modelLeftSig.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		m_modelMiddleSig.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
		m_modelRightSig.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	
}


void Signal::Render2D()
{
	if (GoSpriteInitFlag == true)
	{
		Draw();
	}
	
}

void Signal::Draw()
{
	if (SignalGenerate == true)
	{
		CMatrix mView;
		CMatrix mProj;
		mView.MakeLookAt(
			{ 0, 0, 1 },
			{ 0, 0, 0 },
			{ 0, 1, 0 }
		);
		mProj.MakeOrthoProjectionMatrix(
			FRAME_BUFFER_W, FRAME_BUFFER_H, 0.1, 100);
		m_spriteGo.Draw(mView, mProj);
	}
	
}