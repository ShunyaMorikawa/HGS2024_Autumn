//========================================
//
//  ���U���g [result.h]
//  Author�F���n�Ή�
//
//========================================
#include "result.h"
#include "resultscore.h"
#include "manager.h"
#include "fade.h"
#include "texture.h"
#include "sound.h"

//=======================================
//�R���X�g���N�^
//=======================================
CResult::CResult()
{
}

//=======================================
//�f�X�g���N�^
//=======================================
CResult::~CResult()
{
}

//=======================================
//����
//=======================================
CResult* CResult::Create(void)
{
	//�^�C�g���̃|�C���^
	CResult* pTutorial = nullptr;

	//�C���X�^���X����
	pTutorial = new CResult;

	//�|�C���^��Ԃ�
	return pTutorial;
}

//=======================================
//������
//=======================================
HRESULT CResult::Init(void)
{
	// �e�N�X�`���̃|�C���^
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	// �C���X�^���X����
	m_pObj2D = CObject2D::Create();

	// �ʒu�ݒ�
	m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// �T�C�Y�ݒ�
	m_pObj2D->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// �e�N�X�`���ݒ�
	m_pObj2D->BindTexture(pTexture->Regist("data\\texture\\result.png"));

	// ����̃X�R�A
	m_pScore = CResultScore::Create(m_pObj2D->GetPos() + MyLib::Vector3(0.0f, -50.0f, 0.0f));


	//������Ԃ�
	return S_OK;
}

//=======================================
// �I��
//=======================================
void CResult::Uninit(void)
{
}

//=======================================
// �X�V
//=======================================
void CResult::Update(void)
{
	
}

//=======================================
// �`��
//=======================================
void CResult::Draw(void)
{
}
