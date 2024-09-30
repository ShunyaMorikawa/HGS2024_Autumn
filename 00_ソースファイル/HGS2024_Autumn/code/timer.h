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

	// 静的メンバ関数
	static CTimer* Create(); // 生成処理
	static float GetTime() { return m_fTimer; } // 時間の取得

private:

	// メンバ関数
	void CalcNum(); // 計算

	// メンバ変数
	static float m_fTimer; // 現在の時間
	CNumber* m_pNumber[2]; // 数字

};
