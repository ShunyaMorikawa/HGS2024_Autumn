//========================================
//
// 障害物(木)の処理[obstacle.cpp]
// Author：小原立暉
//
//========================================
#include "obstacleTree.h"

//========================================
//名前空間
//========================================
namespace
{

}

//========================================
//コンストラクタ
//========================================
CObstacleTree::CObstacleTree() : CObstacle()
{//値をクリア
}

//========================================
//デストラクタ
//========================================
CObstacleTree::~CObstacleTree()
{
}

//========================================
// 初期化
//========================================
HRESULT CObstacleTree::Init(const EType type)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CObstacleTree::Uninit(void)
{
	// 終了
	CObstacle::Uninit();
}

//========================================
// 更新
//========================================
void CObstacleTree::Update(void)
{
	// 更新
	CObstacle::Update();
}

//========================================
// 描画
//========================================
void CObstacleTree::Draw(void)
{
	// 描画
	CObstacle::Draw();
}

//========================================
// プレイヤーとの当たり判定
//========================================
bool CObstacleTree::Collision(D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	return false;
}
