//========================================
//
// ��Q���̏���[reverse.cpp]
// Author�F���n�Ή�
//
//========================================
#include "reverse.h"
#include "model.h"
#include "calculation.h"
#include "billboard.h"
#include "manager.h"
#include "texture.h"

//========================================
//���O���
//========================================
namespace
{
	const char* TEXTURE = "data\\TEXTURE\\reverse.png";	// ���f���̃p�X
	const float COLLISIONRANGE = 200.0f;	// �L���͈�
}
CListManager<CReverse> CReverse::m_List = {};	// ���X�g

//========================================
//�R���X�g���N�^
//========================================
CReverse::CReverse() : CStageObj(),
m_pBillboard(nullptr)
{

}

//========================================
//�f�X�g���N�^
//========================================
CReverse::~CReverse()
{

}

//========================================
// ������
//========================================
HRESULT CReverse::Init(void)
{
	// ���X�g�ɒǉ�
	m_List.Regist(this);

	// �r���{�[�h����
	m_pBillboard = CBillboard::Create(GetPos(), 200.0f, 200.0f);

	//�e�N�X�`���̃|�C���^
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	int texIdx = pTexture->Regist(TEXTURE);
	m_pBillboard->BindTexture(texIdx);

	if (FAILED(CStageObj::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CReverse::Uninit(void)
{
	// ���X�g����폜
	m_List.Delete(this);

	// �I��
	CStageObj::Uninit();
}

//========================================
// �폜
//========================================
void CReverse::Kill()
{
	if (m_pBillboard != nullptr)
	{
		m_pBillboard->Uninit();
		m_pBillboard = nullptr;
	}

	// �I��
	CReverse::Uninit();
}

//========================================
// �X�V
//========================================
void CReverse::Update(void)
{
	// �X�V
	CStageObj::Update();

	if (m_pBillboard != nullptr)
	{
		m_pBillboard->SetPos(GetPos());
		m_pBillboard->Update();
	}
}

//========================================
// �`��
//========================================
void CReverse::Draw(void)
{
	if (m_pBillboard != nullptr)
	{
		m_pBillboard->Draw();
	}

	// �`��
	CStageObj::Draw();
}

//========================================
// �v���C���[�Ƃ̓����蔻��
//========================================
bool CReverse::Collision(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rSize)
{
	bool bHit = false;

	// �ʒu�擾
	MyLib::Vector3 pos = GetPos();

	if (UtilFunc::Collision::CircleRange3D(pos, rPos, COLLISIONRANGE, rSize.x))
	{
		Kill();
		bHit = true;
	}

	return bHit;

}
