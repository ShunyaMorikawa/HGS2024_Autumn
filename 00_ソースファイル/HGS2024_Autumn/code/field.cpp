//========================================
//
// フィールド[field.cpp]
// Author：森川駿弥
//
//========================================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================================================
// 定数定義
//==========================================================================
namespace
{
	const float WIDTH = 2000.0f;	// 横幅
	const float HEIGHT = 200.0f;	// 縦幅
}

//========================================
//静的メンバ変数
//========================================
LPDIRECT3DTEXTURE9 CField::m_pTexture = nullptr;

//========================================
//コンストラクタ
//========================================
CField::CField(int nPriority) :
	CObject3D(nPriority)
{
}

//========================================
//デストラクタ
//========================================
CField::~CField()
{
}

//========================================
//ポリゴン生成
//========================================
CField* CField::Create(void)
{
	//CPlayer型のポインタ
	CField* pField = new CField;;

	//初期化
	pField->Init();

	//ポインタを返す
	return pField;
}

//========================================
//初期化
//========================================
HRESULT CField::Init(void)
{
	//テクスチャのポインタ
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	// 継承の初期化
	CObject3D::Init();

	//テクスチャ割り当て
	BindTexture(pTexture->Regist("data\\texture\\soil.jpg"));


	return S_OK;
}

//========================================
//終了
//========================================
void CField::Uninit(void)
{
	// 継承の初期化
	CObject3D::Uninit();
}

//========================================
//更新
//========================================
void CField::Update(void)
{
	// 継承の初期化
	CObject3D::Update();
}

//========================================
// 頂点情報
//========================================
void CField::SetVertex3D()
{
	// 頂点情報へのポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-WIDTH, 0.0f, HEIGHT);
	pVtx[1].pos = D3DXVECTOR3(WIDTH, 0.0f, HEIGHT);
	pVtx[2].pos = D3DXVECTOR3(-WIDTH, 0.0f, -HEIGHT);
	pVtx[3].pos = D3DXVECTOR3(WIDTH, 0.0f, -HEIGHT);

	// テクスチャ座標の設定
	float ratioX = 0.0f;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
	pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

	// 頂点バッファをアンロック
	GetVtxBuff()->Unlock();
}

//========================================
//描画
//========================================
void CField::Draw(void)
{
	//描画
	CObject3D::Draw();
}
