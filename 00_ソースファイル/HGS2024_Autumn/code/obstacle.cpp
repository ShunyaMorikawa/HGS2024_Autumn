//========================================
//
// 障害物の処理[obstacle.cpp]
// Author：小原立暉
//
//========================================
#include "obstacle.h"
#include "model.h"

#include "obstacleTree.h"
#include "obstacleRiver.h"
#include "obstacleStone.h"
#include "obstacleHole.h"
#include "obstacleSoftRock.h"

//========================================
//名前空間
//========================================
namespace
{

}

//========================================
//コンストラクタ
//========================================
CObstacle::CObstacle() : CStageObj(),
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
	if (FAILED(CStageObj::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CObstacle::Uninit(void)
{
	// 終了
	CStageObj::Uninit();
}

//========================================
// 更新
//========================================
void CObstacle::Update(void)
{
	// 更新
	CStageObj::Update();
}

//========================================
// プレイヤーとの当たり判定
//========================================
bool CObstacle::Collision(D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	return true;
}

//========================================
// 描画
//========================================
void CObstacle::Draw(void)
{
	// 描画
	CStageObj::Draw();
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

	case CObstacle::TYPE_SOFTROCK:

		pObstacle = new CObstacleSoftRock;

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
