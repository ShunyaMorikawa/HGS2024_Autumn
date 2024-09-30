//==========================================
//
//  タイマークラス(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "timer.h"
#include "number.h"
#include "manager.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float INIT_TIME = 30.0f; // 初期値
	const D3DXVECTOR3 NUMBER_SIZE = D3DXVECTOR3(50.0f, 50.0f, 0.0f); // サイズ
	const D3DXVECTOR3 NUMBER_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 50.0f, 0.0f); // 座標
}

//==========================================
//  コンストラクタ
//==========================================
CTimer::CTimer() :
	m_fTimer(0.0f)
{
}

//==========================================
//  デストラクタ
//==========================================
CTimer::~CTimer()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CTimer::Init()
{
	// 初期値を設定
	m_fTimer = INIT_TIME;

	// 数字を生成
	for (int i = 0; i < 2; ++i)
	{
		m_pNumber[i] = CNumber::Create();
		m_pNumber[i]->SetPos(NUMBER_POS);
		m_pNumber[i]->SetPosVertex();
	}

	// 計算
	CalcNum();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTimer::Uninit()
{
	// 数字の終了
	for (int i = 0; i < 2; ++i)
	{
		if (m_pNumber[i] != nullptr)
		{
			m_pNumber[i]->Uninit();
			m_pNumber[i] = nullptr;
		}
	}
}

//==========================================
//  更新処理
//==========================================
void CTimer::Update()
{
	// タイマーを減少
	m_fTimer -= CManager::GetInstance()->GetDeltaTime();

	// 計算
	CalcNum();
}

//==========================================
//  描画処理
//==========================================
void CTimer::Draw()
{
}

//==========================================
//  生成処理
//==========================================
CTimer* CTimer::Create()
{
	// ポインタを確保
	CTimer* pTime = new CTimer;

	// nullチェック
	if (pTime == nullptr) { assert(false); return nullptr; }

	// 初期化処理
	pTime->Init();

	return pTime;
}

//==========================================
//  計算
//==========================================
void CTimer::CalcNum()
{
	// タイマーを整数値に変換
	int nTime = (float)m_fTimer;

	// 数字を更新
	for (int i = 0; i < 2; ++i)
	{
		if (m_pNumber[i] != nullptr)
		{
			// 桁に合わせた数値を算出
			int nNum = nTime / 10;

			// 数値を設定
			m_pNumber[i]->SetNumber(nNum);

			// 数値を変更
			nTime %= 10;
			nTime *= 10;
		}
	}
}
