//========================================
//
// �v���C���[[player.cpp]
// Author�F�X��x��
//
//========================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "debugproc.h"
#include "game.h"
#include "particle.h"
#include "useful.h"
#include "gauge.h"
#include "main.h"
#include "model.h"
#include "motion.h"
#include "effect.h"
#include "object2D.h"
#include "object3D.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "lockonMarker.h"

//========================================
// �萔��`
//========================================
namespace
{
	const int LIFE = 10;			// �̗�
	const float SPEED = 240.0f;		// ���x
	const float JUMP_MOVE = 1500.0f;	// �W�����v��
	const float JUMP_SAB = JUMP_MOVE * 0.04f;	// �W�����v����
	const float RADIUS = 50.0f;		// ���a
}

//========================================
// �ÓI�����o�ϐ�
//========================================
CPlayer* CPlayer::m_pPlayer = nullptr;

//========================================
//�R���X�g���N�^
//========================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority),
m_apNumModel	(0),			// ���f���̑���
m_nLife			(0),			// �̗�
m_nOldMotion	(0),			// �O��̃��[�V����
m_WalkCounter	(0),			// ���s���G�t�F�N�g�o���p�̃J�E���^�[
m_State			(STATE_NONE),	// ���
m_fRadius		(0.0f),			// ���a
m_bJump			(false),		// �W�����v�t���O
m_pEffect		(nullptr),		// �G�t�F�N�g�̃|�C���^
m_pGauge		(nullptr),		// �Q�[�W�̃|�C���^
m_pMarker		(nullptr)		// ���b�N�I���}�[�J�[�\��
{
	memset(&m_apModel[0], 0, sizeof(m_apModel));	//���f�����
}

//========================================
//�f�X�g���N�^
//========================================
CPlayer::~CPlayer()
{
}

//========================================
//�v���C���[�̐���
//========================================
CPlayer *CPlayer::Create(std::string pfile)
{
	if (m_pPlayer == nullptr)
	{
		//�v���C���[����
		m_pPlayer = new CPlayer;

		//������
		m_pPlayer->Init(pfile);
	}

	//�|�C���^��Ԃ�
	return m_pPlayer;
}

//========================================
// ������
//========================================
HRESULT CPlayer::Init(std::string pfile)
{
	// �L�����̏�����
	CCharacter::Init(pfile);

	// �v���C���[��Ԃ̏�����
	m_State = STATE_NORMAL;

	// �ʒu�ݒ�
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 500.0f));

	// �����ݒ�
	SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// �ړ��ʐݒ�
	SetMove(D3DXVECTOR3(SPEED, 0.0f, 0.0));

	// ���s���̃J�E���^�[
	m_WalkCounter = 0;

	// �̗�
	m_nLife = LIFE;

	// ���a
	m_fRadius;

	// �Q�[�W����
	m_pGauge = CGauge::Create(m_nLife);

	// �ʒu�ݒ�
	m_pGauge->SetPos(D3DXVECTOR3(50.0f, 600.0f, 0.0f));

	// �T�C�Y�ݒ�
	m_pGauge->SetSize(50.0f, 50.0f);

	return S_OK;
}

//========================================
//�I��
//========================================
void CPlayer::Uninit(void)
{
	// �I��
	CCharacter::Uninit();

	m_pPlayer = nullptr;

	m_pGauge->Uninit();
	m_pGauge = nullptr;
}

//========================================
//�X�V
//========================================
void CPlayer::Update(void)
{
	// ���g�̏����擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 rot = GetRot();

	// �f���^�^�C���̎擾
	const float fDeltaTime = CManager::GetInstance()->GetDeltaTime();

	// �J�����̒Ǐ]�ݒ�
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->Following(pos, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// �ړ�����
	Move(pos, move, fDeltaTime);

	// ���n����
	Land(pos, move);

	// �Q�[�W�ɑ̗͐ݒ�
	m_pGauge->SetLife(m_nLife);

	if (m_nLife <= 0)
	{
		//�e�N�X�`���̏��擾
		CTexture* pTexture = CManager::GetInstance()->GetTexture();

		// �T�E���h���擾
		CSound* pSound = CManager::GetInstance()->GetSound();

		// ����
		CObject2D* pObje2D = CObject2D::Create();

		// �ʒu�ݒ�
		pObje2D->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

		// �T�C�Y�ݒ�
		pObje2D->SetSize(SCREEN_WIDTH, 200.0f);

		// �s�k�e�N�X�`��
		pObje2D->BindTexture(pTexture->Regist("data\\texture\\lose.png"));

		// �T�E���h��~
		pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);

		// �T�E���h�Đ�
		pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_LOSE);

		// �I��
		Uninit();
	}

	// ���[�V����
	Motion();

	// ����ݒ�
	SetPos(pos);
	SetMove(move);
	SetRot(rot);

	// �f�o�b�O�\��
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̈ʒu�F%f�A%f�A%f\n", pos.x, pos.y, pos.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̈ړ��ʁF%f�A%f�A%f\n", move.x, move.y, move.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̌����F%f�A%f�A%f\n", rot.x, rot.y, rot.z);
	DebugProc::Print(DebugProc::POINT_LEFT, "�v���C���[�̗̑́F%d\n", m_nLife);
}

//========================================
//�`��
//========================================
void CPlayer::Draw(void)
{
	// �`��
	CCharacter::Draw();
}

//========================================
// ���[�V�����Ǘ�
//========================================
void CPlayer::Motion()
{
	// ���[�V�������擾
	CMotion* pMotion = GetMotion();

	// ���[�V������null�̏ꍇ�֐��𔲂���
	if (pMotion == nullptr)
	{
		assert(false);
		return;
	}

	// ���[�V������ݒ�
	switch (m_State)
	{
	case STATE_NORMAL: // �ʏ���

		// ���s���[�V������ݒ�
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_WALK);

		break;

	default: // ���̑��̏ꍇ
		
		// �x��
		assert(false);

		// �ҋ@���[�V������ݒ�
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_NEUTRAL);

		break;
	}

	// ���[�V�������X�V
	pMotion->Update();
}

//==========================================
//  �ړ�����
//==========================================
void CPlayer::Move(D3DXVECTOR3& pos, D3DXVECTOR3& move, const float fDeltaTime)
{
	// �C���v�b�g���̎擾
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputPad* pPad = CManager::GetInstance()->GetInputPad();

#ifdef _DEBUG
	// 0�L�[�ŏ����ʒu�ɖ߂�
	if (pKeyboard->GetTrigger(DIK_2))
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		return;
	}

	// �f�o�b�O���͉E�V�t�g�������Ȃ��Ɠ����Ȃ�
	if (!pKeyboard->GetPress(DIK_RSHIFT))
	{
		return;
	}
#endif

	// �W�����v����
	Jump(move, pPad, pKeyboard);

	// TODO : �^�C�}�[���o���������������ǉ�

	// ���W�Ɉړ��ʂ����Z
	pos += move * fDeltaTime;
}

//==========================================
//  �W�����v����
//==========================================
void CPlayer::Jump(D3DXVECTOR3& move, CInputPad* pPad, CInputKeyboard* pKeyboard)
{
	// �W�����v���̏ꍇ�֐��𔲂���
	if (m_bJump) { return; }

	// �{�^���������ꂽ��W�����v����
	if (pPad->GetTrigger(CInputPad::BUTTON_A, 0) || pKeyboard->GetTrigger(DIK_SPACE))
	{
		// �W�����v�t���O��ݒ�
		m_bJump = true;

		// �ړ��ʂ����Z
		move.y += JUMP_MOVE;
	}
}

//==========================================
//  ���n����
//==========================================
void CPlayer::Land(D3DXVECTOR3& pos, D3DXVECTOR3& move)
{
	// y���W��0.0����������ꍇ�␳����
	if (pos.y < 0.0f)
	{
		// �W�����v�t���O��false
		m_bJump = false;

		// ���W��␳
		pos.y = 0.0f;

		// �ړ��ʂ��폜
		move.y = 0.0f;
	}

	// �W�����v���Ȃ�ړ��ʂ�����������
	if (m_bJump)
	{
		move.y -= JUMP_SAB;
	}
}
