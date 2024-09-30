//========================================
//
// 障害物の処理[obstacle.cpp]
// Author：小原立暉
//
//========================================
#include "obstacle.h"

#include "obstacleTree.h"
#include "obstacleRiver.h"
#include "obstacleStone.h"
#include "obstacleHole.h"

//========================================
//名前空間
//========================================
namespace
{

}

//========================================
//コンストラクタ
//========================================
CObstacle::CObstacle() : CModel(),
m_type(TYPE_TREE)
{//値をクリア
}

//========================================
//デストラクタ
//========================================
CObstacle::~CObstacle()
{
}

//========================================
// 初期化
//========================================
HRESULT CObstacle::Init(const EType type)
{
	//if (FAILED(CModel::Init()))
	//{ // 初期化に失敗した場合

	//	// 失敗を返す
	//	return E_FAIL;
	//}

	// 値の設定
	SetPos(D3DXVECTOR3(0.0f, 0.0f, -500.0f));	// 位置
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// 向き

	return S_OK;
}

//========================================
// 終了
//========================================
void CObstacle::Uninit(void)
{
	// 終了
	CModel::Uninit();
}

//========================================
// 更新
//========================================
void CObstacle::Update(void)
{
	// 更新
	CModel::Update();
}

//========================================
// 描画
//========================================
void CObstacle::Draw(void)
{
	// 描画
	CModel::Draw();
}

//========================================
// 生成処理
//========================================
CObstacle* CObstacle::Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot)
{
	CObstacle* pObstacle = nullptr;

	switch (type)
	{
	case CObstacle::TYPE_TREE:

		pObstacle = new CObstacleTree;

		break;

	case CObstacle::TYPE_RIVER:

		pObstacle = new CObstacleRiver;

		break;

	case CObstacle::TYPE_STONE:

		pObstacle = new CObstacleStone;

		break;

	case CObstacle::TYPE_HOLE:

		pObstacle = new CObstacleHole;

		break;

	default:
		assert(false);
		break;
	}

	// 初期化処理に失敗したら、停止
	if (FAILED(pObstacle->Init(type))) { assert(false); return nullptr; }

	// ポインタを返す
	return pObstacle;
}
