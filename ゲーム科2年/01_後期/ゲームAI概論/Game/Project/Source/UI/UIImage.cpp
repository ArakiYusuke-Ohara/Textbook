#include "DxLib.h"
#include "UIImage.h"

UIImage::UIImage()
{
	m_Handle = 0;
}

UIImage::~UIImage()
{
	Fin();
}

void UIImage::Load(const char* path)
{
	m_Handle = LoadGraph(path);
}

void UIImage::Draw()
{
	DrawGraph((int)m_Pos.x, (int)m_Pos.y, m_Handle, TRUE);
}

void UIImage::Fin()
{
	DeleteGraph(m_Handle);
}

