//========================================
//
// プレイヤー[player.cpp]
// Author：森川駿弥
//
//========================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "debugproc.h"
#include "game.h"
#include "particle.h"
#include "useful.h"
#include "gauge.h"
#include "main.h"
#include "model.h"
#include "motion.h"
#include "effect.h"
#include "object2D.h"
#include "object3D.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "lockonMarker.h"

//========================================
// 定数定義
//========================================
namespace
{
	const int LIFE = 10;			// 体力
	const float NOCKBACK = 50.0f;	// ノックバック値
	const float SPEED = 4.0f;		// 速度
	const float INERTIA = 0.3f;		// 慣性
	const float RADIUS = 50.0f;		// 半径
	const float FIELD_LIMIT = 4000.0f;	// フィールドの大きさ
	const float MARKERPOS = 200.0f;		// ロックオンマーカーの位置
}

//========================================
// 静的メンバ変数
//========================================
CPlayer* CPlayer::m_pPlayer = nullptr;

//========================================
//コンストラクタ
//========================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority),
m_apNumModel	(0),			// モデルの総数
m_nLife			(0),			// 体力
m_nOldMotion	(0),			// 前回のモーション
m_WalkCounter	(0),			// 歩行時エフェクト出す用のカウンター
m_State			(STATE_NONE),	// 状態
m_fRadius		(0.0f),			// 半径
m_bJump			(false),		// ジャンプフラグ
m_pEffect		(nullptr),		// エフェクトのポインタ
m_pGauge		(nullptr),		// ゲージのポインタ
m_pMarker		(nullptr)		// ロックオンマーカー表示
{
	memset(&m_apModel[0], 0, sizeof(m_apModel));	//モデル情報
}

//========================================
//デストラクタ
//========================================
CPlayer::~CPlayer()
{
}

//========================================
//プレイヤーの生成
//========================================
CPlayer *CPlayer::Create(std::string pfile)
{
	if (m_pPlayer == nullptr)
	{
		//プレイヤー生成
		m_pPlayer = new CPlayer;

		//初期化
		m_pPlayer->Init(pfile);
	}

	//ポインタを返す
	return m_pPlayer;
}

//========================================
// 初期化
//========================================
HRESULT CPlayer::Init(std::string pfile)
{
	// キャラの初期化
	CCharacter::Init(pfile);

	// プレイヤー状態の初期化
	m_State = STATE_NORMAL;

	// 位置設定
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 500.0f));

	// 向き設定
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 歩行時のカウンター
	m_WalkCounter = 0;

	// 体力
	m_nLife = LIFE;

	// 半径
	m_fRadius;

	// ゲージ生成
	m_pGauge = CGauge::Create(m_nLife);

	// 位置設定
	m_pGauge->SetPos(D3DXVECTOR3(50.0f, 600.0f, 0.0f));

	// サイズ設定
	m_pGauge->SetSize(50.0f, 50.0f);

	return S_OK;
}

//========================================
//終了
//========================================
void CPlayer::Uninit(void)
{
	// 終了
	CCharacter::Uninit();

	m_pPlayer = nullptr;

	m_pGauge->Uninit();
	m_pGauge = nullptr;
}

//========================================
//更新
//========================================
void CPlayer::Update(void)
{
	// キーボードの情報取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// コントローラーの情報取得	
	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();

	//テクスチャの情報取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	// サウンド情報取得
	CSound* pSound = CManager::GetInstance()->GetSound();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// カメラの追従設定
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->Following(pos, rot);

	// プレイヤー行動
	Act(SPEED);

	// ゲージに体力設定
	m_pGauge->SetLife(m_nLife);

	if (m_nLife <= 0)
	{
		// 生成
		CObject2D* pObje2D = CObject2D::Create();

		// 位置設定
		pObje2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

		// サイズ設定
		pObje2D->SetSize(SCREEN_WIDTH, 200.0f);

		// 敗北テクスチャ
		pObje2D->BindTexture(pTexture->Regist("data\\texture\\lose.png"));

		// サウンド停止
		pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);

		// サウンド再生
		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_LOSE);

		// 終了
		Uninit();
	}

	// デバッグ表示
	DebugProc::Print(DebugProc::POINT_LEFT, "\nプレイヤーの位置：%f、%f、%f\n", pos.x, pos.y, pos.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "プレイヤーの移動量：%f、%f、%f\n", move.x, move.y, move.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "プレイヤーの向き：%f、%f、%f\n", rot.x, rot.y, rot.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "プレイヤーの体力：%d\n", m_nLife);
}

//========================================
//描画
//========================================
void CPlayer::Draw(void)
{
	// 描画
	CCharacter::Draw();
}

//========================================
// 行動
//========================================
void CPlayer::Act(float fSpeed)
{
	// キーボードの情報取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// コントローラーの情報取得	
	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 移動量取得
	D3DXVECTOR3 move = GetMove();

	// 位置設定
	SetPos(pos);

	// 移動量設定
	SetMove(move);

	// モーション
	Motion();
}

//========================================
// モーション管理
//========================================
void CPlayer::Motion()
{
	// モーション情報取得
	CMotion* pMotion = GetMotion();

	switch (m_State)
	{
	case STATE_NORMAL: // 通常状態

		// 歩行モーションを設定
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_WALK);

		break;

	default: // その他の場合
		
		// 警告
		assert(false);

		// 待機モーションを設定
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_NEUTRAL);

		break;
	}

	if (pMotion != nullptr)
	{// モーション更新
		pMotion->Update();
	}
}
