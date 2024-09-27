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
#include "field.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "wall.h"
#include "mapobject.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"

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
}

//========================================
//�R���X�g���N�^
//========================================
CGame::CGame() : 
	m_bPause(false),
	m_nTransition(0),
	m_pObjectX(nullptr),
	m_pIdxMesh(nullptr),
	m_pFade(nullptr),
	m_pObj2D(nullptr)
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

	// �v���C���[����
	CPlayer::Create("data//FILE//player.txt");

	// �t�B�[���h����
	CField::Create();

	// �G�l�~�[����
	CEnemy::Create("data//FILE//motion.txt");

	// 4�����ɕǐ���
	CWall::Create(D3DXVECTOR3(0.0f, 2000.0f, -4000.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	CWall::Create(D3DXVECTOR3(0.0f, 2000.0f, 4000.0f), D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI, 0.0f));
	CWall::Create(D3DXVECTOR3(4000.0f, 2000.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f,  -D3DX_PI * 0.5f, 0.0f));
	CWall::Create(D3DXVECTOR3(-4000.0f, 2000.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f,  D3DX_PI * 0.5f, 0.0f));

	// �}�b�v�I�u�W�F�N�g����
	CMapObject::Create();

	// �J�ڎ���
	m_nTransition = 0;

	//�|�[�Y�̏��
	m_bPause = false;

	// �C���X�^���X����
	m_pObj2D = CObject2D::Create();

	// �ʒu�ݒ�
	m_pObj2D->SetPos(D3DXVECTOR3(1100.0f, 300.0f, 0.0f));

	// �T�C�Y�ݒ�
	m_pObj2D->SetSize(300.0f, 350.0f);

	// �e�N�X�`���ݒ�
	m_pObj2D->BindTexture(pTexture->Regist("data\\texture\\guide_game.png"));

	// �T�E���h���擾
	CSound* pSound = CManager::GetInstance()->GetSound();

	// �T�E���h��~
	pSound->Stop(CSound::SOUND_LABEL_BGM_TUTORIAL);

	// �T�E���h�Đ�
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//========================================
//�I��
//========================================
void CGame::Uninit(void)
{
	if(m_pObj2D != nullptr)
	{
		m_pObj2D->Uninit();
		m_pObj2D = nullptr;
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

	// �v���C���[�̏��擾
	CPlayer* pPlayer = CPlayer::GetInstance();

	// �G�̏��擾
	CEnemy* pEnemy = CEnemy::GetInstance();

	if (pEnemy == nullptr || pPlayer == nullptr)
	{// �G���v���C���[�̗̑͂�0�ȉ��ɂȂ�����
		m_nTransition++;

		if (m_nTransition > TRANSITIONTIME ||
			pInputKeyboard->GetTrigger(DIK_RETURN))
		{
			// ��ʑJ��(�t�F�[�h)
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);

			m_nTransition = 0;
		}
	}

	// �f�o�b�O�\���̏��擾
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDebugProc();

	// �f�o�b�O�\��
	pDebugProc->Print("\n�J�E���^�[�F%d\n", m_nTransition);

#ifdef _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_F2) == true)
	{// �Q�[����ʂɑJ��
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITLE);
	}
#endif
}

//========================================
//�`��
//========================================
void CGame::Draw(void)
{
}
