//========================================
//
// 障害物(柔らかい岩)の処理[obstacleSoftRock.cpp]
// Author：小原立暉
//
//========================================
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
CObstacleSoftRock::CObstacleSoftRock() : CObstacle()
{//値をクリア
}

//========================================
//デストラクタ
//========================================
CObstacleSoftRock::~CObstacleSoftRock()
{
}

//========================================
// 初期化
//========================================
HRESULT CObstacleSoftRock::Init(const EType type)
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
void CObstacleSoftRock::Uninit(void)
{
	// 終了
	CObstacle::Uninit();
}

//========================================
// 更新
//========================================
void CObstacleSoftRock::Update(void)
{
	// 更新
	CObstacle::Update();
}

//========================================
// 描画
//========================================
void CObstacleSoftRock::Draw(void)
{
	// 描画
	CObstacle::Draw();
}

//========================================
// プレイヤーとの当たり判定
//========================================
bool CObstacleSoftRock::Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	return false;
}
