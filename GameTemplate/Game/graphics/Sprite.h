#pragma once

#include "graphics/Shader.h"
class Sprite
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Sprite::Sprite();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	Sprite::~Sprite();
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="textureFilePath">�e�N�X�`���̃t�@�C���p�X�B</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	/// <summary>
	/// �e�N�X�`����SRV���w�肵�ď������B
	/// </summary>
	/// <param name="srv"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void Init(ID3D11ShaderResourceView* srv, float w, float h);
	/// <summary>
	/// ���[���h�s����X�V
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale);
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="mView">�J�����s��</param>
	/// /// <param name="mView">�v���W�F�N�V�����s��</param>
	void Draw(CMatrix mView, CMatrix mProj);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// ����ψʂ�����
	/// </summary>
	/// <param name="delta">��Z����ψʂ������</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//���l�̋��E�`�F�b�N�B
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}
private:
	/// <summary>
	/// �������̋��ʏ���
	/// </summary>
	void InitCommon(float w, float h);
	/// <summary>
	/// �萔�o�@�t�@�̏�����
	/// </summary>
	void InitConstantBuffer();

	/// <summary>
	/// ���_�o�b�t�@�̏������B
	/// </summary>
	/// <param name="w">�摜�̕�</param>
	/// <param name="h">�摜�̍���</param>
	void InitVertexBuffer(float w, float h);

	/// <summary>
	/// �C���f�b�N�X�o�@�t�@�̏�����
	/// </summary>
	void InitIndexBuffer();

	/// <summary>
	/// �T���v���X�e�[�g�̏�����
	/// </summary>
	void InitSamplerState();
	
	/// <summary>
	/// �V�F�[�_�[�����[�h�B
	/// </summary>
	void LoadShader();
	/// <summary>
	/// ���_�o�b�t�@���쐬�B
	/// </summary>
	void CreateVertexBuffer(float w, float h);
	/// <summary>
	/// �C���f�b�N�X�o�b�t�@���쐬�B
	/// </summary>
	void CreateIndexBuffer();
	/// <summary>
	/// �T���v���X�e�[�g���쐬�B
	/// </summary>
	void CreateSamplerState();
	/// <summary>
	/// �萔�o�b�t�@�̍쐬�B
	/// </summary>
	void CreateConstantBuffer();
	/// <summary>
	/// �e�N�X�`�������\�h�B
	/// </summary>
	/// <param name="textureFIlePath">���[�h����e�N�X�`���̃t�@�C���p�X�B</param>
	void LoadTexture(const wchar_t* textureFIlePath);
private:
	struct ConstantBuffer {
		CMatrix WVP;     //���[���h�r���[�v���W�F�N�V�����s��
		float alpha;     //���l
	};
	Shader                             m_vs;                            //���_�V�F�[�_�[
	Shader                             m_ps;                            //�s�N�Z���V�F�[�_�[
	ID3D11Buffer*	                   m_vertexBuffer = nullptr;	    //VRAM��̒��_�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11Buffer*	                   m_indexBuffer = nullptr;         //VRAM��̃C���f�b�N�X�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11Buffer*	                   m_cbGPU = nullptr;			    //GPU���̒萔�o�b�t�@�ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11ShaderResourceView*          m_texture = nullptr;       	    //�e�N�X�`���ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X�B
	ID3D11SamplerState*                m_samplerState = nullptr;	    //�T���v���X�e�[�g�B
	CMatrix                            m_world = CMatrix::Identity();	         //���[���h�s��B
	CVector2                           m_size = CVector2::Zero();
	ID3D11Buffer*				       m_cb = nullptr;							//�萔�o�b�t�@�B
	float						       m_alpha = 1.0f;							//�X�v���C�g�̃��l�B
};

