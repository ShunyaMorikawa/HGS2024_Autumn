//========================================
//
//  リザルト [ranking.h]
//  Author：相馬靜雅
//
//========================================
#include "ranking.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "sound.h"
#include "timer.h"

namespace
{
	const int NUM = 3;
}

//=======================================
//コンストラクタ
//=======================================
CRanking::CRanking() : 
m_bNewRecord(false)		// ニューレコード
{
}

//=======================================
//デストラクタ
//=======================================
CRanking::~CRanking()
{
}

//=======================================
//生成
//=======================================
CRanking* CRanking::Create(float nowScore)
{
	//タイトルのポインタ
	CRanking* pTutorial = nullptr;

	//インスタンス生成
	pTutorial = new CRanking;

	if (pTutorial != nullptr)
	{
		// 今回のスコア
		pTutorial->m_fNowScore = nowScore;
		pTutorial->Init();
	}

	//ポインタを返す
	return pTutorial;
}

//=======================================
//初期化
//=======================================
HRESULT CRanking::Init(void)
{
	
	Load();
	Sort();
	Save();


	//成功を返す
	return S_OK;
}

//=======================================
// 終了
//=======================================
void CRanking::Uninit(void)
{
}

//=======================================
// 更新
//=======================================
void CRanking::Update(void)
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
void CRanking::Draw(void)
{
}

//=======================================
// 描画
//=======================================
void CRanking::Sort()
{
	// 降順処理
	for (int nCntData = 0; nCntData < NUM - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < NUM; nCntSort++)
		{
			if (m_fRanking[nCntData] < m_fRanking[nCntSort])
			{// 要素1より要素2が大きかったら

				int nTemp = m_fRanking[nCntData];
				m_fRanking[nCntData] = m_fRanking[nCntSort];
				m_fRanking[nCntSort] = nTemp;
			}
		}
	}

	// ランキング最大値よりも今回のが小さかったら
	if (m_fRanking[NUM - 1] < m_fNowScore)
	{// 入れ替え

		m_fRanking[NUM - 1] = m_fNowScore;	// 最小値と今回のデータ入れ替え
		m_bNewRecord = true;	// フラグON
	}

	// 降順処理
	for (int nCntData = 0; nCntData < NUM - 1; nCntData++)
	{
		for (int nCntSort = nCntData + 1; nCntSort < NUM; nCntSort++)
		{
			if (m_fRanking[nCntData] < m_fRanking[nCntSort])
			{// 要素1より要素2が大きかったら

				int nTemp = m_fRanking[nCntData];
				m_fRanking[nCntData] = m_fRanking[nCntSort];
				m_fRanking[nCntSort] = nTemp;
			}
		}
	}
}

//=======================================
// セーブ
//=======================================
void CRanking::Save()
{
	// ファイルを開く
	std::ofstream File("data\\FILE\\ranking.bin", std::ios::binary);
	if (!File.is_open()) {
		return;
	}

	// 書き込み
	File.write(reinterpret_cast<char*>(m_fRanking), sizeof(m_fRanking));

	// ファイルを閉じる
	File.close();
}

//=======================================
// ロード
//=======================================
void CRanking::Load()
{
	// ファイルを開く
	std::ifstream File("data\\FILE\\ranking.bin", std::ios::binary);
	if (!File.is_open()) {
		
		m_fRanking[0] = 20.0f;	// ランキング
		m_fRanking[1] = 15.0f;	// ランキング
		m_fRanking[2] = 10.0f;	// ランキング

		return;
	}

	// 書き込み
	File.read(reinterpret_cast<char*>(m_fRanking), sizeof(m_fRanking));

	// ファイルを閉じる
	File.close();
}

