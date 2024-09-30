//========================================
//
// 障害物の処理[reverse.h]
// Author：相馬靜雅
//
//========================================
#ifndef _REVERSE_H_
#define _REVERSE_H_

#include "stageobj.h"

//========================================
// 障害物クラス
//========================================
class CReverse : public CStageObj
{
public:

	CReverse();		//コンストラクタ
	~CReverse();	//デストラクタ

	// メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	virtual bool Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize) override;	// プレイヤーとの当たり判定
	static CListManager<CReverse> GetList() { return m_List; }	// リスト取得

private:

	static CListManager<CReverse> m_List;	// リスト
};

#endif
