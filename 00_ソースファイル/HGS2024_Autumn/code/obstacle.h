//========================================
//
// 障害物の処理[obstacle.h]
// Author：森川駿弥
//
//========================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "model.h"

//========================================
// 障害物クラス
//========================================
class CObstacle : public CModel
{
public:

	// 種類
	enum EType
	{
		TYPE_TREE = 0,	// 木
		TYPE_RIVER,		// 川
		TYPE_STONE,		// 石
		TYPE_MAX		// 列挙型の総数
	};

	CObstacle();		//コンストラクタ
	~CObstacle();		//デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CObstacle* Create(std::string pfile);

private:


};

#endif
