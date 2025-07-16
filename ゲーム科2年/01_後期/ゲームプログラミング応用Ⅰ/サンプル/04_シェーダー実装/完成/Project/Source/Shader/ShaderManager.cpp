#include "ShaderManager.h"
#include "DxLib.h"

ShaderManager::~ShaderManager()
{
	Fin();
}

/// <summary>
/// 全てのシェーダーをロードする
/// </summary>
void ShaderManager::Load()
{
	// 頂点シェーダーのロード
	m_VSHandles[NORMALMESH_NOLIGHT] = LoadVertexShader("Data/Shader/NormalMesh_NoLight_VS.vso");

	// ピクセルシェーダーのロード
	m_PSHandles[NORMALMESH_NOLIGHT] = LoadPixelShader("Data/Shader/NormalMesh_NoLight_PS.pso");
}

/// <summary>
/// 頂点シェーダーとピクセルシェーダーをまとめて設定する
/// </summary>
/// <param name="id">シェーダーID</param>
void ShaderManager::SetShader(int id)
{
	SetVertexShader(id);
	SetPixelShader(id);
}

/// <summary>
/// 頂点シェーダーを設定する
/// </summary>
/// <param name="id">シェーダーID</param>
void ShaderManager::SetVertexShader(int id)
{
	SetUseVertexShader(m_VSHandles[id]);
}

/// <summary>
/// ピクセルシェーダーを設定する
/// </summary>
/// <param name="id">シェーダーID</param>
void ShaderManager::SetPixelShader(int id)
{
	SetUsePixelShader(m_PSHandles[id]);
}

/// <summary>
/// 終了処理
/// </summary>
void ShaderManager::Fin()
{
	for (int i = 0; i < SHADER_ID_MAX; i++)
	{
		DeleteShader(m_VSHandles[i]);
		DeleteShader(m_PSHandles[i]);
	}

	// デフォルトの状態に戻す
	MV1SetUseOrigShader(FALSE);
	SetUseVertexShader(-1);
	SetUsePixelShader(-1);
}

