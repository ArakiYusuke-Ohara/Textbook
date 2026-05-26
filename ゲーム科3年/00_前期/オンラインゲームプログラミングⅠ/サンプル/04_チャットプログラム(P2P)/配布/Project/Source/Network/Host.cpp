#include "Host.h"
#include "../Input/InputString.h"

Host::Host()
{
	m_ClientIP = {};
}

Host::~Host()
{
}

void Host::StartNetwork()
{
	// マッチング開始


	// マッチング待ち状態へ

}

void Host::UpdateWaiting()
{

}

void Host::DrawWaiting()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "マッチング中...");
}
