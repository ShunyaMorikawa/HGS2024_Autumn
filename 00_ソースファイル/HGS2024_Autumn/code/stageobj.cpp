//=============================================================================
// 
//  ステージの配置物処理 [transferBeacon.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "stageobj.h"
#include "manager.h"
#include "calculation.h"
#include "model.h"
#include "input.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const char* MODEL = "data\\MODEL\\box.x";
}

namespace StateTime
{
	const float APPEARANCE = 1.0f;	// 登場
	const float LEAVE = 1.0f;		// 退場
}

//==========================================================================
// 関数ポインタ
//==========================================================================
CStageObj::SAMPLE_FUNC CStageObj::m_SampleFuncList[] =
{
	&CStageObj::StateNone,			// なし
	&CStageObj::StateAppearance,	// 登場
	&CStageObj::StateLeave,			// 退場
};

//==========================================================================
// 静的メンバ変数
//==========================================================================
CListManager<CStageObj> CStageObj::m_List = {};	// リスト

//==========================================================================
// コンストラクタ
//==========================================================================
CStageObj::CStageObj(int nPriority) : CObject(nPriority),
m_fStateTime(0.0f),		// 状態タイマー
m_state(State::STATE_NONE),	// 状態
m_pModel(nullptr)		// モデル
{

}

//==========================================================================
// デストラクタ
//==========================================================================
CStageObj::~CStageObj()
{
	
}

//==========================================================================
// 生成処理
//==========================================================================
CStageObj *CStageObj::Create(const Type& type, const MyLib::Vector3& pos)
{
	// メモリの確保
	CStageObj* pObj = new CStageObj;

	if (pObj != nullptr)
	{
		// 引数設定
		pObj->SetPos(pos);
		pObj->SetOriginPosition(pos);

		// 初期化処理
		pObj->Init();
	}

	return pObj;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CStageObj::Init()
{
	// リストに追加
	m_List.Regist(this);

	// モデル生成
	m_pModel = CModel::Create(MODEL);
	m_pModel->SetType(CModel::TYPE_NOT_HIERARCHY);
	m_pModel->SetPosition(GetPos());

	// 登場
	SetState(State::STATE_APPEARANCE);
	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CStageObj::Uninit()
{
	if (m_pModel != nullptr)
	{// モデルの削除
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = nullptr;
	}

	// リストから削除
	m_List.Delete(this);

	// 終了
	Release();
}

//==========================================================================
// 削除
//==========================================================================
void CStageObj::Kill()
{
	if (m_pModel != nullptr)
	{// モデルの削除
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = nullptr;
	}

	// リストから削除
	m_List.Delete(this);

	// 終了
	Release();
}

//==========================================================================
// 更新処理
//==========================================================================
void CStageObj::Update()
{
	// 状態更新
	UpdateState();

	if (m_pModel != nullptr)
	{// モデルの更新
		m_pModel->SetPosition(GetPos());
		m_pModel->Update();
	}
}

//==========================================================================
// 状態更新
//==========================================================================
void CStageObj::UpdateState()
{
	// 状態カウンター加算
	m_fStateTime += CManager::GetInstance()->GetDeltaTime();

	// 状態別処理
	(this->*(m_SampleFuncList[m_state]))();
}

//==========================================================================
// なし
//==========================================================================
void CStageObj::StateNone()
{
	m_fStateTime = 0.0f;
}

//==========================================================================
// 登場
//==========================================================================
void CStageObj::StateAppearance()
{
	MyLib::Vector3 posOrigin = GetOriginPosition();	// 初期位置
	MyLib::Vector3 posDest = GetOriginPosition();	// 目標位置
	posDest.y = 0.0f;

	// 線形補間
	MyLib::Vector3 pos = posOrigin;
	pos.y = UtilFunc::Correction::EaseOutBack(posOrigin.y, posDest.y, 0.0f, StateTime::APPEARANCE, m_fStateTime);

	// 位置設定
	SetPos(pos);
}

//==========================================================================
// 退場
//==========================================================================
void CStageObj::StateLeave()
{
	MyLib::Vector3 posOrigin = GetOriginPosition();	// 初期位置
	MyLib::Vector3 posDest = GetOriginPosition();	// 目標位置
	posDest.y = 0.0f;

	// 線形補間
	MyLib::Vector3 pos = posOrigin;
	pos.y = UtilFunc::Correction::EaseInBack(0.0f, posOrigin.y, 0.0f, StateTime::APPEARANCE, m_fStateTime);

	// 位置設定
	SetPos(pos);
}

//==========================================================================
// 状態設定
//==========================================================================
void CStageObj::SetState(const State& state)
{
	m_fStateTime = 0.0f;	// 状態カウンター
	m_state = state;		// 状態
}

//==========================================================================
// 描画処理
//==========================================================================
void CStageObj::Draw()
{
	if (m_pModel != nullptr)
	{// モデルの描画
		m_pModel->Draw();
	}
}

