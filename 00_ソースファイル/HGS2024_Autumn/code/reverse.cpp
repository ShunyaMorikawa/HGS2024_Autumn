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
