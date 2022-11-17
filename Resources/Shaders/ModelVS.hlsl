#include "Model.hlsli"

VSOutput main(float4 pos : POSITION,float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	VSOutput output;	// �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos_ = mul(mat_, pos);	// ���W�ɍs�����Z
	output.normal_ = normal;
	output.uv_ = uv;
	return output;
}