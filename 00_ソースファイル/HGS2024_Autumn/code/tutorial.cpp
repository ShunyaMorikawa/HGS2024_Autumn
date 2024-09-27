//========================================
//
//�`���[�g���A��[tutorial.h]
//Author�F�X��x��
//
//========================================
#include "tutorial.h"
#include "manager.h"
#include "player.h"
#include "field.h"
#include "bullet.h"
#include "fade.h"
#include "texture.h"
#include "wall.h"
#include "mapobject.h"
#include "sound.h"

//=======================================
//�R���X�g���N�^
//=======================================
CTutorial::CTutorial()
{
}

//=======================================
//�f�X�g���N�^
//=======================================
CTutorial::~CTutorial()
{
}

//=======================================
//����
//=======================================
CTutorial* CTutorial::Create(void)
{
	//�^�C�g���̃|�C���^
	CTutorial* pTutorial = nullptr;

	//�C���X�^���X����
	pTutorial = new CTutorial;

	//�|�C���^��Ԃ�
	return pTutorial;
}

//=======================================
//������
//=======================================
HRESULT CTutorial::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	// �v���C���[����
	m_pPlayer = CPlayer::Create("data\\FILE\\player.txt");

	// �t�B�[���h����
	m_pField = CField::Create();

	// �ǐ���
	CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -4000.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 4000.0f), D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
	CWall::Create(D3DXVECTOR3(4000.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, -D3DX_PI * 0.5f, 0.0f));
	CWall::Create(D3DXVECTOR3(-4000.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI * 0.5f, 0.0f));

	// �}�b�v�I�u�W�F�N�g����
	m_pMobj = CMapObject::Create();

	// �C���X�^���X����
	m_pObj2D = CObject2D::Create();

	// �ʒu�ݒ�
	m_pObj2D->SetPos(D3DXVECTOR3(1000.0f, 200.0f, 0.0f));

	// �T�C�Y�ݒ�
	m_pObj2D->SetSize(300.0f, 350.0f);

	// �e�N�X�`���ݒ�
	m_pObj2D->BindTexture(pTexture->Regist("data\\texture\\guide_tutorial.png"));

	// �T�E���h���擾
	CSound* pSound = CManager::GetInstance()->GetSound();

	// �T�E���h��~
	pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

	// �T�E���h�Đ�
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TUTORIAL);

	//������Ԃ�
	return S_OK;
}

//=======================================
//�I��
//=======================================
void CTutorial::Uninit(void)
{
}

//=======================================
//�X�V
//=======================================
void CTutorial::Update(void)
{
	//CInputKeyboard���擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//CInputPad���擾
	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN)||
		pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		// ��ʑJ��(�t�F�[�h)
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//=======================================
//�`��
//=======================================
void CTutorial::Draw(void)
{
}
