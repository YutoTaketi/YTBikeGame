/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�@��
Texture2D<float4> g_normalMap : register(t2);		

//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
//�V���h�E�}�b�v
Texture2D<float4> g_shadowMap : register(t3);		

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//���C�g�r���[�s���ǉ�
	float4x4 mLightView;  //���C�g�r���[�s��
	float4x4 mLightProj;  //���C�g�v���W�F�N�V�����s��
	int isShadowReciever; //�V���h�[���V�[�o�[�t���O
	int isHasNormalMap;	//�@���}�b�v����H
};
/*struct SDirectionLight {
	float3 dligDirection[4];
	float4 dligColor[4];
};*/
/*!
 *@brief    ���C�g�p�̒萔�o�b�t�@
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
 * @brief	�V���h�E�}�b�v�p�̒萔�o�@�t�@�B
 */
cbuffer ShadowMapCb : register(b2) {
	float4x4 lightViewProjMatrix;  //���C�g�r���[
}

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 WorldPos		: TEXCOORD1;	//���[���h���W�B
	float4 posInLVP     : TEXCOORD2;    //���C�g�r���[�v���W�F�N�V������Ԃł̍��W
};

/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��͍\����
/// </summary>
struct PSInput_ShadowMap {
	float4 Position     : SV_POSITION; //���W
	float3 Normal       : NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 WorldPos		: TEXCOORD1;	//���[���h���W�B
};

/*!
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//���[�J�����W�n���烏�[���h���W�n�ɕϊ�����B
	float4 pos = mul(mWorld, In.Position);
	psInput.WorldPos = pos;

	if (isShadowReciever == 1)
	{
		//���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
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
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
		pos = mul(skinning, In.Position);
	}
	psInput.WorldPos = pos.xyz;
	if (isShadowReciever == 1)
	{
		//���C�g�r���[�v���W�F�N�V������Ԃɕϊ�
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
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);

	//�@��
	float3 normal = 0;
	if (isHasNormalMap == 1) //1�Ȃ�ݒ肳��Ă���B
	{
		float3 biNormal = cross(In.Normal, In.Tangent);
		biNormal = normalize(biNormal);
		//���[�J���@���������Ă���
		normal = g_normalMap.Sample(Sampler, In.TexCoord);   //�@���@-1�`0�`1��0�`0.5�`1�ŋL�^����Ă�B
		normal = normalize((normal * 2.0f) - 1.0f);                       //-1�`0�`1�̏�Ԃɂ���B
		//���[���h�@���ɕϊ�
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal* normal.z;
	}
	else {
		//�Ȃ�
		normal = In.Normal;
	}


	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = 0.0f;
	for (int i = 0; i < 4; i++) {
		lig += max(0.0f, dot(normal * -1.0f, dligDirection[i])) * dligColor[i].xyz;
	}
	{
		for (int i = 0; i < 4; i++) {
			//���ʔ��˂̌v�Z
			float3 R = reflect(dligDirection[i], normal);
		
			//�A���_���烉�C�g�𓖂Ă镨�̂ɐL�т�x�N�g��E�����߂�B
			float3 E = normalize(In.WorldPos - eyePos);

			//�@�ƇA�ŋ��܂����x�N�g���̓��ς��v�Z����B
			//�X�y�L�������˂̋��������߂�B
			float specPower = max(0, dot(R, -E));


			lig += dligColor[i].xyz * pow(specPower, specPow) * dligColor[i].w;
			//lig += dligColor[i].xyz;
			//lig += 0.0f;
		}
	}
	
	//�V���h�E���V�[�o�[
	if (isShadowReciever == 1)
	{
		
		//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;

		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
		if (shadowMapUV.x < 1.0f && shadowMapUV.x > 0.0f && shadowMapUV.y < 1.0f && shadowMapUV.y > 0.0f)
		{
			///LVP��Ԃł̐[�x�l���v�Z�B
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);
			if (zInLVP > zInShadowMap + 0.001f) {
			    //�e�𗎂��Ă���̂ŁA�����キ����
				lig *= 0.2f;
			}
		}
		
	}

	//���C�g�̌��ƃA���x�h�J���[����Z���āA
	//�ŏI�J���[�Ƃ���
	
	//���������Ă�
	lig += float3(0.4f, 0.4f, 0.4f);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
}
/// <summary>
/// �X�L�����f���Ȃ��p�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[
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
/// �X�L�����f������p�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[
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
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
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
// �V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

//--------------------------------------------------------------------------------------
// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B+
	return In.Position.z / In.Position.w;
}