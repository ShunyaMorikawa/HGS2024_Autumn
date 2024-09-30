//========================================
//
// 障害物の処理[obstacle.h]
// Author：小原立暉
//
//========================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "stageobj.h"

//========================================
// 障害物クラス
//========================================
class CObstacle : public CStageObj
{
public:

	// 種類
	enum EType
	{
		TYPE_TREE = 0,	// 木
		TYPE_RIVER,		// 川
		TYPE_STONE,		// 石
		TYPE_HOLE,		// 穴
		TYPE_SOFTROCK,	// 柔らかい岩
		TYPE_MAX		// 列挙型の総数
	};

	CObstacle();		//コンストラクタ
	~CObstacle();		//デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	virtual bool Collision(const D3DXMATRIX& rMtx, const D3DXVECTOR3& rSize) override;	// プレイヤーとの当たり判定

	// 静的メンバ関数
	static CObstacle* Create(const EType type, const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot);

private:

	// メンバ変数
	EType m_type;		// 種類
};

#endif
