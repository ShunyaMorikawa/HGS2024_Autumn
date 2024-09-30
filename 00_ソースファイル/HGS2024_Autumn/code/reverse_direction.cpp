//=============================================================================
// 
//  反転演出処理 [reverse_direction.cpp]
//  Author : 相馬靜雅
// 
//=============================================================================
#include "reverse_direction.h"
#include "manager.h"
#include "texture.h"
#include "calculation.h"
#include "input.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const std::string TEXTURE_SAMPLE = "data\\TEXTURE\\reverse.png";	// テクスチャのファイル
}

//==========================================================================
// コンストラクタ
//==========================================================================
CReverse_Direction::CReverse_Direction(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
}

//==========================================================================
// デストラクタ
//==========================================================================
CReverse_Direction::~CReverse_Direction()
{

}

//==========================================================================
// 生成処理
//==========================================================================
CReverse_Direction* CReverse_Direction::Create()
{
	// メモリの確保
	CReverse_Direction* pObj = new CReverse_Direction;

	if (pObj != nullptr)
	{
		// 初期化処理
		pObj->Init();
	}

	return pObj;
}

//==========================================================================
// 初期化処理
//==========================================================================
HRESULT CReverse_Direction::Init()
{

	// オブジェクト2Dの初期化
	CObject2D::Init();

	// テクスチャ設定
	int texID = CTexture::GetInstance()->Regist(TEXTURE_SAMPLE);
	BindTexture(texID);

	// サイズ設定
	D3DXVECTOR2 size = CTexture::GetInstance()->GetImageSize(texID);

#if 0	// 横幅を元にサイズ設定
	size = UtilFunc::Transformation::AdjustSizeByWidth(size, 240.0f);

#else	// 縦幅を元にサイズ設定
	size = UtilFunc::Transformation::AdjustSizeByWidth(size, 240.0f);
#endif
	SetSize(size.x, size.y);
	SetSizeOrigin(size);


	// 位置、向き設定は必要があれば追加


	return S_OK;
}

//==========================================================================
// 終了処理
//==========================================================================
void CReverse_Direction::Uninit()
{
	// 終了処理
	CObject2D::Uninit();
}

//==========================================================================
// 更新処理
//==========================================================================
void CReverse_Direction::Update()
{
	// 更新処理
	CObject2D::Update();
}

//==========================================================================
// 描画処理
//==========================================================================
void CReverse_Direction::Draw()
{
	// 描画処理
	CObject2D::Draw();
}
