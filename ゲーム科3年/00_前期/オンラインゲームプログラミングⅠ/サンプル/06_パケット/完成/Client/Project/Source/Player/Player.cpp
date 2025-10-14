#include "Player.h"
#include "../Component/Transform.h"
#include "../Component/Splite.h"
#include "../Component/Controller2D.h"
#include "../MyMath/MyMath.h"

Player::Player()
{
	m_MoveSpeed = 0.0f;
	m_ScaleSpeed = 0.0f;
	m_RotSpeed = 0.0f;
	m_Transform = nullptr;
	m_Splite = nullptr;
	m_Controller = nullptr;
}

Player::~Player() = default;

void Player::Init()
{
	m_MoveSpeed = 1.0f;
	m_ScaleSpeed = 0.01f;
	m_RotSpeed = 0.01f;
	m_Transform = MakeUnique<Transform>();
	m_Splite = MakeUnique<Splite>();
	m_Controller = MakeUnique<Controller2D>();

	m_Transform->SetPos(VGet(100.0f, 100.0f, 0.0f));
}

void Player::Load()
{
	m_Splite->Load("Data/Player/Player.png");
}

void Player::Update()
{
	VECTOR pos = m_Transform->GetPos();
	VECTOR scale = m_Transform->GetScale();
	VECTOR rot = m_Transform->GetRot();

	// ˆÚ“®
	pos += m_Controller->Move() * m_MoveSpeed;

	// Šgk
	scale += m_Controller->Scale() * m_ScaleSpeed;

	// ‰ñ“]
	rot += m_Controller->Rotate() * m_RotSpeed;

	m_Transform->SetPos(pos);
	m_Transform->SetScale(scale);
	m_Transform->SetRot(rot);
}

void Player::Draw()
{
	if (m_Splite)
	{
		m_Splite->SetTransform(*m_Transform);
		m_Splite->Draw();
	}
}
