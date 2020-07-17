#include "stdafx.h"
#include "Goal.h"
#include "EpsilonBike.h"
#include "BikeMove_Player.h"
#include "BikeMaster.h"
#include "graphics/SkinModel.h"
Goal::Goal()
{
	m_model = new SkinModel();
	MakeGoalFlag = false;
    m_model->Init(L"Assets/modelData/TestGoal.cmo");
}


Goal::~Goal()
{
	g_goMgr.DeleteGameObject(this);
}

void Goal::Update()
{
	if (MakeGoalFlag == false)
	{
		m_ghostObject.CreateBox(m_position, m_rotation, {1000.0f, 10.0f, 10.0f});
		MakeGoalFlag = true;
	}
	//m_model->UpdateWorldMatrix(m_position, m_rotation, m_scale);
	/*m_model->Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
	
}
void Goal::Render()
{
	m_model->UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model->Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Goal::Draw()
{

}

