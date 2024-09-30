//========================================
//
// 障害物の処理[reverse.cpp]
// Author：相馬靜雅
//
//========================================
#include "reverse.h"
#include "model.h"
#include "calculation.h"
#include "billboard.h"
#include "manager.h"
#include "texture.h"

//========================================
//名前空間
//========================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\reverse.png";	// モデルのパス
	const float COLLISIONRANGE = 200.0f;	// 有効範囲
}
CListManager<CReverse> CReverse::m_List = {};	// リスト

//========================================
//コンストラクタ
//========================================
CReverse::CReverse() : CStageObj(),
m_pBillboard(nullptr)
{

}

//========================================
//デストラクタ
//========================================
CReverse::~CReverse()
{

}

//========================================
// 初期化
//========================================
HRESULT CReverse::Init(void)
{
	// リストに追加
	m_List.Regist(this);

	// ビルボード生成
	m_pBillboard = CBillboard::Create(GetPos(), 200.0f, 200.0f);

	//テクスチャのポインタ
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	int texIdx = pTexture->Regist(TEXTURE);
	m_pBillboard->BindTexture(texIdx);

	if (FAILED(CStageObj::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CReverse::Uninit(void)
{
	// リストから削除
	m_List.Delete(this);

	// 終了
	CStageObj::Uninit();
}

//========================================
// 削除
//========================================
void CReverse::Kill()
{
	if (m_pBillboard != nullptr)
	{
		m_pBillboard->Uninit();
		m_pBillboard = nullptr;
	}

	// 終了
	CReverse::Uninit();
}

//========================================
// 更新
//========================================
void CReverse::Update(void)
{
	// 更新
	CStageObj::Update();

	if (m_pBillboard != nullptr)
	{
		m_pBillboard->SetPos(GetPos());
		m_pBillboard->Update();
	}
}

//========================================
// 描画
//========================================
void CReverse::Draw(void)
{
	if (m_pBillboard != nullptr)
	{
		m_pBillboard->Draw();
	}

	// 描画
	CStageObj::Draw();
}

//========================================
// プレイヤーとの当たり判定
//========================================
bool CReverse::Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	bool bHit = false;

	// 位置取得
	MyLib::Vector3 pos = GetPos();

	if (UtilFunc::Collision::CircleRange3D(pos, rPos, COLLISIONRANGE, rSize.x))
	{
		Kill();
		bHit = true;
	}

	return bHit;

}
