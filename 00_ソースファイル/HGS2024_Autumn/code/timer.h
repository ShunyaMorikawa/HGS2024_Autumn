#pragma once
//==========================================
//
//  タイマークラス(timer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object.h"

//==========================================
//  前方宣言
//==========================================
class CNumber;

//==========================================
//  クラス定義
//==========================================
class CTimer : public CObject
{
public:

	CTimer();
	~CTimer();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetTimeZero(); // タイムアップしてる判定

	static CTimer* Create();

private:

	// メンバ関数
	void CalcNum(); // 計算

	// メンバ変数
	float m_fTimer; // 現在の時間
	CNumber* m_pNumber[2]; // 数字

};
