//========================================
//
// 障害物の処理[reverse.cpp]
// Author：相馬靜雅
//
//========================================
#include "reverse.h"
#include "model.h"
#include "calculation.h"

//========================================
//名前空間
//========================================
namespace
{
	const char* MODEL = "data\\MODEL\\obstacle\\wood00.x";	// モデルのパス
	const float COLLISIONRANGE = 200.0f;	// 有効範囲
}
CListManager<CReverse> CReverse::m_List = {};	// リスト

//========================================
//コンストラクタ
//========================================
CReverse::CReverse() : CStageObj()
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

	// モデル生成
	m_pModel = CModel::Create(MODEL);

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
// 更新
//========================================
void CReverse::Update(void)
{
	// 更新
	CStageObj::Update();
}

//========================================
// プレイヤーとの当たり判定
//========================================
bool CReverse::Collision(const D3DXMATRIX& rMtx, const D3DXVECTOR3& rSize)
{
	bool bHit = false;

	// 位置取得
	MyLib::Vector3 pos = GetPos();
	MyLib::Vector3 posTarget = UtilFunc::Transformation::WorldMtxChangeToPosition(rMtx);

	if (UtilFunc::Collision::CircleRange3D(pos, posTarget, COLLISIONRANGE, rSize.x))
	{
		Uninit();
		bHit = true;
	}

	return bHit;

}
