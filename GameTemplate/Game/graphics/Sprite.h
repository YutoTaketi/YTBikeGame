#pragma once

#include "graphics/Shader.h"
class Sprite
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Sprite::Sprite();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	Sprite::~Sprite();
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="textureFilePath">テクスチャのファイルパス。</param>
	void Init(const wchar_t* textureFilePath, float w, float h);
	/// <summary>
	/// テクスチャのSRVを指定して初期化。
	/// </summary>
	/// <param name="srv"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void Init(ID3D11ShaderResourceView* srv, float w, float h);
	/// <summary>
	/// ワールド行列を更新
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale);
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="mView">カメラ行列</param>
	/// /// <param name="mView">プロジェクション行列</param>
	void Draw(CMatrix mView, CMatrix mProj);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// /α値を取得
	/// </summary>
	/// <returns></returns>
	float GetAlpha()
	{
		return m_alpha;
	}
	/// <summary>
	/// αを変位させる
	/// </summary>
	/// <param name="delta">乗算αを変位させる量</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//数値の境界チェック。
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}

	
private:
	/// <summary>
	/// 初期化の共通処理
	/// </summary>
	void InitCommon(float w, float h);
	/// <summary>
	/// 定数バァファの初期化
	/// </summary>
	void InitConstantBuffer();

	/// <summary>
	/// 頂点バッファの初期化。
	/// </summary>
	/// <param name="w">画像の幅</param>
	/// <param name="h">画像の高さ</param>
	void InitVertexBuffer(float w, float h);

	/// <summary>
	/// インデックスバァファの初期化
	/// </summary>
	void InitIndexBuffer();

	/// <summary>
	/// サンプラステートの初期化
	/// </summary>
	void InitSamplerState();
	
	/// <summary>
	/// シェーダーをロード。
	/// </summary>
	void LoadShader();
	/// <summary>
	/// 頂点バッファを作成。
	/// </summary>
	void CreateVertexBuffer(float w, float h);
	/// <summary>
	/// インデックスバッファを作成。
	/// </summary>
	void CreateIndexBuffer();
	/// <summary>
	/// サンプラステートを作成。
	/// </summary>
	void CreateSamplerState();
	/// <summary>
	/// 定数バッファの作成。
	/// </summary>
	void CreateConstantBuffer();
	/// <summary>
	/// テクスチャをロ―ド。
	/// </summary>
	/// <param name="textureFIlePath">ロードするテクスチャのファイルパス。</param>
	void LoadTexture(const wchar_t* textureFIlePath);
	/// <summary>
	/// デプスステンシルステート
	/// </summary>
	void CreateDepthStencilState();
	/// <summary>
	/// ブレンドステート
	/// </summary>
	void InitTranslucentBlendState();
	/// <summary>
	/// ラスタライザステート
	/// </summary>
	void InitRasterizerState();

private:
	struct ConstantBuffer {
		CMatrix WVP;     //ワールドビュープロジェクション行列
		float alpha;     //α値
	};
	Shader                             m_vs;                            //頂点シェーダー
	Shader                             m_ps;                            //ピクセルシェーダー
	ID3D11Buffer*	                   m_vertexBuffer = nullptr;	    //VRAM上の頂点バッファにアクセスするためのインターフェース。
	ID3D11Buffer*	                   m_indexBuffer = nullptr;         //VRAM上のインデックスバッファにアクセスするためのインターフェース。
	ID3D11Buffer*	                   m_cbGPU = nullptr;			    //GPU側の定数バッファにアクセスするためのインターフェース。
	ID3D11ShaderResourceView*          m_texture = nullptr;       	    //テクスチャにアクセスするためのインターフェース。
	ID3D11SamplerState*                m_samplerState = nullptr;	    //サンプラステート。
	CMatrix                            m_world = CMatrix::Identity();	         //ワールド行列。
	CVector2                           m_size = CVector2::Zero();
	ID3D11Buffer*				       m_cb = nullptr;							//定数バッファ。
	float						       m_alpha = 1.0f;	                //スプライトのα値。
	ID3D11DepthStencilState*           m_depthStencilState = nullptr;        //デプスステンシルステート
	ID3D11BlendState*                  m_translucentBlendState = nullptr;    //ブレンドステート
	ID3D11RasterizerState*             m_rasterrizerState = nullptr;     //ラスタライザステート

};

