//========================================
//
// �t�B�[���h[field.cpp]
// Author�F�X��x��
//
//========================================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================================================
// �萔��`
//==========================================================================
namespace
{
	const float WIDTH = 2000.0f;	// ����
	const float HEIGHT = 200.0f;	// �c��
}

//========================================
//�ÓI�����o�ϐ�
//========================================
LPDIRECT3DTEXTURE9 CField::m_pTexture = nullptr;

//========================================
//�R���X�g���N�^
//========================================
CField::CField(int nPriority) :
	CObject3D(nPriority)
{
}

//========================================
//�f�X�g���N�^
//========================================
CField::~CField()
{
}

//========================================
//�|���S������
//========================================
CField* CField::Create(void)
{
	//CPlayer�^�̃|�C���^
	CField* pField = new CField;;

	//������
	pField->Init();

	//�|�C���^��Ԃ�
	return pField;
}

//========================================
//������
//========================================
HRESULT CField::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	// �p���̏�����
	CObject3D::Init();

	//�e�N�X�`�����蓖��
	BindTexture(pTexture->Regist("data\\texture\\soil.jpg"));


	return S_OK;
}

//========================================
//�I��
//========================================
void CField::Uninit(void)
{
	// �p���̏�����
	CObject3D::Uninit();
}

//========================================
//�X�V
//========================================
void CField::Update(void)
{
	// �p���̏�����
	CObject3D::Update();
}

//========================================
// ���_���
//========================================
void CField::SetVertex3D()
{
	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-WIDTH, 0.0f, HEIGHT);
	pVtx[1].pos = D3DXVECTOR3(WIDTH, 0.0f, HEIGHT);
	pVtx[2].pos = D3DXVECTOR3(-WIDTH, 0.0f, -HEIGHT);
	pVtx[3].pos = D3DXVECTOR3(WIDTH, 0.0f, -HEIGHT);

	// �e�N�X�`�����W�̐ݒ�
	float ratioX = 0.0f;
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 10.0f);
	pVtx[3].tex = D3DXVECTOR2(10.0f, 10.0f);

	// ���_�o�b�t�@���A�����b�N
	GetVtxBuff()->Unlock();
}

//========================================
//�`��
//========================================
void CField::Draw(void)
{
	//�`��
	CObject3D::Draw();
}
