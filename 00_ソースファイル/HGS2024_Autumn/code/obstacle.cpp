////========================================
////
//// 障害物の処理[obstacle.cpp]
//// Author：森川駿弥
////
////========================================
//#include "obstacle.h"
//
////========================================
////名前空間
////========================================
//namespace
//{
//
//}
//
////========================================
////コンストラクタ
////========================================
//CObstacle::CObstacle() :
//	m_nLife(0),
//	m_fRadius(0.0f),
//	m_nState(STATE_NORMAL),
//	m_bWalk(false),
//	m_bAttack(false),
//	m_pGauge(nullptr)
//{//値をクリア
//}
//
////========================================
////デストラクタ
////========================================
//CObstacle::~CObstacle()
//{
//}
//
////========================================
//// 生成
////========================================
//CObstacle* CObstacle::Create(std::string pfile)
//{
//	if (m_pEnemy == nullptr)
//	{//	インスタンス生成
//		m_pEnemy = new CObstacle;
//
//		m_pEnemy->Init(pfile);
//	}
//
//	return m_pEnemy;
//}
//
////========================================
//// 初期化
////========================================
//HRESULT CObstacle::Init(std::string pfile)
//{
//	//テクスチャのポインタ
//	CTexture* pTexture = CManager::GetInstance()->GetTexture();
//
//	// キャラの初期化
//	CCharacter::Init(pfile);
//
//	// 位置設定
//	SetPos(D3DXVECTOR3(0.0f, 0.0f, -500.0f));
//
//	// 向き設定
//	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//
//	// 体力
//	m_nLife = LIFE;
//
//	// 半径
//	m_fRadius = RADIUS;
//
//	// ゲージ生成
//	m_pGauge = CGauge::Create(m_nLife);
//
//	// 位置設定
//	m_pGauge->SetPos(D3DXVECTOR3(600.0f, 25.0f, 0.0f));
//
//	// サイズ設定
//	m_pGauge->SetSize(50.0f, 50.0f);
//
//	return S_OK;
//}
//
////========================================
//// 終了
////========================================
//void CObstacle::Uninit(void)
//{
//	// 終了
//	CCharacter::Uninit();
//
//	m_pEnemy = nullptr;
//
//	m_pGauge->Uninit();
//	m_pGauge = nullptr;
//}
//
////========================================
//// 更新
////========================================
//void CObstacle::Update(void)
//{
//	// 目的の向き
//	D3DXVECTOR3 DiffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	// 更新
//	CCharacter::Update();
//
//	// 位置取得
//	D3DXVECTOR3 pos = GetPos();
//
//	// 移動量取得
//	D3DXVECTOR3 move = GetMove();
//
//	// 向き取得
//	D3DXVECTOR3 rot = GetRot();
//
//	// 目的の向き取得
//	D3DXVECTOR3 RotDest = GetRotDest();
//
//	// プレイヤー情報の取得
//	CPlayer* pPlayer = CPlayer::GetInstance();
//
//	// キーボードの情報取得
//	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
//
//	if (pPlayer != nullptr)
//	{
//		// 位置取得
//		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
//
//		// プレイヤーとの角度
//		RotDest.y = atan2f(pos.x - posPlayer.x, pos.z - posPlayer.z);
//	}
//
//	// プレイヤー方向に移動
//	move.x += sinf(rot.y + D3DX_PI) * SPEED;
//	move.z += cosf(rot.y + D3DX_PI) * SPEED;
//
//	// 位置を更新
//	pos += move;
//
//	// 移動量を更新(減衰させる)
//	move.x += (0.0f - move.x) * INERTIA;
//	move.z += (0.0f - move.z) * INERTIA;
//
//	//目的の向き
//	DiffRot.y = RotDest.y - rot.y;
//
//	// 向きの正規化
//	USEFUL::NormalizeRotAngle(DiffRot.y);
//
//	//Diffに補正係数をかける
//	rot.y += DiffRot.y * 0.1f;
//
//	// 角度の正規化
//	USEFUL::NormalizeRotAngle(rot.y);
//
//	// 重力
//	move.y -= GRAVITY;
//
//	if (pos.y <= 0.0f)
//	{// 位置と移動量の更新停止
//		pos.y = 0.0f;
//		move.y = 0.0f;
//	}
//
//	// カウント加算
//	m_nCnt++;
//
//	if (m_nCnt >= ATTACKCOUNTER)
//	{// 攻撃するまでの時間
//		m_bAttack = true;
//
//		for (int n = 0; n < MAXDIRECTION; n++)
//		{// 弾を8方向に飛ばす
//			float fAngle = D3DX_PI * 2.0f / MAXDIRECTION;
//
//			// 発射角度をずらす
//			fAngle *= n;
//			D3DXVECTOR3 bulletmove;
//			bulletmove.x = sinf(fAngle) * BULLETMOVE;
//			bulletmove.y = 0.0f;
//			bulletmove.z = cosf(fAngle) * BULLETMOVE;
//
//			// 弾の生成
//			CBullet::Create(pos, bulletmove, BULLETLIFE);
//		}
//
//		// サウンド情報取得
//		CSound* pSound = CManager::GetInstance()->GetSound();
//
//		// サウンド再生
//		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BULLET);
//
//		m_nCnt = 0;
//	}
//
//	// ゲージに体力設定
//	m_pGauge->SetLife(m_nLife);
//
//	// 位置設定
//	SetPos(pos);
//
//	// 移動量設定
//	SetMove(move);
//
//	// 向き設定
//	SetRot(rot);
//
//	// 目的の向き設定
//	SetRotDest(RotDest);
//
//	// モーション管理
//	Motion();
//
//	// 闘技場との当たり判定
//	CollisionCircle();
//
//	switch (m_nState)
//	{
//	case STATE_NORMAL:
//		break;
//	default:
//		break;
//	}
//
//#ifdef _DEBUG
//	if (pInputKeyboard->GetPress(DIK_F4))
//	{// 体力減算
//		Hit(LIFE);
//	}
//#endif
//
//	// デバッグ表示
//	DebugProc::Print(DebugProc::POINT_LEFT, "\n敵の位置：%f、%f、%f\n", pos.x, pos.y, pos.z);
//	DebugProc::Print(DebugProc::POINT_LEFT, "敵の向き：%f、%f、%f\n", rot.x, rot.y, rot.z);
//	DebugProc::Print(DebugProc::POINT_LEFT, "敵の移動量：%f、%f、%f\n", move.x, move.y, move.z);
//	DebugProc::Print(DebugProc::POINT_LEFT, "敵の体力：%d\n", m_nLife);
//	DebugProc::Print(DebugProc::POINT_LEFT, "F4で敵の体力0\n");
//}
//
////========================================
//// 描画
////========================================
//void CObstacle::Draw(void)
//{
//	// 描画
//	CCharacter::Draw();
//}
//
////========================================
//// ヒット処理
////========================================
//void CObstacle::Hit(int nLife)
//{
//	//CInputKeyboard情報取得
//	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
//
//	//CInputPad情報取得
//	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();
//
//	D3DXVECTOR3 pos = GetPos();
//
//	//テクスチャのポインタ
//	CTexture* pTexture = CManager::GetInstance()->GetTexture();
//
//	// 状態取得
//	int nState = GetState();
//
//	// 体力減らす
//	m_nLife -= nLife;
//
//	if (m_pGauge != nullptr)
//	{
//		// ゲージに体力設定
//		m_pGauge->SetLife(m_nLife);
//	}
//
//	if (m_nLife <= 0)
//	{
//		// 死亡状態
//		nState = STATE_DEATH;
//
//		// パーティクル生成
//		Myparticle::Create(Myparticle::TYPE_DEATH, pos);
//
//		// 終了
//		Uninit();
//
//		// 生成
//		CObject2D* pObje2D = CObject2D::Create();
//
//		// 位置設定
//		pObje2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 00.0f));
//
//		// サイズ設定
//		pObje2D->SetSize(SCREEN_WIDTH, 200.0f);
//
//		// 勝利テクスチャ
//		pObje2D->BindTexture(pTexture->Regist("data\\texture\\win.png"));
//
//		// サウンド情報取得
//		CSound* pSound = CManager::GetInstance()->GetSound();
//
//		// サウンド停止
//		pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
//
//		// サウンド再生
//		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_WIN);
//	}
//}
//
////========================================
//// ノックバック
////========================================
//void CObstacle::NockBack()
//{
//	// 敵の情報取得
//	CPlayer* pPlayer = CPlayer::GetInstance();
//
//	if (pPlayer != nullptr)
//	{
//		// 位置取得
//		D3DXVECTOR3 posEnemy = GetPos();
//
//		// プレイヤーの位置と移動量
//		D3DXVECTOR3 posPlayer = pPlayer->GetPos();
//		D3DXVECTOR3 movePlayer = pPlayer->GetMove();
//
//		// 飛ばされる角度
//		float angle = atan2f(posEnemy.x - posEnemy.x, posPlayer.z - posEnemy.z);
//
//		// 位置更新
//		movePlayer.x = sinf(angle) * -NOCKBACK;
//		movePlayer.z = cosf(angle) * -NOCKBACK;
//		movePlayer.y = 25.0f;
//
//		// 移動量設定
//		pPlayer->SetMove(movePlayer);
//	}
//}
//
////========================================
//// モーション管理
////========================================
//void CObstacle::Motion()
//{
//	// モーション情報取得
//	CMotion* pMotion = GetMotion();
//
//	// 位置取得
//	D3DXVECTOR3 pos = GetPos();
//
//	// 移動量取得
//	D3DXVECTOR3 move = GetMove();
//
//	if (m_bWalk)
//	{// 歩きモーション
//		pMotion->Set(CMotion::ENEMY_MOTIONTYPE_WALK);
//	}
//	else if (m_bAttack)
//	{// 切り下ろしモーション
//		pMotion->Set(CMotion::ENEMY_MOTIONTYPE_ATTACK);
//
//		m_bWalk = false;
//
//		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		if (pMotion->IsFinish() && m_bAttack == true)
//		{// モーション終了
//			m_bAttack = false;
//		}
//	}
//	else
//	{
//		pMotion->Set(CMotion::ENEMY_MOTIONTYPE_WALK);
//	}
//
//	if (pMotion != nullptr)
//	{// モーション更新
//		pMotion->Update();
//	}
//
//	SetMove(move);
//}
