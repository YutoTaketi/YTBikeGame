#pragma once
#include "graphics/RenderTarget.h"
#include "level/Level.h"
#include "GameObjectManager.h"
#include "GameCamera.h"
#include "ItemWaku.h"
#include "BikeMove_Enemy.h"
#include "Goal.h"
#include "Result.h"
#include "graphics/ShadowMap.h"
#include "SoundEngine.h"

//�|�X�g�G�t�F�N�g�֘A
#include "graphics/RenderTarget.h"
#include "graphics/ShadowMap.h"
#include "graphics/Sprite.h"
#include "graphics/SkinModel.h"
#include "BikeMove_Enemy.h"

class ItemWaku;
class CoursePath;
class BikeMove_Enemy;
class BetaBike;
class Goal;
class BikeSelect;
class BikeMaster;
class Course;
class LapCount;
class Kyakuseki;
class Road;
class Jimen;
class Signal;
class Guest;
//class Sky;
/// <summary>

/// �Q�[���N���X
/// </summary>
/// 
/*struct Point {
	CVector3 s_position;
	int s_number;
};*/
class Game : public IGameObject
{
	
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Game();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Game();


public:
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();
	/// <summary>
	/// �V���O���g���p�^�[��
	/// </summary>
	
	/// <summary>
	/// �V���h�E�}�b�v���擾
	/// </summary>
	/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		//return &m_shadowMap;
	}
	//���̃|�C���g��Ԃ�
	Point* GetNextNumber(int number)
	{
		if (m_pointList.count(number + 1) == 0) {
			return m_pointList[1];
		}
		else {
			return m_pointList[number + 1];
		}
	}
	/// <summary>
	/// �p�X�ړ��̃|�C���g��Ԃ�
	/// </summary>
	/// <returns></returns>
	Point* GetGorlPoint()
	{
		return m_pointList[1];
	}
	/// <summary>
	/// ���b�v�J�E���g
	/// </summary>
	/// <returns></returns>
	bool LapCountUp()
	{
		lapcheck += 1;
		return true;
	}
	/// <summary>
	/// ���b�v�`�F�b�N
	/// </summary>
	/// <returns></returns>
	bool GetLapCheck()
	{
		return lapcheck;
	}
	
	/// <summary>
	/// �t�B�j�b�V���t���O�̍X�V
	/// </summary>
	void ChangeFinishFlag()
	{
		finishFlag = true;
	}
	/// <summary>
	/// �t�B�j�b�V���t���O��Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetFinishFlag()
	{
		return finishFlag;
	}


private:
	/// <summary>
	/// �v�������_�����O
	/// </summary>
	void PreRender();
	/// <summary>
	/// �t�H���[�h�����_�����O
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// �|�X�g�����_�����O
	/// </summary>
	void PostRender();

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ�
	/// </summary>
	/// <param name="d3dDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

	/// <summary>
	/// �V���h�E�}�b�v���擾�B
	/// </summary>
	/// <returns></returns>
	/*ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}*/
private:
	//�I�t�X�N���[�������_�����O
	//SkinModel m_playerModelDraw;       //�v���C���[�̕`�揈��
	//SkinModel m_enemyModelDraw;        //�G�o�C�N�̕`�揈��
	//SkinModel m_stageModelDraw;        //�X�e�[�W�̕`�揈��
	//RenderTarget m_mainRenderTarget;
	//ShadowMap m_shadowMap;

	//Sprite m_copyMainRtToFrameBufferSprite;         //���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;          //�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;   //�t���[���o�@�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;   //�t���[���o�@�t�@�̃f�v�X�X�e���V���r���[�B

	SoundEngine m_soundEngine;    //�T�E���h�G���W��

	//�I�u�W�F�N�g�̃|�C���^
	Level level;	//���x��
	
	ItemWaku* itemwaku = nullptr;  //�A�C�e���\���̘g
	Goal* goal = nullptr;
	BikeSelect* bikeselect = nullptr;   //�o�C�N�̑I�����
	BikeMaster* bikemaster = nullptr;   //�o�C�N�̐�����S��
	Course* course = nullptr;           //�R�[�X
	Kyakuseki* kyakuseki = nullptr;     //�q��
	Road* road = nullptr;               //�R�[�X
	Jimen* jimen = nullptr;             //�n��
	Signal* signal = nullptr;           //�V�O�i��
	Guest* guest = nullptr;
	//Sky* sky = nullptr;

	LapCount* lapcount = nullptr;       //����J�E���g
	ShadowMap m_shadowMap;              //�V���h�E�}�b�v
	int lapcheck = 0;  //���b�v�`�F�b�N
	
	bool finishFlag = false;       //�t�B�j�b�V���t���O
	bool bikesentakuFlag = false;  //�o�C�N�I���t���O

	std::map<int , Point*> m_pointList;  //�p�X�̃��X�g
	
};

//extern Game &g_game;