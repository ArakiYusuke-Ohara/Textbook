#include "Player.h"
#include "../Component/Renderer/Splite.h"
#include "../Component/Controller/Controller2D.h"
#include "../MyMath/MyMath.h"

Player::Player() : GameObject()
, m_IsActive(true)
, m_MoveSpeed(0.0f)
, m_ScaleSpeed(0.0f)
, m_RotSpeed(0.0f)
, m_Splite(nullptr)
, m_Controller(nullptr)
{
}

Player::~Player() = default;

void Player::Init()
{
	m_MoveSpeed = 10.0f;
	m_ScaleSpeed = 0.01f;
	m_RotSpeed = 0.01f;
	m_Splite = AddComponent<Splite>();
	m_Controller = AddComponent<Controller2D>();
}

void Player::Load()
{
	m_Splite->Load("Data/Player/Player.png");
}

void Player::Start()
{
	SetPosition(VGet(100.0f, 100.0f, 0.0f));
}

void Player::Step()
{
	if (!m_IsActive) return;

	VECTOR pos = m_Transform.GetPosition();
	VECTOR scale = m_Transform.GetScale();
	VECTOR rot = m_Transform.GetRotation();

	// à⁄ìÆì¸óÕ
	pos += m_Controller->Move() * m_MoveSpeed;

	// ägèkì¸óÕ
	scale += m_Controller->Scale() * m_ScaleSpeed;

	// âÒì]ì¸óÕ
	rot += m_Controller->Rotate() * m_RotSpeed;

	m_Transform.SetPosition(pos);
	m_Transform.SetScale(scale);
	m_Transform.SetRotation(rot);
}

void Player::Draw()
{
	if (!m_IsActive) return;

	if (m_Splite)
	{
		m_Splite->Draw();
	}
}

/// <summary>
/// éÄñSèàóù
/// </summary>
void Player::Die()
{
	m_IsActive = false;
}

