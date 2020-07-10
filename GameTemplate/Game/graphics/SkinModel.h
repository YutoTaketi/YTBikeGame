#pragma once

#include "Skeleton.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "Game.h"

class Game;
class ShadowMap;
/*!
*@brief	FBXの上方向。
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
	//コンストラクタ。
	C3DModelEffect()
	{
		//頂点シェーダーをロード。
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	}
	//この関数はDirectX::Model::Draw内部のドローコールの直前に呼ばれる。
	//なので、この関数のなかで、シェーダーの設定や、テクスチャの設定などを行うとよい。
	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override
	{
		//シェーダーを適用する。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
	}
	//この関数はDirectX::Modelの初期化処理から呼ばれる。
	//頂点シェーダーのバイトコードとコードの長さを設定する必要がある。
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
*@brief	スキンモデルクラス。
*/

class SkinModel 
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!解説②　16の倍数に切り上げる処理を関数化。
	*@brief	引数で渡された整数値を16の倍数に切り上げます。
	*@param[in]		n		整数の値。
	*@return		nを16の倍数に切り上げた値。
	*/
	int Raundup16(int n)
	{
		return (((n - 1) / 16) + 1) * 16;
	}

	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}

	/// <summary>
	/// ライトのカラーを設定
	/// </summary>
	void SetLightColor(int lightNo, CVector4 color)
	{
		m_light.directionLight.color[lightNo] = color;
	}

	/// <summary>
	/// 更新。
	/// </summary>
	/// <param name="trans">平行移動</param>
	/// <param name="qRot">回転</param>
	/// <param name="scale">拡大率</param>
	void Update(CVector3 trans);

	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="renderStep">
	///	描画モード。GraphicsEngine.hのEnRenderModeを参照。
	/// </param>
	/// <param name="viewMatrix">ビュー行列</param>
	/// <param name="projMatrix">プロジェクション行列行列</param>
	void Draw(EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix);

	/// <summary>
	/// マテリアルに対してクエリを行う。
	/// </summary>
	/// <param name="func">問い合わせ関数</param>
	void QueryMaterials(std::function<void(C3DModelEffect*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<C3DModelEffect*>(material));
			});
	}

	/// <summary>
	/// シャドウレシーバーのフラグを設定する。
	/// </summary>
	/// <param name="flag">trueを渡すとシャドウレシーバーになる</param>
	/// <remarks>
	/// シャドウレシーバーとは影を落とされるオブジェクトのことです。
	/// シャドウキャスターによって生成された、シャドウマップを利用して
	/// 自身に影を落とします。
	/// オブジェクトがシャドウレシーバーかつシャドウキャスターになっている場合は
	/// セルフシャドウ(自分の影が自分に落ちる)を行うことができます。
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}

	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="renderStep">
	/// 描画ステップ。0なら通常描画、1ならシルエット描画。
	/// </param>
	void Draw(int renderStep);
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
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
	/// 法線マップの設定
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* srv)
	{
		m_normalMapSRV = srv;
	}
	
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	/*!
	 *@brif ディレクションライトの初期化
	 */
	void InitDirectionLight();
	/*!
	*@brif アルベドテクスチャの初期化
	*/
	//void InitAlbedoTexture();
	
	

private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		int isHasNormalMap;  //法線マップを保持している？
	};
	


	struct SDirectionLight {
		CVector4 direction[4];		//ライトの方向。
		CVector4 color[4];			//ライトのカラー。
	};
	/*
	*@brief	ライト構造体。
	*/
	struct SLight {
		SDirectionLight		directionLight;		//ディレクションライト
		CVector3			eyePos;				//視点の座標。
		float				specPow;			//鏡面反射の絞り。
	};

	
	
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	ID3D11Buffer*       m_lightCb = nullptr;            //!<ライト用の定数バッファ
	SLight              m_light;                        //ライト用の構造体

	//SDirectionLight     m_directionLight;
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr; //!<法線マップ
	

	
	/// <summary>
	/// モデルエフェクト用の構造体。
	/// </summary>
	/// <remarks>
	/// これを変更したら、Asserts/shader/model.fxの
	/// VSCbも変更する必要があります。
	/// この構造体は16byteアライメントになっている必要があります。
	/// </remarks>
	struct SModelFxConstantBuffer {
		CMatrix mWorld;			//ワールド行列。
		CMatrix mView;			//ビュー行列。
		CMatrix mProj;			//プロジェクション行列。
		CMatrix mLightView;		//todo ライトビュー行列。
		CMatrix mLightProj;		//todo ライトプロジェクション行列。
		int isShadowReciever;	//todo シャドウレシーバーのフラグ。
	};
	/*
	std::unique_ptr<DirectX::Model>		m_modelDx;				//DirectXTKが提供するモデル。
	
	ID3D11SamplerState* m_samplerState = nullptr;			//!<サンプラーステート。
	CMatrix m_worldMatrix = CMatrix::Identity();			//!<ワールド行列。
	*/
	bool m_isShadowReciever = false;                     //シャドウレシーバーのフラグ
};

