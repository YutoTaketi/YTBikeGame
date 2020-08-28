/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//法線
Texture2D<float4> g_normalMap : register(t2);		

//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
//シャドウマップ
Texture2D<float4> g_shadowMap : register(t3);		

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//ライトビュー行列を追加
	float4x4 mLightView;  //ライトビュー行列
	float4x4 mLightProj;  //ライトプロジェクション行列
	int isShadowReciever; //シャドーレシーバーフラグ
	int isHasNormalMap;	//法線マップある？
};
/*struct SDirectionLight {
	float3 dligDirection[4];
	float4 dligColor[4];
};*/
/*!
 *@brief    ライト用の定数バッファ
 */
//static const int NUM_DIRECTION_LIG = 4;
cbuffer LightCb : register(b1) {
	//SDirectionLight   directionLight;
	float3 dligDirection[4];
	float4 dligColor[4];
	float3 eyePos;
	float  specPow;
};

/*!
 * @brief	シャドウマップ用の定数バァファ。
 */
cbuffer ShadowMapCb : register(b2) {
	float4x4 lightViewProjMatrix;  //ライトビュー
}

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 WorldPos		: TEXCOORD1;	//ワールド座標。
	float4 posInLVP     : TEXCOORD2;    //ライトビュープロジェクション空間での座標
};

/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体
/// </summary>
struct PSInput_ShadowMap {
	float4 Position     : SV_POSITION; //座標
	float3 Normal       : NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 WorldPos		: TEXCOORD1;	//ワールド座標。
};

/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//ローカル座標系からワールド座標系に変換する。
	float4 pos = mul(mWorld, In.Position);
	psInput.WorldPos = pos;

	if (isShadowReciever == 1)
	{
		//ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul( mLightView, float4(psInput.WorldPos, 1.0f) );
		psInput.posInLVP = mul( mLightProj, psInput.posInLVP);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;

	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);
	}
	psInput.WorldPos = pos.xyz;
	if (isShadowReciever == 1)
	{
		//ライトビュープロジェクション空間に変換
		psInput.posInLVP = mul(mLightView, float4(psInput.WorldPos, 1.0f));
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	//psInput.Normal = In.Normal;
	//psInput.Tangent = In.Tangent;


	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.WorldPos = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);

	//法線
	float3 normal = 0;
	if (isHasNormalMap == 1) //1なら設定されている。
	{
		float3 biNormal = cross(In.Normal, In.Tangent);
		biNormal = normalize(biNormal);
		//ローカル法線をもってくる
		normal = g_normalMap.Sample(Sampler, In.TexCoord);   //法線　-1～0～1が0～0.5～1で記録されてる。
		normal = normalize((normal * 2.0f) - 1.0f);                       //-1～0～1の状態にする。
		//ワールド法線に変換
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal* normal.z;
	}
	else {
		//ない
		normal = In.Normal;
	}


	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0.0f;
	for (int i = 0; i < 4; i++) {
		lig += max(0.0f, dot(normal * -1.0f, dligDirection[i])) * dligColor[i].xyz;
	}
	{
		for (int i = 0; i < 4; i++) {
			//鏡面反射の計算
			float3 R = reflect(dligDirection[i], normal);
		
			//②視点からライトを当てる物体に伸びるベクトルEを求める。
			float3 E = normalize(In.WorldPos - eyePos);

			//①と②で求まったベクトルの内積を計算する。
			//スペキュラ反射の強さを求める。
			float specPower = max(0, dot(R, -E));


			lig += dligColor[i].xyz * pow(specPower, specPow) * dligColor[i].w;
			//lig += dligColor[i].xyz;
			//lig += 0.0f;
		}
	}
	
	//シャドウレシーバー
	if (isShadowReciever == 1)
	{
		
		//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;

		//シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f && shadowMapUV.x > 0.0f && shadowMapUV.y < 1.0f && shadowMapUV.y > 0.0f)
		{
			///LVP空間での深度値を計算。
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);
			if (zInLVP > zInShadowMap + 0.001f) {
			    //影を落ちているので、光を弱くする
				lig *= 0.2f;
			}
		}
		
	}

	//ライトの光とアルベドカラーを乗算して、
	//最終カラーとする
	
	//環境光をあてる
	lig += float3(0.4f, 0.4f, 0.4f);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
/// <summary>
/// スキンモデルなし用シャドウマップ生成用の頂点シェーダー
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

/// <summary>
/// スキンモデルあり用シャドウマップ生成用の頂点シェーダー
/// </summary>
PSInput_ShadowMap VSMain_SkinShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);
	}

	psInput.Normal = normalize(mul(skinning, In.Normal));
	psInput.Tangent = normalize(mul(skinning, In.Tangent));

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

//--------------------------------------------------------------------------------------
// シャドウマップ用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。+
	return In.Position.z / In.Position.w;
}