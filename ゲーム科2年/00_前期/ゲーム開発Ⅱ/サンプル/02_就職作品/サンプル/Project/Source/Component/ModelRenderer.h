#pragma once
#include "Renderer.h"

class Model;

class ModelRenderer : public Renderer
{
public:
	ModelRenderer() = default;
	virtual ~ModelRenderer();

	void SetModel(Model* model);

	void Update() override;
	void Render() override;

private:
	Model* m_Model;
	int m_Handle;
};
