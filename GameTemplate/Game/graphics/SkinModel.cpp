#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "Game.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	//ライト用の定数バァファの開放
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}

	if (m_normalMapSRV != nullptr) {
		m_normalMapSRV->Release();
	}
	
}

void SkinModel::Update(CVector3 trans)
{
	m_worldMatrix.MakeTranslation(trans);
}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();

	//ディレクションライトの初期化
	InitDirectionLight();
	//アルベドテクスチャの初期化
	//InitAlbedoTexture();

	//エフェクトファクトリを作成
	//C3DModelEffectFactory effectFactory(g_graphicsEngine->GetD3DDevice());
	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}

//ディレクションライトの初期化
void SkinModel::InitDirectionLight()
{
	m_light.directionLight.direction[0] = { 1.0f, -1.0f,0.0f, 0.0f };
	m_light.directionLight.direction[0].Normalize();
	m_light.directionLight.color[0] = { 0.5f, 0.5f, 0.5f, 1.0f };

	m_light.directionLight.direction[1] = { -1.0f, -1.0f,0.0f, 0.0f };
	m_light.directionLight.direction[1].Normalize();
	m_light.directionLight.color[1] = { 0.2f, 0.2f, 0.2f, 1.0f };

	m_light.directionLight.direction[2] = { 0.0f, -1.0f, 1.0f, 0.0f };
	m_light.directionLight.direction[2].Normalize();
	m_light.directionLight.color[2] = { 0.2f, 0.2f, 0.2f, 1.0f };

	m_light.directionLight.direction[3] = { 1.0f, -1.0f, -1.0f, 0.0f };
	m_light.directionLight.direction[3].Normalize();
	m_light.directionLight.color[3] = { 0.2f, 0.2f, 0.2f, 1.0f };
	m_light.specPow = 5.0f;
}
/*void SkinModel::InitAlbedoTexture()
{
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/modelData/utc_all2.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_albedoTextureSRV);
}*/



void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}

//定数バァファの初期化
void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	//続いて、ライト用の定数バッファを作成。
	//作成するバッファのサイズを変更するだけ。
	bufferDesc.ByteWidth = sizeof(SLight);				//SDirectionLightは16byteの倍数になっているので、切り上げはやらない。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}


void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}


void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);
	
	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}


void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();


	//定数バッファの内容を更新。
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;

	//法線マップを使用するかどうかのフラグを送る。
	if (m_normalMapSRV != nullptr) {
		vsCb.isHasNormalMap = true;
	}
	else {
		vsCb.isHasNormalMap = false;
	}
	static float specPow = 5.0f;
	m_light.specPow = specPow;
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);

	//視点を設定
	m_light.eyePos = g_camera3D.GetPosition();
	//ライト用の定数バァファを更新.
     d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);

	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);

	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();
	//アルベドテクスチャを設定する。
	//d3dDeviceContext->PSSetShaderResources(0, 1, &m_albedoTextureSRV);

	if (m_normalMapSRV != nullptr) {
		//法線マップが設定されていたらレジスタt2に設定する。
		d3dDeviceContext->PSSetShaderResources(2, 1, &m_normalMapSRV);
	}

	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
	
}

//オフスクリーン用描画
void SkinModel::Draw(int renderMode)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	//定数バァファの更新
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = g_camera3D.GetProjectionMatrix();
	vsCb.mView = g_camera3D.GetViewMatrix();
	deviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//ライト用の定数バァファを更新。
	deviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);

	//定数バァファをシェーダースロットに設定
	deviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	deviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	//サンプラステートを設定する。
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//エフェクトにクエリを行う。
	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<C3DModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
	});
	m_modelDx->Draw(
		deviceContext,
		state,
		m_worldMatrix,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

//ポストエフェクト用描画関数
void SkinModel::PostEffectDraw(EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix)
{
	/*auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	
	//auto shadowMap = 
	//定数バァファを更新
	SModelFxConstantBuffer modelFxCb;
	modelFxCb.mWorld = m_worldMatrix;
	modelFxCb.mProj = projMatrix;
	modelFxCb.mView = viewMatrix;
	//todo ライトカメラのビュー、プロジェクション行列を送る。
	modelFxCb.mLightProj = shadowMap->GetLightProjMatrix();
	modelFxCb.mLightView = shadowMap->GetLighViewMatrix();
	if (m_isShadowReciever == true) {
		modelFxCb.isShadowReciever = 1;
	}
	else {
		modelFxCb.isShadowReciever = 0;
	}

	deviceContext->UpdateSubresource(m_cb, 0, nullptr, &modelFxCb, 0, 0);
	//ライト用の定数バァファを更新
	deviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);

	//定数バァファをシェーダースロットに設定
	deviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	deviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	deviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	
	//サンプラーステートを設定する。
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//エフェクトにクエリを行う。
	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<C3DModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
		});
	m_modelDx->Draw(
		deviceContext,
		state,
		m_worldMatrix,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);*/
}