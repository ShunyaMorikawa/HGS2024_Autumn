//========================================
//
//�^�C�g��[title.cpp]
//Author�F�X��x��
//
//========================================
#include "title.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "field.h"
#include "mapobject.h"
#include "wall.h"
#include "player.h"

//========================================
// �萔��`
//========================================
namespace
{
const char* TITLE_TEX = "data\\TEXTURE\\title.png";	// �^�C�g���e�N�X�`���̃p�X
}

//=======================================
//�R���X�g���N�^
//=======================================
CTitle::CTitle(int nPriority)
{
	m_pObj2D = nullptr;
}

//=======================================
//�f�X�g���N�^
//=======================================
CTitle::~CTitle()
{
}

//=======================================
//����
//=======================================
CTitle* CTitle::Create(void)
{
	//�^�C�g���̃|�C���^
	CTitle* pTitle = nullptr;

	//�C���X�^���X����
	pTitle = new CTitle;

	//������
	pTitle->Init();

	//�|�C���^��Ԃ�
	return pTitle;
}

//=======================================
//������
//=======================================
HRESULT CTitle::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	// �C���X�^���X����
	m_pObj2D = CObject2D::Create();

	// �ʒu�ݒ�
	m_pObj2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// �T�C�Y�ݒ�
	m_pObj2D->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// �e�N�X�`���ݒ�
	m_pObj2D->BindTexture(pTexture->Regist("data\\texture\\title.png"));

	// �T�E���h���擾
	CSound* pSound = CManager::GetInstance()->GetSound();

	// �T�E���h��~
	pSound->Stop();

	// �T�E���h�Đ�
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	//������Ԃ�
	return S_OK;
}

//=======================================
//�I��
//=======================================
void CTitle::Uninit(void)
{
}

//=======================================
//�X�V
//=======================================
void CTitle::Update(void)
{
	// �L�[�{�[�h�ƃp�b�h�̃|�C���^
	CInputKeyboard *pInputKeyboard = pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();	
	CInputPad *pInputPad = pInputPad = CManager::GetInstance()->GetInputPad();
	
	// �J�����̏��擾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || 
		pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) == true ||
		pInputPad->GetTrigger(CInputPad::BUTTON_START, 0) == true)
	{
		// ��ʑJ��(�t�F�[�h)
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TUTORIAL);
	}
}

//=======================================
//�`��
//=======================================
void CTitle::Draw(void)
{
}
