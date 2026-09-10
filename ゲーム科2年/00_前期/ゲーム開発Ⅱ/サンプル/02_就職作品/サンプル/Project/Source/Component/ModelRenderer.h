#pragma once
#include "Renderer.h"

class Model;

class ModelRenderer : public Renderer
{
public:
	ModelRenderer() = default;
	virtual ~ModelRenderer();

	void SetModel(Model* model) { m_Model = model; }

	void Render() override;

private:
	Model* m_Model;
};
