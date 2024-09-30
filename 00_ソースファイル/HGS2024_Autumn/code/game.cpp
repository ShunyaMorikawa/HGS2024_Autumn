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
#include "field.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "wall.h"
#include "mapobject.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"

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

const char* PLAYER_PASS = "data\\FILE\\player.txt";

}

//========================================
//コンストラクタ
//========================================
CGame::CGame() : 
	m_bPause(false),
	m_nTransition(0),
	m_pObjectX(nullptr),
	m_pIdxMesh(nullptr),
	m_pFade(nullptr),
	m_pObj2D(nullptr)
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

	// プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(PLAYER_PASS);
	}

	// インスタンス生成
	m_pObj2D = CObject2D::Create();

	// 位置設定
	m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// サイズ設定
	m_pObj2D->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// テクスチャ設定
	m_pObj2D->BindTexture(pTexture->Regist("data\\texture\\game.png"));

	return S_OK;
}

//========================================
//終了
//========================================
void CGame::Uninit(void)
{
	if(m_pObj2D != nullptr)
	{
		m_pObj2D->Uninit();
		m_pObj2D = nullptr;
	}

	m_pGame = nullptr;
}

//========================================
//更新
//========================================
void CGame::Update(void)
{
	// CInputKeyboard型のポインタ
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// プレイヤーの情報取得
	CPlayer* pPlayer = CPlayer::GetInstance();

	// 敵の情報取得
	CEnemy* pEnemy = CEnemy::GetInstance();

	if (pEnemy == nullptr || pPlayer == nullptr)
	{// 敵かプレイヤーの体力が0以下になったら
		m_nTransition++;

		if (m_nTransition > TRANSITIONTIME ||
			pInputKeyboard->GetTrigger(DIK_RETURN))
		{
			// 画面遷移(フェード)
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);

			m_nTransition = 0;
		}
	}

	// デバッグ表示
	DebugProc::Print(DebugProc::POINT_LEFT, "\nカウンター：%d\n", m_nTransition);

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_F2) == true)
	{// ゲーム画面に遷移
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);
	}
#endif
}

//========================================
//描画
//========================================
void CGame::Draw(void)
{
}
