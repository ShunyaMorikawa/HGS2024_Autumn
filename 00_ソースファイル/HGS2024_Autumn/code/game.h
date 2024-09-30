//========================================
//
//ゲーム内処理[game.h]
//Author：森川駿弥
//
//========================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "manager.h"

//========================================
//前方宣言
//========================================
class CPlayer;
class CFade;
class CTimer;
class CStageManager;
class CStageEdittor;

//========================================
//ゲームクラス
//========================================
class CGame : public CScene
{
public:
	CGame();	//コンストラクタ
	~CGame();	//デストラクタ

	//メンバ関数
	static CGame *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PauseState(bool bPauseState) { m_bPause = bPauseState; }	//ポーズ状態かどうか

	static CGame* GetInstance(void) { return m_pGame; }		// ゲームマネージャーの情報
	
private:
	static CGame *m_pGame;		// ゲームマネージャーのポインタ

	int m_nTransition;			// カウンター

	bool m_bPause;				// ポーズ状態のON/OFF

	CFade* m_pFade;					// フェードのポインタ
	CPlayer* m_pPlayer;				// プレイヤーポインタ
	CTimer* m_pTimer;				// タイマーのポインタ
	CStageManager* m_pStageManager;	// ステージマネージャー

#ifdef _DEBUG

	CStageEdittor* m_pEdittor;		// エディター

#endif // _DEBUG
};

#endif
