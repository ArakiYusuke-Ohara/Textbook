#pragma once

// NetworkCommonParam.hはクライアント/サーバー共通のパラメータ
// 必ず双方で同じ状態にする必要がある

// ポート番号は49152～65535が好ましい
#define PORT_NUMBER 50000

// 通信できるユーザー名のMAXサイズ（全角7文字まで）
constexpr int NETWORK_USER_NAME_MAX = 14;
// 文字列の長さは文字数＋終端文字
constexpr int NETWORK_USER_NAME_BUFFER_MAX = NETWORK_USER_NAME_MAX + 1;

// 通信できる文字列のMAXサイズ（全角45文字まで）
constexpr int NETWORK_MESSAGE_MAX = 90;
// 文字列の長さは文字数＋終端文字
constexpr int NETWORK_MESSAGE_BUFFER_MAX = NETWORK_MESSAGE_MAX + 1;

// クライアントが送信するデータ
struct ClientChatData
{
	// ユーザー名
	char userName[NETWORK_USER_NAME_BUFFER_MAX];
	
	// 文字列（全角30文字まで）
	char message[NETWORK_MESSAGE_BUFFER_MAX];
};
