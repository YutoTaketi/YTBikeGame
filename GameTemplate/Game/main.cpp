#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "StageDemo.h"
#include "level/Level.h"
#include "GameObjectManager.h"
#include <iostream>
#include "Game.h"
#include "Title.h"
#include "Result.h"
//Game* g_game = nullptr;
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	/*g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);*/
	
	
	//Game *game;
   // game = g_goMgr.NewGO<Game>();

	Title *title;
	title = g_goMgr.NewGO<Title>();

	//Result *result;
	//result = g_goMgr.NewGO<Result>();
	//g_game = &Game::GetInstance();
	//g_game = g_goMgr.NewGO<Game>();
     
	
	

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		
		//�Q�[���̍X�V����
		//game->Update();
		//title->Update();
		g_goMgr.Update();
		
		
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}