#include "UIManager.h"
#include "UIImage.h"

UIManager* UIManager::m_Instance = nullptr;

UIManager::UIManager()
{
	m_UIs = {};
}

UIManager::~UIManager()
{
	Fin();
}

void UIManager::Init()
{
}

void UIManager::Start()
{
	for (UIBase* ui : m_UIs)
	{
		ui->Start();
	}
}

void UIManager::Step()
{
	for (UIBase* ui : m_UIs)
	{
		ui->Step();
	}
}

void UIManager::Update()
{
	for (UIBase* ui : m_UIs)
	{
		ui->Update();
	}
}

void UIManager::Draw()
{
	for (UIBase* ui : m_UIs)
	{
		ui->Draw();
	}
}

void UIManager::Fin()
{
	for (UIBase* ui : m_UIs)
	{
		delete ui;
	}

	m_UIs.clear();
	m_UIs.shrink_to_fit();
}

UIBase* UIManager::CreateUI(int id)
{
	UIBase* ui = nullptr;
	switch (id)
	{
		case UI_ID_IMAGE: ui = new UIImage;  break;
		case UI_ID_GAUGE:	break;
	}

	m_UIs.push_back(ui);

	return ui;
}
