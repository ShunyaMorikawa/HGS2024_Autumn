//========================================
//
// 障害物の処理[reverse.h]
// Author：相馬靜雅
//
//========================================
#ifndef _REVERSE_H_
#define _REVERSE_H_

#include "stageobj.h"
class CBillboard;

//========================================
// 障害物クラス
//========================================
class CReverse : public CStageObj
{
public:

	CReverse();		//コンストラクタ
	~CReverse();	//デストラクタ

	// メンバ関数
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Kill() override;

	virtual bool Collision(const D3DXMATRIX& rMtx, const D3DXVECTOR3& rSize) override;	// プレイヤーとの当たり判定
	static CListManager<CReverse> GetList() { return m_List; }	// リスト取得

private:

	CBillboard* m_pBillboard;		// ビルボードオブジェクト
	static CListManager<CReverse> m_List;	// リスト
};

#endif
