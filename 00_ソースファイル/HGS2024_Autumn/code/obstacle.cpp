//========================================
//
// 障害物の処理[obstacle.cpp]
// Author：森川駿弥
//
//========================================
#include "obstacle.h"

//========================================
//名前空間
//========================================
namespace
{

}

//========================================
//コンストラクタ
//========================================
CObstacle::CObstacle() : CModel()
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
// プレイヤーとの当たり判定
//========================================
bool CObstacle::Collision(D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	return false;
}

//========================================
// 生成処理
//========================================
CObstacle* CObstacle::Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot)
{
	//CObstacle* pObstacle = new ;

	//if (m_pEnemy == nullptr)
	//{//	インスタンス生成
	//	m_pEnemy = new CEnemy;

	//	m_pEnemy->Init(pfile);
	//}

	//return m_pEnemy;

	return nullptr;
}
