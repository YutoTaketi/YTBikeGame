#include "stdafx.h"
#include "Game.h"
#include "level/Level.h"
#include "Player.h"
#include "Goal.h"
#include "ItemWaku.h"
#include "AlphaBike.h"
#include "BetaBike.h"
#include "GammaBike.h"
#include "DeltaBike.h"
#include "EpsilonBike.h"
#include "EpsilonBike.h"
#include "BikeSelect.h"
#include "BikeMaster.h"
//#include "StageDemo.h"



Game::Game()
{
	//���x���̏�����
	//coursepath = new CoursePath();
	level.Init(L"Assets/level/CourseLevelDemo2.tkl", [&]( const LevelObjectData objData) {
		
		if (wcsncmp(L"point", objData.name, 5) == 0) {
			int number = _wtoi(&objData.name[5]);
			Point* point = new Point();
			point->s_position = objData.position;
			point->s_number = number;
			m_pointList[number] = point;
			return true;
		}
		
		
		
		
		return false;
    });
	
	

	//player = g_goMgr.NewGO<Player>();
	//alphabike = g_goMgr.NewGO<AlphaBike>();
	//betabike = g_goMgr.NewGO<BetaBike>();
	//gammabike = g_goMgr.NewGO<GammaBike>();
	//deltabike = g_goMgr.NewGO<DeltaBike>();
	//epsilonbike = g_goMgr.NewGO<EpsilonBike>();
	//gamecamera = g_goMgr.NewGO<GameCamera>();
	bikemaster = g_goMgr.NewGO<BikeMaster>();
	bikemaster->SetGame(this);
	//bikemove_enemy = new BikeMove_Enemy();
	
	//gamecamera->SetBike(epsilonbike);
	//gamecamera->SetGame(this);
	//goal = g_goMgr.NewGO<Goal>();
	//goal->SetGame(this);
	//goal->SetBike(epsilonbike);
	/*m_bikemove_enemy.GetPassObject(m_pointList);
	m_bikemove_enemy.SetGame(this);*/
	
	
	
	//alphabike->SetGame(this);
	//alphabike->GetPassObject(m_pointList);
	//betabike->SetGame(this);
	//betabike->GetPassObject(m_pointList);
	//gammabike->SetGame(this);
	//gammabike->GetPassObject(m_pointList);
	//deltabike->SetGame(this);
	//deltabike->GetPassObject(m_pointList);

	//epsilonbike->SetGame(this);
	//epsilonbike->GetPassObject(m_pointList);
	
	//itemwaku = g_goMgr.NewGO<ItemWaku>();
	//�o�C�N�̑I�����
	bikeselect = g_goMgr.NewGO<BikeSelect>();
	bikeselect->SetBikeMaster(bikemaster);
	//�n�ʂ��V���h�E���V�[�o�[�ɂ���B
	//m_stageModelDraw.SetShadowReciever(true);

	//�����_�����O�^�[�Q�b�g�̍쐬
	//m_renderTarget.Create(FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R8G8B8A8_UNORM);
	//���C���ƂȂ郌���_�[�^�[�Q�b�g���쐬�B
	/*m_mainRenderTarget.Create(
	    FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);

	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
	m_copyMainRtToFrameBufferSprite.Init(
	     m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);*/
	

}


Game::~Game()
{
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}

	g_goMgr.DeleteGameObject(alphabike);
	g_goMgr.DeleteGameObject(betabike);
	g_goMgr.DeleteGameObject(gammabike);
	g_goMgr.DeleteGameObject(deltabike);
	g_goMgr.DeleteGameObject(epsilonbike);
	//g_goMgr.DeleteGameObject(itemwaku);
	g_goMgr.DeleteGameObject(gamecamera);
	g_goMgr.DeleteGameObject(goal);
	g_goMgr.DeleteGameObject(bikeselect);
	g_goMgr.DeleteGameObject(bikemaster);
}

void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
	   d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}
void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}

void Game::Update()
{
	//���x���̕`��
	if (bikemaster->GetbikesetFlag() == true)
	{
		level.Draw();
	}
	
	//�v���C���[�̕`��B
	//player->Update();
	//�G�̕`��
	//enemybike->Update();
	
	//�A�C�e���g�̕`��
	//itemwaku->Update();
	//bikeselect->Update();
	//alphabike->Update();
	//betabike->Update();
	//gammabike->Update();
	//deltabike->Update();
	//epsilonbike->Update();

	//bikeselect->Update();
	//�J����
	//gamecamera->Update();
	bikemaster->Update();
    //�X�e�[�W�̕`��
	//stagedemo->Update();
	
	//�V���h�E�L���X�^�[��o�^
	//m_shadowMap.RegistShadowCaster(&m_playerModelDraw);
	//m_shadowMap.RegistShadowCaster(&m_enemyModelDraw);
	//m_shadowMap.RegistShadowCaster(&m_stageModelDraw);
	///�V���h�E�}�b�v���X�V
	/**m_shadowMap.UpdateFromLightTarget(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }

	);*/

	if (finishhantei >= 4 )
	{
		
		g_goMgr.NewGO<Result>();
		g_goMgr.DeleteGameObject(this);
		
	}
}

void Game::PreRender()
{
	//�V���h�E�}�b�v�Ƀ����_�����O
	//m_shadowMap.RenderToShadowMap();
}

void Game::ForwordRender()
{
	/*
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	*/
	
	g_goMgr.Draw();
}

void Game::PostRender()
{
	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//�h���h��
	//m_copyMainRtToFrameBufferSprite.Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}

void Game::Render()
{
	//�`��J�n�B
	//g_graphicsEngine->BegineRender();


	/*
	//�`��J�n�B
	g_graphicsEngine->BegineRender();
	//�t���[���o�@�t�@�̃����_�����O�^�[�Q�b�g��
	//�o�b�N�A�b�v���Ă����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);

	//�v�������_�����O
	PreRender();

	//�t�H���[�h�����_�����O
	ForwordRender();

	//�|�X�g�����_�����O
	PostRender();
	
	//�`��I��
	g_graphicsEngine->EndRender();
	*/
}