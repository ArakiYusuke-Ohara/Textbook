#pragma once

// オレンジが入った箱オブジェクト
class OrangeBox 
{
public:
	void Add(int num);		// オレンジを追加する
	void Delete(int num);	// オレンジを削除する
	void Empty();			// 箱の中を空にする

	// 箱の中のオレンジの総数を取得する関数
	// このように1行にまとめて書くこともできる
	int GetTotal() { return m_Total; }			

private:
	int m_Total;	// 箱の中のオレンジの総数
};


