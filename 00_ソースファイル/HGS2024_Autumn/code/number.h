//========================================
//
//シューティングアクション[number.h]
//Author：森川駿弥
//
//========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"

//========================================
//ナンバークラス
//========================================
class CNumber : public CObject2D
{
public:
	CNumber();		//コンストラクタ
	~CNumber();		//デストラクタ

	HRESULT Init(void);		//初期化
	void Uninit(void);		//終了
	void Update(void);		//更新
	void Draw(void);		//描画

	//メンバ関数
	static CNumber *Create(void);	//プレイヤー生成
};

#endif