//=============================================================================
// 
//  ステージの配置物ヘッダー [stageobj.h]
//  Author : 相馬靜雅
// 
//=============================================================================

#ifndef _STAGEOBJ_H_
#define _STAGEOBJ_H_		// 二重インクルード防止

#include "object.h"
#include "listmanager.h"

// 前方宣言
class CModel;

//==========================================================================
// クラス定義
//==========================================================================
// ステージの配置物クラス
class CStageObj : public CObject
{
public:
	
	//=============================
	// 列挙型定義
	//=============================
	enum State
	{
		STATE_NONE = 0,		// 無し
		STATE_APPEARANCE,	// 登場
		STATE_LEAVE,		// 退場
		STATE_MAX
	};

	// 種類
	enum Type
	{
		TYPE_BG = 0,	// 背景
		TYPE_OBSTACLE,	// 障害物
		TYPE_MAX
	};

	CStageObj(int nPriority = 6);
	~CStageObj();

	//=============================
	// オーバーライド関数
	//=============================
	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	//=============================
	// メンバ関数
	//=============================
	void Kill();		// 削除
	void SetState(const State& state);	// 状態設定
	virtual bool Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize);	// プレイヤーとの当たり判定

	//=============================
	// 静的関数
	//=============================
	/**
	@brief		生成処理
	@param	type	[in]	種類
	@param	pos		[in]	位置
	*/
	static CStageObj *Create(const Type& type, const MyLib::Vector3& pos);
	static CListManager<CStageObj> GetList() { return m_List; }	// リスト取得

protected:

	// メンバ変数
	CModel* m_pModel;		// モデルポインタ

private:

	//=============================
	// 関数リスト
	//=============================
	typedef void(CStageObj::*SAMPLE_FUNC)();
	static SAMPLE_FUNC m_SampleFuncList[];	// 状態関数のリスト

	//=============================
	// メンバ関数
	//=============================
	// 状態関数
	void UpdateState();		// 状態更新
	void StateNone();		// なし
	void StateAppearance();	// 登場
	void StateLeave();		// 退場

	//=============================
	// メンバ変数
	//=============================
	float m_fStateTime;		// 状態カウンター
	State m_state;			// 状態
	static CListManager<CStageObj> m_List;	// リスト

};


#endif