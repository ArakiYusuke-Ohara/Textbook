#include "DxLib.h"
#include "ModelRenderer.h"
#include "../Resource/Model.h"
#include "../Component/Transform.h"
#include "../Object/Object.h"

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::SetModel(Model* model)
{
	m_Model = model;
	m_Handle = MV1DuplicateModel(model->GetHandle());
}

void ModelRenderer::Update()
{
	Transform t = GetOwner()->GetTransform();

	MV1SetPosition(m_Handle, t.GetPos());
	MV1SetRotationXYZ(m_Handle, t.GetRotate());
	MV1SetScale(m_Handle, t.GetScale());
}

void ModelRenderer::Render()
{
	if (m_Model)
	{
		m_Model->Draw();
	}
}
