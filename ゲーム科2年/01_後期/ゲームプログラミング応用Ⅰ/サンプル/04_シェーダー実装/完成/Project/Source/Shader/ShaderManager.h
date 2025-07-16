#pragma once
#include "../Singleton/Singleton.h"

enum ShaderID
{
	NORMALMESH_NOLIGHT,
	SHADER_ID_MAX
};

class ShaderManager : public Singleton<ShaderManager>
{
public:
	~ShaderManager();

public:
	void Load();
	void SetShader(int id);
	void SetVertexShader(int id);
	void SetPixelShader(int id);
	void Fin();

private:
	// ロードした頂点シェーダー配列
	int m_VSHandles[SHADER_ID_MAX] = {};
	// ロードしたピクセルシェーダー配列
	int m_PSHandles[SHADER_ID_MAX] = {};
};

