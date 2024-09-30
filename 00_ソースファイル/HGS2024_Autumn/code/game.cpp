//========================================
//
//ゲーム内処理[game.cpp]
//Author：森川駿弥
//
//========================================
#include "game.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "texture.h"
#include "fade.h"

#include "timer.h"
#include "field.h"
#include "stageobj.h"
#include "stagemanager.h"

//========================================
//静的メンバ変数
//========================================
CGame *CGame::m_pGame = nullptr;			// ゲームのポインタ

//========================================
// 定数定義
//========================================
namespace
{
const int TRANSITIONTIME = 180;		// 遷移するまでの時間

const char* PLAYER_PASS = "data\\FILE\\turtle.txt"; // プレイヤーのパス
}

//========================================
//コンストラクタ
//========================================
CGame::CGame() : 
	m_bPause(false),
	m_pFade(nullptr),
	m_pTimer(nullptr),
	m_pStageManager(nullptr)
{
	m_pGame = nullptr;
}

//========================================
//デストラクタ
//========================================
CGame::~CGame()
{
}

//========================================
//生成
//========================================
CGame *CGame::Create(void)
{
	if (m_pGame == nullptr)
	{
		//インスタンス生成
		m_pGame = new CGame;
	}

	//ポインタを返す
	return m_pGame;
}

//========================================
//初期化
//========================================
HRESULT CGame::Init(void)
{
	//テクスチャのポインタ
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	CField::Create();

	// プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(PLAYER_PASS);
	}

	// タイマー
	if (m_pTimer == nullptr)
	{
		m_pTimer = CTimer::Create();
	}

	// ステージマネージャーの生成
	if (m_pStageManager == nullptr)
	{
		m_pStageManager = CStageManager::Create();
	}

	return S_OK;
}

//========================================
//終了
//========================================
void CGame::Uninit(void)
{
	if(m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		m_pTimer = nullptr;
	}

	if (m_pStageManager != nullptr)
	{
		m_pStageManager->Uninit();
		m_pStageManager = nullptr;
	}

	m_pGame = nullptr;
}

//========================================
//更新
//========================================
void CGame::Update(void)
{
	// タイマーが0を下回った場合終了
	if (m_pTimer->GetTimeZero() || CPlayer::GetInstance()->GetLife() <= 0.0f)
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);
	}

#ifdef _DEBUG

	// CInputKeyboard型のポインタ
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_F2) == true)
	{// ゲーム画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);
	}
	
	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		CStageObj::Create(CStageObj::Type::TYPE_REVERSE, MyLib::Vector3(500.0f, 500.0f, 0.0f));
	}
#endif
}

//========================================
//描画
//========================================
void CGame::Draw(void)
{
}
