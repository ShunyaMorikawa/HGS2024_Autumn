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

#include "stageobj.h"
#include "reverse.h"

//========================================
// 定数定義
//========================================
namespace
{
	const int LIFE = 10;			// 体力
	const float SPEED = 500.0f;		// 速度
	const float JUMP_MOVE = 1500.0f;	// ジャンプ量
	const float JUMP_SAB = JUMP_MOVE * 0.04f;	// ジャンプ減衰
	const float ROLL_TIME = 1.0f;	// 転がり継続時間
	const float RADIUS = 50.0f;		// 半径
	const float HEIGHT = 100.0f;	// 身長
	const float HEIGHT_SCALE = 0.5f;	// 転がり中の身長倍率
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
m_fHeight		(0.0f),			// 身長
m_fRollTime		(0.0f),			// 転がり時間
m_bJump			(false),		// ジャンプフラグ
m_bRoll			(false),		// 転がりフラグ
m_pEffect		(nullptr),		// エフェクトのポインタ
m_pGauge		(nullptr),		// ゲージのポインタ
m_type			(TYPE_NONE),	// タイプ
m_typeDefault	(TYPE_NONE)		// デフォルトタイプ
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
	m_typeDefault = m_type = TYPE_TURTLE;

	// 位置設定
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 向き設定
	SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// 移動量設定
	SetMove(D3DXVECTOR3(SPEED, 0.0f, 0.0));

	// 歩行時のカウンター
	m_WalkCounter = 0;

	// 情報を初期化
	m_nLife = LIFE;
	m_fRadius = RADIUS;
	m_fHeight = HEIGHT;

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
	// 自身の情報を取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRot();

	// デルタタイムの取得
	const float fDeltaTime = CManager::GetInstance()->GetDeltaTime();

	// カメラの追従設定
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->Following(pos, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// 移動処理
	Move(pos, move, fDeltaTime);

	// 着地判定
	Land(pos, move);

	// ステージオブジェとの範囲チェック
	CheckStageObjRange();

	// 反転オブジェの当たり判定
	CollisionReverseObj();

	// ゲージに体力設定
	m_pGauge->SetLife(m_nLife);

	// モーション
	Motion();

	// 情報を設定
	SetPos(pos);
	SetMove(move);
	SetRot(rot);

	// デバッグ表示
	DebugProc::Print(DebugProc::POINT_LEFT, "プレイヤーの位置：%f、%f、%f\n", pos.x, pos.y, pos.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "プレイヤーの移動量：%f、%f、%f\n", move.x, move.y, move.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "プレイヤーの向き：%f、%f、%f\n", rot.x, rot.y, rot.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "プレイヤーのサイズ：%f、%f、%f\n", m_fRadius, m_fHeight, m_fRadius);
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
// モーション管理
//========================================
void CPlayer::Motion()
{
	// モーション情報取得
	CMotion* pMotion = GetMotion();

	// モーションがnullの場合関数を抜ける
	if (pMotion == nullptr)
	{
		assert(false);
		return;
	}

	// モーションを設定
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

	// モーションを更新
	pMotion->Update();
}

//==========================================
//  移動処理
//==========================================
void CPlayer::Move(D3DXVECTOR3& pos, D3DXVECTOR3& move, const float fDeltaTime)
{
	// インプット情報の取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputPad* pPad = CManager::GetInstance()->GetInputPad();

#ifdef _DEBUG
	// 2キーで初期位置に戻る
	if (pKeyboard->GetTrigger(DIK_2))
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		return;
	}

	// デバッグ中は右シフトを押さないと動かない
	if (!pKeyboard->GetPress(DIK_RSHIFT))
	{
		return;
	}

#endif

	// 状態の切り替え
	SwitchType(pPad, pKeyboard);

	// 状態ごとの処理
	switch (m_type)
	{
	case TYPE_RABBIT:
		// ジャンプ処理
		Jump(move, pPad, pKeyboard);
		DebugProc::Print(DebugProc::POINT_CENTER, "今、兎です！！！\n");
		break;

	case TYPE_TURTLE:
		// 転がり処理
		Roll(move, pPad, pKeyboard, fDeltaTime);
		DebugProc::Print(DebugProc::POINT_CENTER, "今、亀です！！！\n");
		break;

	default:
		assert(false);
		break;
	}

	// TODO : タイマーが出来次第加速処理を追加

	// 座標に移動量を加算
	pos += move * fDeltaTime;
}

//==========================================
//  ジャンプ処理
//==========================================
void CPlayer::Jump(D3DXVECTOR3& move, CInputPad* pPad, CInputKeyboard* pKeyboard)
{
	// ジャンプ中の場合関数を抜ける
	if (m_bJump) { return; }

	// ボタンが押されたらジャンプする
	if (pPad->GetTrigger(CInputPad::BUTTON_A, 0) || pKeyboard->GetTrigger(DIK_SPACE))
	{
		// ジャンプフラグを設定
		m_bJump = true;

		// 移動量を加算
		move.y += JUMP_MOVE;
	}
}

//==========================================
//  転がり処理
//==========================================
void CPlayer::Roll(D3DXVECTOR3& move, CInputPad* pPad, CInputKeyboard* pKeyboard, const float fDeltaTime)
{
	// 転がり中の場合時間を加算
	if (m_bRoll)
	{
		// 加算
		m_fRollTime += fDeltaTime;

		// 一定時間経過していない場合関数を抜ける
		if (m_fRollTime < ROLL_TIME) { return; }

		// 転がり状態を解除する
		m_fRollTime = 0.0f;
		m_bRoll = false;
		m_fHeight = HEIGHT;

		return;
	}

	// ボタンが押されたら転がり状態になる
	if (pPad->GetTrigger(CInputPad::BUTTON_A, 0) || pKeyboard->GetTrigger(DIK_SPACE))
	{
		// フラグをtrue
		m_bRoll = true;

		// 身長を減らす
		m_fHeight *= HEIGHT_SCALE;
	}
}

//==========================================
//  状態の切り替え
//==========================================
void CPlayer::SwitchType(CInputPad* pPad, CInputKeyboard* pKeyboard)
{
	// 転がり状態もしくはジャンプ中の場合関数を抜ける
	if (m_bJump || m_bRoll) { return; }

	// タイプをデフォルトで上書きする
	m_type = m_typeDefault;

	// ボタンが押されていない場合関数を抜ける
	if(!pPad->GetPress(CInputPad::BUTTON_LB, 0) && !pKeyboard->GetPress(DIK_LSHIFT)) { return; }

	// デフォルトタイプを見てタイプを変更する
	m_type = m_typeDefault == TYPE_TURTLE ? TYPE_RABBIT : TYPE_TURTLE;
}

//==========================================
//  着地判定
//==========================================
void CPlayer::Land(D3DXVECTOR3& pos, D3DXVECTOR3& move)
{
	// y座標が0.0を下回った場合補正する
	if (pos.y < 0.0f)
	{
		// ジャンプフラグをfalse
		m_bJump = false;

		// 座標を補正
		pos.y = 0.0f;

		// 移動量を削除
		move.y = 0.0f;
	}

	// ジャンプ中なら移動量を減少させる
	if (m_bJump)
	{
		move.y -= JUMP_SAB;
	}
}

//==========================================
// ステージオブジェの範囲チェック
//==========================================
void CPlayer::CheckStageObjRange()
{
	// ステージオブジェのリスト取得
	CListManager<CStageObj> list = CStageObj::GetList();

	// 終端を保存
	std::list<CStageObj*>::iterator itr = list.GetEnd();
	CStageObj* pObj = nullptr;

	// 位置取得
	MyLib::Vector3 pos = GetPos();

	// 終端までループ
	while (list.ListLoop(itr))
	{
		CStageObj* pObj = *itr;
		pObj->CollisionRange(pos);
	}
}

//==========================================
// 反転オブジェの当たり判定
//==========================================
void CPlayer::CollisionReverseObj()
{
	// 反転オブジェのリスト取得
	CListManager<CReverse> list = CReverse::GetList();

	// 終端を保存
	std::list<CReverse*>::iterator itr = list.GetEnd();
	CReverse* pObj = nullptr;

	// 位置取得
	MyLib::Vector3 pos = GetPos();

	// 終端までループ
	while (list.ListLoop(itr))
	{
		CReverse* pObj = *itr;
		if (pObj->Collision(pos, MyLib::Vector3(RADIUS, HEIGHT, RADIUS)))
		{
			// 反転
			m_typeDefault = (m_typeDefault == TYPE_RABBIT) ? PLAYERTYPE::TYPE_TURTLE : PLAYERTYPE::TYPE_RABBIT;
			return;
		}
	}
}
