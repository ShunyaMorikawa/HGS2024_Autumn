//========================================
//
//  リザルト [result.h]
//  Author：相馬靜雅
//
//========================================
#include "result.h"
#include "resultscore.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "sound.h"
#include "timer.h"
#include "ranking.h"

//=======================================
//コンストラクタ
//=======================================
CResult::CResult()
{
}

//=======================================
//デストラクタ
//=======================================
CResult::~CResult()
{
}

//=======================================
//生成
//=======================================
CResult* CResult::Create(void)
{
	//タイトルのポインタ
	CResult* pTutorial = nullptr;

	//インスタンス生成
	pTutorial = new CResult;

	//ポインタを返す
	return pTutorial;
}

//=======================================
//初期化
//=======================================
HRESULT CResult::Init(void)
{
	// テクスチャのポインタ
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	// インスタンス生成
	m_pObj2D = CObject2D::Create();

	// 位置設定
	m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// サイズ設定
	m_pObj2D->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// テクスチャ設定
	m_pObj2D->BindTexture(pTexture->Regist("data\\texture\\result.png"));

	// 今回のスコア
	m_pScore = CResultScore::Create(m_pObj2D->GetPos() + MyLib::Vector3(0.0f, -50.0f, 0.0f), CTimer::GetTime());


	// ランキング
	CRanking::Create(CTimer::GetTime());


	//成功を返す
	return S_OK;
}

//=======================================
// 終了
//=======================================
void CResult::Uninit(void)
{
}

//=======================================
// 更新
//=======================================
void CResult::Update(void)
{
	//CInputKeyboard情報取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//CInputPad情報取得
	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) ||
		pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		// 画面遷移(フェード)
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
	}
}

//=======================================
// 描画
//=======================================
void CResult::Draw(void)
{
}
