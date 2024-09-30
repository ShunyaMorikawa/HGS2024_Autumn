//========================================
//
//�V���[�e�B���O�A�N�V����[Number.cpp]
//Author�F�X��x��
//
//========================================
#include "number.h"
#include "texture.h"
#include "manager.h"
#include "debugproc.h"

//========================================
//�R���X�g���N�^
//========================================
CNumber::CNumber()
{

}

//========================================
//�f�X�g���N�^
//========================================
CNumber::~CNumber()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CNumber::Init(void)
{
	// �e�N���X�̏���������
	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CNumber::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CNumber::Update(void)
{
	// �e�N���X�̍X�V����
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CNumber::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObject2D::Draw();
}

//========================================
//�i���o�[����
//========================================
CNumber *CNumber::Create(void)
{
	// �|�C���^�錾
	CNumber *pNumber = nullptr;

	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	if (pNumber == nullptr)
	{
		//����
		pNumber = new CNumber;

		//������
		pNumber->Init();

		pNumber->BindTexture(pTexture->Regist("data\\TEXTURE\\number.png"));
	}

	//�|�C���^��Ԃ�
	return pNumber;
}
