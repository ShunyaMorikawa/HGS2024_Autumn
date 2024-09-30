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
const float NOCKBACK = 50.0f;	// �m�b�N�o�b�N�l
const float SPEED = 4.0f;		// ���x
const float INERTIA = 0.3f;		// ����
const float RADIUS = 50.0f;		// ���a
const float FIELD_LIMIT = 4000.0f;	// �t�B�[���h�̑傫��
const float MARKERPOS = 200.0f;		// ���b�N�I���}�[�J�[�̈ʒu
}

//========================================
// �ÓI�����o�ϐ�
//========================================
CPlayer* CPlayer::m_pPlayer = nullptr;

//========================================
//�R���X�g���N�^
//========================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority)
{//�l���N���A
	m_apNumModel = 0;		// ���f���̑���
	m_nLife = 0;			// �̗�
	m_nOldMotion = 0;		// �O��̃��[�V����
	m_WalkCounter = 0;		// ���s���G�t�F�N�g�o���p�̃J�E���^�[
	m_nState = STATE_NONE;	// ���
	m_fRadius = 0.0f;		// ���a
	m_bJump  = false;		// �m�b�N�o�b�N
	m_bMove = false;		// �ړ�
	m_bWait = false;		// �ҋ@
	m_bMowingdown = false;	// �U��
	m_bCutdown = false;		// �؂艺��
	m_bStrongAttack = false;	// ���U��
	m_IsLock = false;		// ���b�N�I��
	m_pEffect = nullptr;	// �G�t�F�N�g�̃|�C���^
	m_pGauge = nullptr;		// �Q�[�W�̃|�C���^
	m_pMarker = nullptr;	// ���b�N�I���}�[�J�[�\��
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
	m_nState = STATE_NORMAL;

	// �ʒu�ݒ�
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 500.0f));

	// �����ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
	// �L�[�{�[�h�̏��擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �R���g���[���[�̏��擾	
	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();

	//�e�N�X�`���̏��擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	// �T�E���h���擾
	CSound* pSound = CManager::GetInstance()->GetSound();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �v���C���[�s��
	Act(SPEED);

	// �Q�[�W�ɑ̗͐ݒ�
	m_pGauge->SetLife(m_nLife);

	if (m_nLife <= 0)
	{
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

	if (pInputKeyboard->GetTrigger(DIK_R) ||
		pInputPad->GetTrigger(CInputPad::BUTTON_PUSHING_R, 0))
	{
		m_IsLock = m_IsLock ? false : true;

		if (m_IsLock)
		{// ���b�N�I��
			if (m_pMarker == nullptr)
			{// �}�[�J�[����
				m_pMarker = CLockonMarker::Create(true);
			}
		}
		else
		{
			if (m_pMarker != nullptr)
			{// �}�[�J�[�폜
				m_pMarker->Uninit();
				m_pMarker = nullptr;
			}
		}
	}

	// �f�o�b�O�\��
	DebugProc::Print(DebugProc::POINT_LEFT, "\n�v���C���[�̈ʒu�F%f�A%f�A%f\n", pos.x, pos.y, pos.z);
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
// �s��
//========================================
void CPlayer::Act(float fSpeed)
{
	// ���[�V��������
	m_bMove = false;

	// �L�[�{�[�h�̏��擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �R���g���[���[�̏��擾	
	CInputPad* pInputPad = CManager::GetInstance()->GetInputPad();

	//CCamera�^�̃|�C���^
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌����擾
	D3DXVECTOR3 Camrot = pCamera->GetRot();

	// �ړI�̌���
	D3DXVECTOR3 DiffRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ړ��ʎ擾
	D3DXVECTOR3 move = GetMove();

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �ړI�̌����擾
	D3DXVECTOR3 RotDest = GetRotDest();

	if (pInputKeyboard->GetPress(DIK_A) == true
		|| pInputPad->GetLStickXPress(CInputPad::BUTTON_L_STICK, 0) < 0)
	{//A�������ꂽ
		if (pInputKeyboard->GetPress(DIK_W) == true
			|| pInputPad->GetLStickYPress(CInputPad::BUTTON_L_STICK, 0) > 0)
		{//����
			m_bMove = true;

			move.x += sinf(Camrot.y + D3DX_PI * 0.75f) * fSpeed;
			move.z += cosf(Camrot.y + D3DX_PI * 0.75f) * fSpeed;

			//�ړ������Ƀ��f����������
			RotDest.y = Camrot.y - D3DX_PI * 0.25f;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true
			|| pInputPad->GetLStickYPress(CInputPad::BUTTON_L_STICK, 0) < 0)
		{//����
			m_bMove = true;

			move.x += sinf(Camrot.y + D3DX_PI * 0.25f) * fSpeed;
			move.z += cosf(Camrot.y + D3DX_PI * 0.25f) * fSpeed;

			//�ړ������Ƀ��f����������
			RotDest.y = Camrot.y - D3DX_PI * 0.75f;
		}
		else
		{//��
			m_bMove = true;

			move.x += sinf(Camrot.y + D3DX_PI * 0.5f) * fSpeed;
			move.z += cosf(Camrot.y + D3DX_PI * 0.5f) * fSpeed;

			//�ړ������Ƀ��f����������
			RotDest.y = Camrot.y - D3DX_PI * 0.5f;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true
		|| pInputPad->GetLStickXPress(CInputPad::BUTTON_L_STICK, 0) > 0)
	{//D�������ꂽ
		if (pInputKeyboard->GetPress(DIK_W) == true
			|| pInputPad->GetLStickYPress(CInputPad::BUTTON_L_STICK, 0) > 0)
		{//�E��
			m_bMove = true;

			move.x += sinf(Camrot.y + -D3DX_PI * 0.75f) * fSpeed;
			move.z += cosf(Camrot.y + -D3DX_PI * 0.75f) * fSpeed;

			//�ړ������Ƀ��f����������
			RotDest.y = Camrot.y + D3DX_PI * 0.25f;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true
			|| pInputPad->GetLStickXPress(CInputPad::BUTTON_L_STICK, 0) > 0)
		{//�E��
			m_bMove = true;

			move.x += sinf(Camrot.y + -D3DX_PI * 0.25f) * fSpeed;
			move.z += cosf(Camrot.y + -D3DX_PI * 0.25f) * fSpeed;

			//�ړ������Ƀ��f����������
			RotDest.y = Camrot.y + D3DX_PI * 0.75f;
		}
		else
		{//�E
			m_bMove = true;

			move.x += sinf(Camrot.y + -D3DX_PI * 0.5f) * fSpeed;
			move.z += cosf(Camrot.y + -D3DX_PI * 0.5f) * fSpeed;

			//�ړ������Ƀ��f����������
			RotDest.y = Camrot.y + D3DX_PI * 0.5f;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true
		|| pInputPad->GetLStickYPress(CInputPad::BUTTON_L_STICK, 0) > 0)
	{//W�������ꂽ
		m_bMove = true;

		move.x += sinf(Camrot.y + D3DX_PI) * fSpeed;
		move.z += cosf(Camrot.y + D3DX_PI) * fSpeed;

		//�ړ������Ƀ��f����������
		RotDest.y = Camrot.y;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true
		|| pInputPad->GetLStickYPress(CInputPad::BUTTON_L_STICK, 0) < 0)
	{//S�������ꂽ
		m_bMove = true;

		move.x += sinf(Camrot.y + D3DX_PI * 0.0f) * fSpeed;
		move.z += cosf(Camrot.y + D3DX_PI * 0.0f) * fSpeed;

		//�ړ������Ƀ��f����������
		RotDest.y = Camrot.y + D3DX_PI;
	}

	if (m_bMove)
	{//�ʒu���X�V
		pos += move;

		//�ړ��ʂ��X�V(����������)
		move.x += (0.0f - move.x) * INERTIA;
		move.z += (0.0f - move.z) * INERTIA;

		m_WalkCounter = (m_WalkCounter + 1) % 20;

		if (m_WalkCounter == 0)
		{
			// �p�[�e�B�N������
			Myparticle::Create(Myparticle::TYPE_WALK, pos);

			// �T�E���h�Đ�
			CSound* pSound = CManager::GetInstance()->GetSound();
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);
		}
	}

	//�ړI�̌���
	DiffRot.y = RotDest.y - rot.y;

	// �����̐��K��
	USEFUL::NormalizeRotAngle(DiffRot.y);

	//Diff�ɕ␳�W����������
	rot.y += DiffRot.y * 0.1f;

	// �p�x�̐��K��
	USEFUL::NormalizeRotAngle(rot.y);

	// �ʒu�ݒ�
	SetPos(pos);

	// �ړ��ʐݒ�
	SetMove(move);

	// �����ݒ�
	SetRot(rot);

	// �ړI�̌����ݒ�
	SetRotDest(RotDest);

	// ���[�V����
	Motion();
}

//========================================
// ���[�V�����Ǘ�
//========================================
void CPlayer::Motion()
{
	// ���[�V�������擾
	CMotion* pMotion = GetMotion();

	if (m_bMove)
	{// �������[�V����
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_WALK);
	}
	else if (m_bCutdown)
	{// �؂艺�낵���[�V����
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_CUTDOWN);

		m_bCutdown = false;
	}
	else if (m_bMowingdown)
	{// �ガ����
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_MOWINGDOWN);

		m_bMowingdown = false;
	}
	else if (m_bStrongAttack)
	{// ���U��
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_STRONGATTACK);

		m_bStrongAttack = false;
	}
	else
	{// �ҋ@���[�V����
		pMotion->Set(CMotion::PLAYER_MOTIONTYPE_NEUTRAL);
	}

	if (pMotion != nullptr)
	{// ���[�V�����X�V
		pMotion->Update();
	}
}
