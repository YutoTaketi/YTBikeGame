#pragma once
#include "IGameObject.h"
#include <vector>


//�|�X�g�G�t�F�N�g�֘A
#include "graphics/RenderTarget.h"
#include "graphics/ShadowMap.h"
#include "graphics/Sprite.h"
#include "graphics/SkinModel.h"
//#include "graphics/ShadowMap.h"

class GameObjectManager
{
public:
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	template<class T>
	 T* NewGO()
	{
		//�C���X�^���X�𐶐�����B
		T* newObj = new T;
		//���������C���X�^���X���ϒ��z��
		m_goList.push_back(newObj);
		return newObj;
	}
	 /// <summary>
	 /// /�Q�[���I�u�W�F�N�g�����X�g����폜����B
	 /// </summary>
	 /// <param name="go"></param>
	void DeleteGameObject(IGameObject* go)
	{
      //�����Ŏw�肳�ꂽ�I�u�W�F�N�g������
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			  if (*it == go) {
				//���������̂Ń��X�g����폜
				//delete* it;
				//m_goList.erase(it);
				//�C���X�^���X���̂��폜
				//delete go;
				//�폜�ł����̂ŏI���
				//�폜���N�G�X�g�𑗂�B
				go->RequestDelete();
				return;
		      }
	     }
	}
	

	void Draw();
	void Render();

private:
	std::list<IGameObject*> m_goList;
	//GameObjectManager();
	//~GameObjectManager();

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
	
	RenderTarget m_mainRenderTarget;                                   //���C�������_�����O�^�[�Q�b�g�B
	D3D11_VIEWPORT m_frameBufferViewports;                             //�t���[���o�b�t�@�̃r���[�|�[�g�B
	Sprite m_copyMainRtToFrameBufferSprite;                            //���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;   //�t���[���o�@�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;   //�t���[���o�@�t�@�̃f�v�X�X�e���V���r���[�B
	//ShadowMap m_shadowMap;                                             //�V���h�E�}�b�v
};

extern GameObjectManager g_goMgr;