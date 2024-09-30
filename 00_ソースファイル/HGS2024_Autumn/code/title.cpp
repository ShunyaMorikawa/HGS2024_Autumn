//========================================
//
//タイトル[title.cpp]
//Author：森川駿弥
//
//========================================
#include "title.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "field.h"
#include "mapobject.h"
#include "wall.h"
#include "player.h"

//========================================
// 定数定義
//========================================
namespace
{
const char* TITLE_TEX = "data\\TEXTURE\\title.png";	// タイトルテクスチャのパス
}

//=======================================
//コンストラクタ
//=======================================
CTitle::CTitle(int nPriority)
{
	m_pObj2D = nullptr;
}

//=======================================
//デストラクタ
//=======================================
CTitle::~CTitle()
{
}

//=======================================
//生成
//=======================================
CTitle* CTitle::Create(void)
{
	//タイトルのポインタ
	CTitle* pTitle = nullptr;

	//インスタンス生成
	pTitle = new CTitle;

	//初期化
	pTitle->Init();

	//ポインタを返す
	return pTitle;
}

//=======================================
//初期化
//=======================================
HRESULT CTitle::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	// インスタンス生成
	m_pObj2D = CObject2D::Create();

	// 位置設定
	m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// サイズ設定
	m_pObj2D->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// テクスチャ設定
	m_pObj2D->BindTexture(pTexture->Regist("data\\texture\\title.png"));

	// サウンド情報取得
	CSound* pSound = CManager::GetInstance()->GetSound();

	// サウンド停止
	pSound->Stop();

	// サウンド再生
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	//成功を返す
	return S_OK;
}

//=======================================
//終了
//=======================================
void CTitle::Uninit(void)
{
}

//=======================================
//更新
//=======================================
void CTitle::Update(void)
{
	// キーボードとパッドのポインタ
	CInputKeyboard *pInputKeyboard = pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();	
	CInputPad *pInputPad = pInputPad = CManager::GetInstance()->GetInputPad();
	
	// カメラの情報取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || 
		pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) == true ||
		pInputPad->GetTrigger(CInputPad::BUTTON_START, 0) == true)
	{
		// 画面遷移(フェード)
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TUTORIAL);
	}
}

//=======================================
//描画
//=======================================
void CTitle::Draw(void)
{
}
