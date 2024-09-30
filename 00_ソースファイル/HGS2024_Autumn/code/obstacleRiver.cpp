//========================================
//
// 障害物(川)の処理[obstacleRiver.cpp]
// Author：小原立暉
//
//========================================
#include "obstacleRiver.h"

//========================================
//名前空間
//========================================
namespace
{

}

//========================================
//コンストラクタ
//========================================
CObstacleRiver::CObstacleRiver() : CObstacle()
{//値をクリア
}

//========================================
//デストラクタ
//========================================
CObstacleRiver::~CObstacleRiver()
{
}

//========================================
// 初期化
//========================================
HRESULT CObstacleRiver::Init(const EType type)
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
void CObstacleRiver::Uninit(void)
{
	// 終了
	CObstacle::Uninit();
}

//========================================
// 更新
//========================================
void CObstacleRiver::Update(void)
{
	// 更新
	CObstacle::Update();
}

//========================================
// 描画
//========================================
void CObstacleRiver::Draw(void)
{
	// 描画
	CObstacle::Draw();
}

//========================================
// プレイヤーとの当たり判定
//========================================
bool CObstacleRiver::Collision(D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	return false;
}
