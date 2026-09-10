#include "ModelRenderer.h"
#include "../Resource/Model.h"

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::Render()
{
	if (m_Model)
	{
		m_Model->Draw();
	}
}
