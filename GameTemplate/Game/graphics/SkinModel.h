#pragma once

#include "Skeleton.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "Game.h"

class Game;
class ShadowMap;
/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};

class C3DModelEffect : public DirectX::IEffect {
private:
	Shader m_vsShader;
	Shader m_psShader;
	ID3D11ShaderResourceView* m_albedoTextureSRV = nullptr;
	bool m_renderMode = 0;


public:
	//�R���X�g���N�^�B
	C3DModelEffect()
	{
		//���_�V�F�[�_�[�����[�h�B
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	}
	//���̊֐���DirectX::Model::Draw�����̃h���[�R�[���̒��O�ɌĂ΂��B
	//�Ȃ̂ŁA���̊֐��̂Ȃ��ŁA�V�F�[�_�[�̐ݒ��A�e�N�X�`���̐ݒ�Ȃǂ��s���Ƃ悢�B
	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override
	{
		//�V�F�[�_�[��K�p����B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
	}
	//���̊֐���DirectX::Model�̏�������������Ă΂��B
	//���_�V�F�[�_�[�̃o�C�g�R�[�h�ƃR�[�h�̒�����ݒ肷��K�v������B
	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}

	void SetAlbedoTexture(ID3D11ShaderResourceView* texSRV)
	{
		m_albedoTextureSRV = texSRV;
	}

	void SetRenderMode(int renderMode)
	{
		m_renderMode = renderMode;
	}
};



/*!
*@brief	�X�L�����f���N���X�B
*/

class SkinModel 
{
public:
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	
	/*!����A�@16�̔{���ɐ؂�グ�鏈�����֐����B
	*@brief	�����œn���ꂽ�����l��16�̔{���ɐ؂�グ�܂��B
	*@param[in]		n		�����̒l�B
	*@return		n��16�̔{���ɐ؂�グ���l�B
	*/
	int Raundup16(int n)
	{
		return (((n - 1) / 16) + 1) * 16;
	}

	
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	�{�[���������B
	*@param[in]		boneName	�{�[���̖��O�B
	*@return	���������{�[���B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}

	/// <summary>
	/// ���C�g�̃J���[��ݒ�
	/// </summary>
	void SetLightColor(int lightNo, CVector4 color)
	{
		m_light.directionLight.color[lightNo] = color;
	}

	/// <summary>
	/// �X�V�B
	/// </summary>
	/// <param name="trans">���s�ړ�</param>
	/// <param name="qRot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void Update(CVector3 trans);

	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="renderStep">
	///	�`�惂�[�h�BGraphicsEngine.h��EnRenderMode���Q�ƁB
	/// </param>
	/// <param name="viewMatrix">�r���[�s��</param>
	/// <param name="projMatrix">�v���W�F�N�V�����s��s��</param>
	void Draw(EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix);

	/// <summary>
	/// �}�e���A���ɑ΂��ăN�G�����s���B
	/// </summary>
	/// <param name="func">�₢���킹�֐�</param>
	void QueryMaterials(std::function<void(C3DModelEffect*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<C3DModelEffect*>(material));
			});
	}

	/// <summary>
	/// �V���h�E���V�[�o�[�̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag">true��n���ƃV���h�E���V�[�o�[�ɂȂ�</param>
	/// <remarks>
	/// �V���h�E���V�[�o�[�Ƃ͉e�𗎂Ƃ����I�u�W�F�N�g�̂��Ƃł��B
	/// �V���h�E�L���X�^�[�ɂ���Đ������ꂽ�A�V���h�E�}�b�v�𗘗p����
	/// ���g�ɉe�𗎂Ƃ��܂��B
	/// �I�u�W�F�N�g���V���h�E���V�[�o�[���V���h�E�L���X�^�[�ɂȂ��Ă���ꍇ��
	/// �Z���t�V���h�E(�����̉e�������ɗ�����)���s�����Ƃ��ł��܂��B
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}

	/*!
	*@brief	���f����`��B
	*@param[in]	viewMatrix		�J�����s��B
	*  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="renderStep">
	/// �`��X�e�b�v�B0�Ȃ�ʏ�`��A1�Ȃ�V���G�b�g�`��B
	/// </param>
	void Draw(int renderStep);
	/*!
	*@brief	�X�P���g���̎擾�B
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	���b�V������������B
	*@param[in] onFindMesh		���b�V�������������Ƃ��̃R�[���o�b�N�֐�
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/// <summary>
	/// �@���}�b�v�̐ݒ�
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* srv)
	{
		m_normalMapSRV = srv;
	}
	
	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};
private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);
	/*!
	 *@brif �f�B���N�V�������C�g�̏�����
	 */
	void InitDirectionLight();
	/*!
	*@brif �A���x�h�e�N�X�`���̏�����
	*/
	//void InitAlbedoTexture();
	
	

private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		int isHasNormalMap;  //�@���}�b�v��ێ����Ă���H
	};
	


	struct SDirectionLight {
		CVector4 direction[4];		//���C�g�̕����B
		CVector4 color[4];			//���C�g�̃J���[�B
	};
	/*
	*@brief	���C�g�\���́B
	*/
	struct SLight {
		SDirectionLight		directionLight;		//�f�B���N�V�������C�g
		CVector3			eyePos;				//���_�̍��W�B
		float				specPow;			//���ʔ��˂̍i��B
	};

	
	
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	ID3D11Buffer*       m_lightCb = nullptr;            //!<���C�g�p�̒萔�o�b�t�@
	SLight              m_light;                        //���C�g�p�̍\����

	//SDirectionLight     m_directionLight;
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr; //!<�@���}�b�v
	

	
	/// <summary>
	/// ���f���G�t�F�N�g�p�̍\���́B
	/// </summary>
	/// <remarks>
	/// �����ύX������AAsserts/shader/model.fx��
	/// VSCb���ύX����K�v������܂��B
	/// ���̍\���̂�16byte�A���C�����g�ɂȂ��Ă���K�v������܂��B
	/// </remarks>
	struct SModelFxConstantBuffer {
		CMatrix mWorld;			//���[���h�s��B
		CMatrix mView;			//�r���[�s��B
		CMatrix mProj;			//�v���W�F�N�V�����s��B
		CMatrix mLightView;		//todo ���C�g�r���[�s��B
		CMatrix mLightProj;		//todo ���C�g�v���W�F�N�V�����s��B
		int isShadowReciever;	//todo �V���h�E���V�[�o�[�̃t���O�B
	};
	/*
	std::unique_ptr<DirectX::Model>		m_modelDx;				//DirectXTK���񋟂��郂�f���B
	
	ID3D11SamplerState* m_samplerState = nullptr;			//!<�T���v���[�X�e�[�g�B
	CMatrix m_worldMatrix = CMatrix::Identity();			//!<���[���h�s��B
	*/
	bool m_isShadowReciever = false;                     //�V���h�E���V�[�o�[�̃t���O
};

