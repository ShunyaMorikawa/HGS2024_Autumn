//========================================
//
//シューティングアクション[Number.cpp]
//Author：森川駿弥
//
//========================================
#include "number.h"
#include "texture.h"
#include "manager.h"
#include "debugproc.h"

//========================================
//コンストラクタ
//========================================
CNumber::CNumber()
{

}

//========================================
//デストラクタ
//========================================
CNumber::~CNumber()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CNumber::Init(void)
{
	// 親クラスの初期化処理
	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CNumber::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CNumber::Update(void)
{
	// 親クラスの更新処理
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CNumber::Draw(void)
{
	// 親クラスの描画処理
	CObject2D::Draw();
}

//========================================
//ナンバー生成
//========================================
CNumber *CNumber::Create(void)
{
	// ポインタ宣言
	CNumber *pNumber = nullptr;

	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	if (pNumber == nullptr)
	{
		//生成
		pNumber = new CNumber;

		//初期化
		pNumber->Init();

		pNumber->BindTexture(pTexture->Regist("data\\TEXTURE\\number.png"));
	}

	//ポインタを返す
	return pNumber;
}
