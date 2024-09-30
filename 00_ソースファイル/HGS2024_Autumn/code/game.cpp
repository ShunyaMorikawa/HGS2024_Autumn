//========================================
//
//�Q�[��������[game.cpp]
//Author�F�X��x��
//
//========================================
#include "game.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "texture.h"
#include "fade.h"

#include "timer.h"
#include "field.h"
#include "stageobj.h"

//========================================
//�ÓI�����o�ϐ�
//========================================
CGame *CGame::m_pGame = nullptr;			// �Q�[���̃|�C���^

//========================================
// �萔��`
//========================================
namespace
{
const int TRANSITIONTIME = 180;		// �J�ڂ���܂ł̎���

const char* PLAYER_PASS = "data\\FILE\\turtle.txt"; // �v���C���[�̃p�X
}

//========================================
//�R���X�g���N�^
//========================================
CGame::CGame() : 
	m_bPause(false),
	m_pFade(nullptr)
{
	m_pGame = nullptr;
}

//========================================
//�f�X�g���N�^
//========================================
CGame::~CGame()
{
}

//========================================
//����
//========================================
CGame *CGame::Create(void)
{
	if (m_pGame == nullptr)
	{
		//�C���X�^���X����
		m_pGame = new CGame;
	}

	//�|�C���^��Ԃ�
	return m_pGame;
}

//========================================
//������
//========================================
HRESULT CGame::Init(void)
{
	//�e�N�X�`���̃|�C���^
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	CField::Create();

	// �v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(PLAYER_PASS);
	}

	// �^�C�}�[
	CTimer::Create();

	return S_OK;
}

//========================================
//�I��
//========================================
void CGame::Uninit(void)
{
	if(m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}

	m_pGame = nullptr;
}

//========================================
//�X�V
//========================================
void CGame::Update(void)
{
	// CInputKeyboard�^�̃|�C���^
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_F2) == true)
	{// �Q�[����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);
	}

	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		CStageObj::Create(CStageObj::Type::TYPE_REVERSE, MyLib::Vector3(500.0f, 500.0f, 0.0f));
	}
#endif
}

//========================================
//�`��
//========================================
void CGame::Draw(void)
{
}
