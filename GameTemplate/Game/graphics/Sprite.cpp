#include "stdafx.h"
#include "Sprite.h"


//頂点構造体。
/*struct Vertex {
	CVector4 pos[4];   //座標
	CVector2 uv[2];    //UV座標
};*/
struct Vertex {
	float pos[4];   //座標
	float uv[2];    //UV座標
};
/// <summary>
/// 2D描画で使用する定数バァファ構造体
/// </summary>
struct SSpriteCB {
	CMatrix mWVP;     //ワールド×ビュー×プロジェクション行列。
	float   alpha;    //α値
};

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	if (m_vertexBuffer != nullptr) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != nullptr) {
		m_indexBuffer->Release();
	}
	if (m_cbGPU != nullptr) {
		m_cbGPU->Release();
	}
	if (m_texture != nullptr) {
		m_texture->Release();
	}
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
	if (m_depthStencilState != nullptr) {
		m_depthStencilState->Release();
	}
	if (m_translucentBlendState != nullptr)
	{
		m_translucentBlendState->Release();
	}
	if (m_rasterrizerState != nullptr)
	{
		m_rasterrizerState->Release();
	}
}

void Sprite::InitVertexBuffer(float w, float h)
{
	//上で定義した頂点を使用して頂点バッファを作成する。
	//頂点バッファを作成するためにはD3D11_BUFFER_DESCとD3D11_SUBRESOURCE_DATAを設定する必要がある。
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	Vertex vertex[4] = {
		//頂点１
		{
			//座標　position[4]
			-halfW, -halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 1.0f
		},
		//頂点２
		{
			//座標　position[4]
			halfW, -halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 1.0f
		},
		//頂点３
		{
			//座標　position[4]
			-halfW,  halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 0.0f
		},
		//頂点４
		{
			//座標　position[4]
			halfW,  halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 0.0f
		},
	};
	//上で定義した頂点を使用して頂点バッファを作成する。
	//頂点バッファを作成するためにはD3D11_BUFFER_DESCとD3D11_SUBRESOURCE_DATAを設定する必要がある。
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//構造体を0で初期化する。
	bd.Usage = D3D11_USAGE_DEFAULT;				//バッファーで想定されている読み込みおよび書き込みの方法。
												//取りあえずはD3D11_USAGE_DEFAULTでよい。
	bd.ByteWidth = sizeof(vertex);				//頂点バッファのサイズ。頂点のサイズ×頂点数となる。
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//これから作成するバッファが頂点バッファであることを指定する。

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	//頂点バッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
}

void Sprite::InitIndexBuffer()
{
	//これがインデックス。頂点番号。
	int index[6] = {
		0,1,2,		//三角形一つ目
		2,1,3		//三角形二つ目
	};
	//上で定義したインデックスを使用してインデックスバッファを作成する。
	//インデックスバッファの作成も頂点バッファと同様に、
	//D3D11_BUFFER_DESCとD3D11_SUBRESOURCE_DATAを設定する必要がある。
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//構造体を0で初期化する。
	bd.Usage = D3D11_USAGE_DEFAULT;				//バッファーで想定されている読み込みおよび書き込みの方法。
												//取りあえずはD3D11_USAGE_DEFAULTでよい。
	bd.ByteWidth = sizeof(index);				//インデックスバッファのサイズ。
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;		//これから作成するバッファがインデックスバッファであることを指定する。

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index;

	//インデックスバッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(
		&bd, &InitData, &m_indexBuffer
	);
}

void Sprite::InitConstantBuffer()
{
	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);
}

void Sprite::InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void Sprite::InitCommon(float w, float h)
{
	m_size.x = w;
	m_size.y = h;
	//頂点バッファの初期化。
	InitVertexBuffer(w, h);
	//インデックスバッファの初期化。
	InitIndexBuffer();
	//サンプラステートの初期化。
	InitSamplerState();
	//シェーダーのロード。
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);

	//定数バッファを初期化。
	InitConstantBuffer();

}
void Sprite::Init(const wchar_t* textureFilePath, float w, float h)
{
	//シェーダーをロード。
	LoadShader();
	//頂点バッファを作成。
	CreateVertexBuffer(w, h);
	//インデックスバッファを作成。
	CreateIndexBuffer();
	//定数バッファを作成。
	CreateConstantBuffer();
	//サンプラステートを作成。
	CreateSamplerState();
	//デプスステンシルステートを作成。
	CreateDepthStencilState();
	//半透明合成のブレンドステートを初期化。
	InitTranslucentBlendState();
	//ラスタライザステートを初期化
	InitRasterizerState();
	//テクスチャをロード。
	LoadTexture(textureFilePath);
}

void Sprite::Init(ID3D11ShaderResourceView* srv, float w, float h)
{
	//共通の初期化処理を呼び出す。
	InitCommon(w, h);
	m_texture = srv;
	m_texture->AddRef();	//参照カウンタを増やす。
}


void Sprite::LoadShader()
{
	//シェーダーをロードする。
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
}

void Sprite::CreateConstantBuffer()
{
	int bufferSize = sizeof(SSpriteCB);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	desc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//定数バッファは16バイトアライメントになっている必要がある。
															//アライメントって→バッファのサイズが16の倍数ということです。
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
															//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	desc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
															//CPUアクセスが不要な場合は0。
															//作成。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBuffer(&desc, NULL, &m_cbGPU);
}

void Sprite::CreateVertexBuffer(float w, float h)
{
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;

	//頂点バッファの元データ。
	//引数で指定された縦、横のサイズの板ポリ。
	Vertex vertices[] = {
		{
			//CVector4(-halfW, -halfH, 0.0f, 1.0f),
			//CVector2(0.0f, 1.0f),
			-halfW, -halfH, 0.0f, 1.0f,
			0.0f, 1.0f,
		},
		{
			//CVector4(halfW, -halfH, 0.0f, 1.0f),
			//CVector2(1.0f, 1.0f),
			halfW, -halfH, 0.0f, 1.0f,
			1.0f, 1.0f,
		},
		{
			//CVector4(-halfW, halfH, 0.0f, 1.0f),
			//CVector2(0.0f, 0.0f)
			-halfW, halfH, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			//CVector4(halfW, halfH, 0.0f, 1.0f),
			//CVector2(1.0f, 0.0f)
			halfW, halfH, 0.0f, 1.0f,
			1.0f, 0.0f
		}
	};

	//頂点バッファを作成するための情報を設定する。
	D3D11_BUFFER_DESC desc = { 0 };					//構造体のメンバを0で初期化する。
	desc.Usage = D3D11_USAGE_DEFAULT;				//気にしなくてよい。
	desc.StructureByteStride = sizeof(Vertex);		//構造体バッファの１要素のサイズ。(頂点一個分のサイズです。)
	desc.ByteWidth = sizeof(Vertex) * 4;			//頂点バッファのサイズ。
													//四角形のポリゴンを描画するので、４頂点必要。
													//なので、一つの頂点のサイズ×４のサイズが必要となる。
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//作成するバッファが頂点バッファであることを指定する。
	desc.CPUAccessFlags = 0;						//CPUから頂点バッファにアクセスするかのフラグ。
													//編集したりはしないので、０にしておく。

													//続いて、元データの情報を作る。
													//元データがないならこれはいらない。
													//今回は必要。
	D3D11_SUBRESOURCE_DATA initData = { 0 };		//構造体のメンバを0で初期化する。
	initData.pSysMem = vertices;					//元データのアドレスを代入。

													//ここまで設定してきた情報を使って、VRAM上に頂点バッファを作成する。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBuffer(&desc, &initData, &m_vertexBuffer);
}

void Sprite::CreateIndexBuffer()
{
	//インデックスバッファの元データ。
	short indices[] = { 0,1,2,3 };

	//インデックスバッファを作るための情報を設定する。
	D3D11_BUFFER_DESC desc = { 0 };					//構造体のメンバを0で初期化する。
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.StructureByteStride = 2;					//インデックス一個分のサイズ。shortなので2バイト。
	desc.ByteWidth = sizeof(indices);				//インデックスバッファのサイズ。
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//作成するバッファがインデックスバッファであることを指定する。
	desc.CPUAccessFlags = 0;						//CPUから頂点バッファにアクセスするかのフラグ。
													//編集したりはしないので、０にしておく。

	D3D11_SUBRESOURCE_DATA initData = { 0 };			//構造体のメンバを0で初期化する。
	initData.pSysMem = indices;						//元データのアドレスを代入する。

													//ここまで設定してきた情報を使って、VRAM上にインデックスバッファを作成する。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBuffer(&desc, &initData, &m_indexBuffer);
}

void Sprite::CreateSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	//Clamp+バイリニアフィルタをかけるサンプラステートを作成する。
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void Sprite::LoadTexture(const wchar_t* textureFIlePath)
{
	//D3Dデバイスを取得。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();

	DirectX::CreateDDSTextureFromFileEx(
		d3dDevice,
		textureFIlePath,
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		false,
		nullptr,
		&m_texture);
}

void Sprite::UpdateWorldMatrix(CVector3 pos, CQuaternion rot, CVector3 scale)
{
	//ワールド行列を計算する
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mScale, mRot);
	m_world.Mul(m_world, mTrans);
}

void Sprite::Draw(CMatrix mView, CMatrix mProj)
{
	//デバイスコンテキストを引っ張ってくる。
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//定数バッファを更新。
	//SSpriteCB cb;
	ConstantBuffer cb;
	//ワールド×ビュー×プロジェクション行列を計算。
	cb.WVP.Mul(m_world, mView);
	cb.WVP.Mul(cb.WVP, mProj);
	cb.alpha = m_alpha;
	//定数バッファの内容をメインメモリからVRAMにコピー。
	deviceContext->UpdateSubresource(m_cbGPU, 0, nullptr, &cb, 0, 0);
	//定数バッファをレジスタb0にバインドする。
	deviceContext->VSSetConstantBuffers(0, 1, &m_cbGPU);
	deviceContext->PSSetConstantBuffers(0, 1, &m_cbGPU);
	//テクスチャをレジスタt0にバインドする。
	deviceContext->PSSetShaderResources(0, 1, &m_texture);
	//サンプラステートをレジスタs0にバインドする。
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	


	

	//頂点バッファを設定。
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	//インデックスバッファを設定。
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	//頂点レイアウトを設定。
	deviceContext->IASetInputLayout(m_vs.GetInputLayout());
	//頂点シェーダーを設定。
	deviceContext->VSSetShader((ID3D11VertexShader *)m_vs.GetBody(), nullptr, 0);
	//ピクセルシェーダを設定。
	deviceContext->PSSetShader((ID3D11PixelShader *)m_ps.GetBody(), nullptr, 0);
	//プリミティブのトポロジーを設定。
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//デプスステンシルステートを切り替える。
	deviceContext->OMSetDepthStencilState(m_depthStencilState, 0);
	//半透明合成のブレンドステートを設定する。
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(m_translucentBlendState, blendFactor, 0xffffffff);
	//ラスタライザステートを設定
	deviceContext->RSSetState(m_rasterrizerState);

	//ここまで設定した内容でドロー
	deviceContext->DrawIndexed(4, 0, 0);
}

void Sprite::Draw()
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	unsigned int vertexSize = sizeof(Vertex);   //頂点のサイズ。
	unsigned int offset = 0;
	d3dDeviceContext->IASetVertexBuffers(	//頂点バッファを設定。
		0,					//StartSlot番号。今は0でいい。
		1,					//バッファの数。今は1でいい。
		&m_vertexBuffer,	//頂点バッファ。
		&vertexSize,		//頂点のサイズ。
		&offset				//気にしなくてよい。
	);
	d3dDeviceContext->IASetIndexBuffer(	//インデックスバッファを設定。
		m_indexBuffer,			//インデックスバッファ。
		DXGI_FORMAT_R32_UINT,	//インデックスのフォーマット。
								//今回は32bitなので、DXGI_FORMAT_R32_UINTでいい。
		0						//オフセット0でいい。
	);
	//シェーダーを設定
	d3dDeviceContext->VSSetShader(
		(ID3D11VertexShader*)m_vs.GetBody(),
		nullptr,
		0
	);
	d3dDeviceContext->PSSetShader(
		(ID3D11PixelShader*)m_ps.GetBody(),
		nullptr,
		0
	);
	

	d3dDeviceContext->IASetInputLayout(m_vs.GetInputLayout());
	//テクスチャを設定
	d3dDeviceContext->PSSetShaderResources(0, 1, &m_texture);
	//サンプラステートを設定
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ワールドビュープロジェクション行列
	ConstantBuffer cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, g_camera2D.GetViewMatrix());
	cb.WVP.Mul(cb.WVP, g_camera2D.GetProjectionMatrix());
	cb.alpha = m_alpha;

	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &cb, 0, 0);
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);

	//デプスステンシルステートを切り替える。
	d3dDeviceContext->OMSetDepthStencilState(m_depthStencilState, 0);
	//半透明合成のブレンドステートを設定する。
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	d3dDeviceContext->OMSetBlendState(m_translucentBlendState, blendFactor, 0xffffffff);

	//プリミティブのトポロジーは
	//トライアングルストリップを設定する。
	d3dDeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d3dDeviceContext->DrawIndexed(  //描画命令
	   6,        //インデックス数
	   0,        //開始インデックス番号
	   0         //開始頂点番号
	);
}

void Sprite::CreateDepthStencilState()
{
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = false;                            //Zテストが有効
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   //ZバァファにZ値を書き込む。
	desc.DepthFunc = D3D11_COMPARISON_LESS;             //Z値が小さければフレームバァファに書き込む。
	//デプスステンシルステートを作成。
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState);

}

void Sprite::InitTranslucentBlendState()
{
	//作成するブレンドステートの情報を設定する。
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	//αブレンディングを有効にする。
	blendDesc.RenderTarget[0].BlendEnable = true;
	//ソースカラーのブレンディング方法を指定。
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//ディスティネーションカラーのブレンディング方法を指定
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//最終的にレンダリングターゲットに書き込まれるカラーの計算方法を指定
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//この設定で、ブレンドステートを作成すると
	//半透明合成を行えるブレンドステートが作成できる。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);
}

void Sprite::InitRasterizerState()
{
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成するラスタライザステートを設定
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;
	pd3d->CreateRasterizerState(&desc, &m_rasterrizerState);
}