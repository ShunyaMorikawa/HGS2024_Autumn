//========================================
//
//プレイヤー処理[player.h]
//Author：森川駿弥
//
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

//========================================
// 前方宣言
//========================================
class CModel;
class CMotion;
class CEffect;
class CGauge;
class CLockonMarker;

//========================================
//プレイヤークラス
//========================================
class CPlayer : public CCharacter
{
public:
	// 状態
	enum PLAYERSTATE
	{// プレイヤーの状態
		STATE_NONE = 0,
		STATE_NORMAL,		// 通常
		STATE_DAMAGE,		// ダメージ
		STATE_DETAH,		// 死亡
		STATE_MAX
	};

	CPlayer(int nPriority = 4);		//コンストラクタ
	~CPlayer();		//デストラクタ

	// メンバ関数
	static CPlayer* Create(std::string pfile);

	HRESULT Init() { return S_OK; }		//純粋仮想
	HRESULT Init(std::string pfile);
	void Uninit();
	void Update();
	void Draw();

	float GetRadius() { return m_fRadius; }		// 半径取得
	int GetLife() { return m_nLife; }			// 体力取得
	int GetState() { return m_State; }			// 状態取得

	// 静的メンバ関数
	static CPlayer* GetInstance() { return m_pPlayer; }

private:

	// メンバ関数
	void Motion();
	void Move(D3DXVECTOR3& pos, const float fDeltaTime);

	// メンバ変数
	int m_apNumModel;		// モデル(パーツ)の総数
	int m_nLife;			// 体力
	int m_nOldMotion;		// 前回のモーション
	int m_WalkCounter;		// 歩行時のカウンター
	int m_State;			// 状態
	float m_fRadius;		// 半径
	bool m_bJump;			// ジャンプ
	CEffect* m_pEffect;				// エフェクトのポインタ
	CGauge* m_pGauge;				// ゲージのポインタ
	CModel* m_apModel[MAX_PARTS];	// モデルのダブルポインタ
	CLockonMarker* m_pMarker;		// ロックオンマーカーのポインタ

	// 静的メンバ変数
	static CPlayer* m_pPlayer;		// 自身のポインタ
};

#endif
